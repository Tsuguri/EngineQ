#include "ScriptedRenderingUnit.hpp"

// Other projects
#include "EngineQRenderer/Graphics/Mesh.hpp"

// This project
#include "EngineQ/Scripting/ScriptEngine.hpp"
#include "EngineQ/Engine.hpp"


namespace EngineQ
{
	namespace Graphics
	{
		void DepthRenderer::ResizeEventHandler(int sizeX, int sizeY)
		{
			this->size.X = sizeX;
			this->size.Y = sizeY;

			this->depthTexture->Resize(sizeX, sizeY);
		}

		DepthRenderer::DepthRenderer(Scripting::ScriptEngine& scriptEngine, Resources::Resource<Shader> shader, ScreenDataProvider* dataProvider, bool drawVolumetric) :
			shaderProperties{ scriptEngine, shader }, resizeHandler{ *this, &DepthRenderer::ResizeEventHandler }, drawVolumetric{ drawVolumetric }
		{
			this->screenDataProvider = dataProvider;
			this->size = dataProvider->GetScreenSize();

			dataProvider->resizeEvent += this->resizeHandler;

			Configuration::TextureConfiguration conf;
			conf.Format = GL_DEPTH_COMPONENT;
			conf.InternalFormat = GL_DEPTH_COMPONENT;
			conf.DataType = GL_FLOAT;
			conf.setBorderColor = true;
			conf.borderCorlor = { 1.0f, 1.0f, 1.0f, 1.0f };

			depthTexture = Resources::Resource<Texture>(std::make_unique<Texture>(size.X, size.Y, conf));

			// strange framebuffer here so not using Framebuffer class, but will need rework in the future - extend usability of Framebuffer (more configurable)
			glGenFramebuffers(1, &depthMapFBO);

			glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture->GetTextureID(), 0);
			glDrawBuffer(GL_NONE);
			glReadBuffer(GL_NONE);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		DepthRenderer::~DepthRenderer()
		{
			this->screenDataProvider->resizeEvent -= this->resizeHandler;
			glDeleteFramebuffers(1, &depthMapFBO);
		}

