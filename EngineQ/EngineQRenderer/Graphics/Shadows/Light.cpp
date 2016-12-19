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
				auto size = screenDataProvider->GetScreenSize();
				Configuration::TextureConfiguration conf;
				conf.Format = GL_DEPTH_COMPONENT;
				conf.InternalFormat = GL_DEPTH_COMPONENT;
				conf.DataType = GL_FLOAT;

				depthTexture = Resources::Resource<Texture>(std::make_unique<Texture>(size.X, size.Y, conf));

				// strange framebuffer here so not using Framebuffer class, but will need rework in the future - extend usability of Framebuffer (more configurable)
				glGenFramebuffers(1, &depthMapFBO);

				glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture->GetTextureID(), 0);
				glDrawBuffer(GL_NONE);
				glReadBuffer(GL_NONE);
				glBindFramebuffer(GL_FRAMEBUFFER, 0);
			}

			void Light::RenderDepthMap(const std::vector<Renderable*>& renderables) const
			{
				auto shader = GetShaderProperties();
				if (shader == nullptr)
					return;
				auto size = screenDataProvider->GetScreenSize();
				auto matrix = GetLightMatrix();

				glViewport(0, 0, size.X, size.Y);
				glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
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

				glBindFramebuffer(GL_FRAMEBUFFER, 0);
			}

			Resources::Resource<Texture> Light::GetDepthTexture()
			{
				return depthTexture;
			}

			Math::Matrix4 Light::GetLightMatrix() const
			{
				GLfloat near_plane = 1.0f, far_plane = 30.0f;
				GLfloat range = 10.0f;
				Math::Matrix4 lightProjection = Math::Matrix4::CreateOrtho(-range, range, -range, range, near_plane, far_plane);
				Math::Matrix4 lightView = Math::Matrix4::CreateLookAt(-GetPosition(), Math::Vector3{ 0,0,0 }, Math::Vector3{ 0,1,0 });
				return lightProjection*lightView;
			}
		}
	}
}