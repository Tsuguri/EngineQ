
// This project
#include "EngineQRenderer/Graphics/Renderable.hpp"
#include "EngineQRenderer/Graphics/Mesh.hpp"
#include "DirectionalShadowCaster.hpp"
#include "EngineQRenderer/Graphics/Framebuffer.hpp"
#include "Light.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		namespace Shadows
		{
			Math::Matrix4 DirectionalShadowCaster::GetLightMatrix()
			{
				Math::Matrix4 lightProjection = Math::Matrix4::CreateOrtho(-range, range, -range, range, nearPlane, farPlane);
				return lightProjection;
			}
			void DirectionalShadowCaster::Init(ScreenDataProvider* dataProvider)
			{
				Configuration::TextureConfiguration conf;
				conf.Format = GL_DEPTH_COMPONENT;
				conf.InternalFormat = GL_DEPTH_COMPONENT;
				conf.DataType = GL_FLOAT;
				conf.setBorderColor = true;
				conf.borderCorlor = { 1.0f, 1.0f, 1.0f, 1.0f };

				auto size = dataProvider->GetScreenSize();
				depthTexture = Resources::Resource<Texture>(std::make_unique<Texture>(size.X, size.Y, conf));

				std::vector<Resources::Resource<Texture>> textures;
				framebuffer = std::make_unique<Framebuffer>(false, textures, dataProvider);
				framebuffer->Bind();
				framebuffer->AddTexture(depthTexture->GetTextureID(), GL_DEPTH_ATTACHMENT);
				framebuffer->ResetDrawBuffer();
				framebuffer->ResetReadBuffer();
				Framebuffer::BindDefault();
			}
			void DirectionalShadowCaster::SetLightDataInShader(const ShaderProperties::Light& lightProperties, Light* light)
			{
				lightProperties.DirectionalShadowMap = depthTexture;
				lightProperties.LightMatrix = GetLightMatrix() * light->GetViewMatrix();
			}
			void DirectionalShadowCaster::RenderDepthMap(const std::vector<Renderable*>& renderables, ShaderProperties* shader, Light* light)
			{
				auto matrix = GetLightMatrix()* light->GetViewMatrix();
				glViewport(0, 0, depthTexture->GetWidth(), depthTexture->GetHeight());
				framebuffer->Bind();
				glClearColor(farPlane, 0.0f, 0.0f, 1.0f);
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

			void DirectionalShadowCaster::Deinitialize()
			{
				framebuffer->UnsubscribeFromResize();
			}

			float DirectionalShadowCaster::GetNearPlane() const
			{
				return nearPlane;
			}

			void DirectionalShadowCaster::SetNearPlane(float value)
			{
				nearPlane = value;
			}

			float DirectionalShadowCaster::GetFarPlane() const
			{
				return farPlane;
			}

			void DirectionalShadowCaster::SetFarPlane(float value)
			{
				farPlane = value;
			}

			float DirectionalShadowCaster::GetRange() const
			{
				return range;
			}

			void DirectionalShadowCaster::SetRange(float value)
			{
				range = value;
			}
		}
	}
}