		void DepthRenderer::RenderDepthMap(const std::vector<Renderable*>& renderables, Math::Matrix4 viewMatrix, Math::Matrix4 projectionMatrix)
		{
			glViewport(0, 0, size.X, size.Y);
			glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
			glClear(GL_DEPTH_BUFFER_BIT);

			const auto& matrices = this->shaderProperties.GetMatrices();
			matrices.View = viewMatrix;
			matrices.Projection = projectionMatrix;

			for (auto renderable : renderables)
			{
				if (renderable->GetVolimetric() != drawVolumetric)
					continue;

				matrices.Model = renderable->GetGlobalMatrix();

				this->shaderProperties.Apply();
				auto mesh = renderable->GetMesh();
				glBindVertexArray(mesh->GetVao());
				glDrawElements(GL_TRIANGLES, mesh->GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
			}

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		Resources::Resource<Texture> DepthRenderer::GetDepthTexture()
		{
			return depthTexture;
		}






		ScriptedRenderingUnit::ScriptedRenderingUnit(Scripting::ScriptEngine& scriptEngine, ScreenDataProvider* screenDataProvider, const Configuration::RenderingUnitConfiguration& configuration) :
			RenderingUnit(screenDataProvider, configuration, std::make_unique<ScriptedShaderPassFactory>(*this)), scriptEngine(scriptEngine), lightSizer{ Math::Vector2i{2048, 2048} }
		{
			Initialize(configuration);

			auto& rm = Engine::Get().GetResourceManager();

			auto shader = rm.GetResource<Shader>("LightDepthRender");

			this->forwardDepthRenderer = std::make_unique<DepthRenderer>(this->scriptEngine, shader, screenDataProvider, true);
			this->backDepthRenderer = std::make_unique<DepthRenderer>(this->scriptEngine, shader, screenDataProvider, true);
			this->depthRenderer = std::make_unique<DepthRenderer>(this->scriptEngine, shader, screenDataProvider, false);

			this->light0backDepth = std::make_unique<DepthRenderer>(this->scriptEngine, shader, &lightSizer, true);
			this->light0frontDepth = std::make_unique<DepthRenderer>(this->scriptEngine, shader, &lightSizer, true);
		}

		void ScriptedRenderingUnit::Update()
		{
			for (auto effect : this->updatable)
				effect->Update();
		}

		Math::Matrix4 CreateFrustum(Math::Real fovy, Math::Real aspect, Math::Real near, Math::Real far)
		{
			// Use for GREATER depth testing
			Math::Real cot = static_cast<Math::Real>(1) / std::tan(fovy / static_cast<Math::Real>(2));
			Math::Real diff = static_cast<Math::Real>(1) / (far - near);

			return Math::Matrix4{
			cot / aspect, static_cast<Math::Real>(0), static_cast<Math::Real>(0), static_cast<Math::Real>(0),
			static_cast<Math::Real>(0), cot, static_cast<Math::Real>(0), static_cast<Math::Real>(0),
			static_cast<Math::Real>(0), static_cast<Math::Real>(0), -(far + near) * diff, static_cast<Math::Real>(2) * far * near * diff,
			static_cast<Math::Real>(0), static_cast<Math::Real>(0), static_cast<Math::Real>(1), static_cast<Math::Real>(0)
			};
		}

		// TMP The most temporary thing in the world
		void ScriptedRenderingUnit::Render(Scene & scene)
		{
			auto& sceneLights = scene.GetLights();

		//	glDisable(GL_CULL_FACE);

			glClearDepth(1.0f);
			glCullFace(GL_BACK);
			glDepthFunc(GL_LESS);
			this->forwardDepthRenderer->RenderDepthMap(scene.GetRenderables(), scene.GetActiveCamera()->GetViewMatrix(), scene.GetActiveCamera()->GetProjectionMatrix());
			if (sceneLights.size() > 0)
				this->light0frontDepth->RenderDepthMap(scene.GetRenderables(), sceneLights[0]->GetLightMatrix(), Math::Matrix4::GetIdentity());


			glClearDepth(0.0f);
			glCullFace(GL_FRONT);
			glDepthFunc(GL_GEQUAL);
			this->backDepthRenderer->RenderDepthMap(scene.GetRenderables(), scene.GetActiveCamera()->GetViewMatrix(), scene.GetActiveCamera()->GetProjectionMatrix());
			if (sceneLights.size() > 0)
				this->light0backDepth->RenderDepthMap(scene.GetRenderables(), sceneLights[0]->GetLightMatrix(), Math::Matrix4::GetIdentity());




			// Restore defaults
			glClearDepth(1.0f);
			glDepthFunc(GL_LESS);
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);

			this->depthRenderer->RenderDepthMap(scene.GetRenderables(), scene.GetActiveCamera()->GetViewMatrix(), scene.GetActiveCamera()->GetProjectionMatrix());







			renderer.Render(scene, screenDataProvider);

			auto& camera = *scene.GetActiveCamera();


			if (effects.size() > 0)
			{
				glDisable(GL_DEPTH_TEST);

				for (auto& effect : effects)
				{
					effect->BeforeRender();

					effect->BindTargetBuffer();

					glClear(GL_COLOR_BUFFER_BIT);
					glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
					auto& shader = effect->GetShaderProperties();

					shader.GetMatrices().View = camera.GetViewMatrix();
					shader.GetMatrices().Projection = camera.GetProjectionMatrix();


					auto frontDepth = shader.TryGetProperty<Resources::Resource<Texture>>("frontDepth");
					if (frontDepth != nullval)
						*frontDepth = this->forwardDepthRenderer->GetDepthTexture();

					auto backDepth = shader.TryGetProperty<Resources::Resource<Texture>>("backDepth");
					if (backDepth != nullval)
						*backDepth = this->backDepthRenderer->GetDepthTexture();

					auto depthMap = shader.TryGetProperty<Resources::Resource<Texture>>("depthMap");
					if (depthMap != nullval)
						*depthMap = this->depthRenderer->GetDepthTexture();

					if (sceneLights.size() > 0)
					{
						auto light0backMap = shader.TryGetProperty<Resources::Resource<Texture>>("light0backVolumeMap");
						if (light0backMap != nullval)
							*light0backMap = this->light0backDepth->GetDepthTexture();

						auto light0frontMap = shader.TryGetProperty<Resources::Resource<Texture>>("light0frontVolumeMap");
						if (light0frontMap != nullval)
							*light0frontMap = this->light0frontDepth->GetDepthTexture();
					}

					if (effect->GetApplyShadowData())
					{
						auto& lights = shader.GetLights();
						auto lightsCount = sceneLights.size() > lights.size() ? lights.size() : sceneLights.size();
						shader.GetLightCount() = static_cast<GLint>(lightsCount);

						for (std::size_t i = 0; i < lightsCount; ++i)
						{
							auto& light = lights[i];
							auto sceneLight = sceneLights[i];

							light.Position = sceneLight->GetPosition();
							light.Direction = sceneLight->GetDirection();
							light.Distance = sceneLight->GetDistance();

							light.Diffuse = Math::Vector3f(0.5f);
							light.Ambient = Math::Vector3f(0.3f);
							light.Specular = Math::Vector3f(1.0f);

							light.CastsShadows = sceneLight->GetCastShadows();
							light.LightMatrix = sceneLight->GetLightMatrix();
							light.DirectionalShadowMap = sceneLight->GetDepthTexture();
							light.FarPlane = sceneLight->GetFarPlane();
						}
					}

					effect->Activate(scene.GetActiveCamera(), 0);
					glBindVertexArray(quadVao);

					glDrawArrays(GL_TRIANGLES, 0, 6);
					glBindVertexArray(0);

					effect->AfterRender();
				}

				glEnable(GL_DEPTH_TEST);
			}
			Framebuffer::BindDefault();
		}

		ScriptedRenderingUnit::ScriptedShaderPassFactory::ScriptedShaderPassFactory(ScriptedRenderingUnit& parent) :
			parent(parent)
		{
		}

		std::unique_ptr<ShaderPass> ScriptedRenderingUnit::ScriptedShaderPassFactory::CreateShaderPass(const Configuration::EffectConfiguration& config)
		{
			Scripting::ScriptClass effectController;
			if (config.ClassName.empty())
			{
				effectController = parent.scriptEngine.GetClass(Scripting::ScriptEngine::Class::EffectController);
			}
			else
			{
				effectController = parent.scriptEngine.GetEffectControllerClass(config.ClassAssembly.c_str(), config.ClassNamespace.c_str(), config.ClassName.c_str());
			}

			auto shaderPass = std::make_unique<ScriptedShaderPass>(parent.scriptEngine, effectController, config.EffectShader);

			if (shaderPass->IsUpdatable())
				parent.updatable.push_back(shaderPass.get());

			return std::move(shaderPass);
		}

		Math::Vector2i ScriptedRenderingUnit::CustomProvider::GetScreenSize() const
		{
			return this->size;
		}

		ScriptedRenderingUnit::CustomProvider::CustomProvider(Math::Vector2i size) :
			size{ size }
		{
		}
	}
}