#include "Light.hpp"

// This project
#include "EngineQRenderer/Graphics/Renderable.hpp"
#include "EngineQRenderer/Graphics/Mesh.hpp"


namespace EngineQ
{
	namespace Graphics
	{
		namespace Shadows
		{
			void Light::Init(ScreenDataProvider* dataProvider)
			{
				this->screenDataProvider = dataProvider;
				Configuration::TextureConfiguration conf;
				conf.Format = GL_DEPTH_COMPONENT;
				conf.InternalFormat = GL_DEPTH_COMPONENT;
				conf.DataType = GL_FLOAT;
				conf.setBorderColor = true;
				conf.borderCorlor = { 1.0f, 1.0f, 1.0f, 1.0f };

				depthTexture = Resources::Resource<Texture>(std::make_unique<Texture>(size.X, size.Y, conf));

				std::vector<Resources::Resource<Texture>> textures;
				framebuffer = std::make_unique<Framebuffer>(false, textures, screenDataProvider);
				framebuffer->Bind();
				framebuffer->AddTexture(depthTexture->GetTextureID(), GL_DEPTH_ATTACHMENT);
				framebuffer->ResetDrawBuffer();
				framebuffer->ResetReadBuffer();
				Framebuffer::BindDefault();
			}

			void Light::RenderDepthMap(const std::vector<Renderable*>& renderables)
			{
				auto shader = GetShaderProperties();
				if (shader == nullptr)
					return;
				auto matrix = GetLightMatrix();

				glViewport(0, 0, size.X, size.Y);
				framebuffer->Bind();
				glClear(GL_DEPTH_BUFFER_BIT);

				const auto& matrices = shader->GetMatrices();
				matrices.View = matrix;

				for (auto renderable : renderables)
				{
					//render each object if cast shadows
					if (renderable->castShadows)
					{
						//bind model matrices to shader
						matrices.Model = renderable->GetGlobalMatrix();

						shader->Apply();
						auto mesh = renderable->GetMesh();
						glBindVertexArray(mesh->GetVao());
						glDrawElements(GL_TRIANGLES, mesh->GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
					}

				}

				framebuffer->BindDefault();
			}

			float Light::GetNearPlane() const
			{
				return this->nearPlane;
			}

			float Light::GetFarPlane() const
			{
				return this->farPlane;
			}

			float Light::GetDistance() const
			{
				return this->distance;
			}

			Resources::Resource<Texture> Light::GetDepthTexture()
			{
				return depthTexture;
			}

			Math::Matrix4 Light::GetLightMatrix()
			{
				GLfloat range = 6.0f;
				Math::Matrix4 lightProjection = Math::Matrix4::CreateOrtho(-range, range, -range, range, this->nearPlane, this->farPlane);
				Math::Matrix4 lightView = this->GetViewMatrix();
				return lightProjection * lightView;
			}
		}
	}
}