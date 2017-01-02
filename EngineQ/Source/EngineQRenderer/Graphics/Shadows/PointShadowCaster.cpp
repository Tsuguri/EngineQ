
// This project
#include "EngineQRenderer/Graphics/Renderable.hpp"
#include "EngineQRenderer/Graphics/Mesh.hpp"
#include "PointShadowCaster.hpp"
#include "EngineQRenderer/Graphics/Framebuffer.hpp"
#include "Light.hpp"
#include "EngineQCommon/Math/Quaternion.hpp"


namespace EngineQ
{
	namespace Graphics
	{
		namespace Shadows
		{
			bool PointShadowCaster::matricesComputed = false;
			Math::Matrix4 PointShadowCaster::cameraMatrices[6];

			Math::Matrix4 PointShadowCaster::GetCameraMatrice(int face, Light* light)
			{
				static const Math::Vector3 directions[6] =
				{
					Math::Vector3(1.0f, 0.0f, 0.0f),
					Math::Vector3(-1.0f, 0.0f, 0.0f),
					Math::Vector3(0.0f, 1.0f, 0.0f),
					Math::Vector3(0.0f, -1.0f, 0.0f),
					Math::Vector3(0.0f, 0.0f, 1.0f),
					Math::Vector3(0.0f, 0.0f, -1.0f)
				};
				static const Math::Vector3 ups[6] =
				{
					Math::Vector3(0.0f, -1.0f, 0.0f),
					Math::Vector3(0.0f, -1.0f, 0.0f),
					Math::Vector3(0.0f, 0.0f, 1.0f),
					Math::Vector3(0.0f, 0.0f, -1.0f),
					Math::Vector3(0.0f, -1.0f, 0.0f),
					Math::Vector3(0.0f, -1.0f, 0.0f)
				};
				static const Math::Matrix4 mat = Math::Matrix4::CreateFrustum(Math::Utils::DegToRad(90.0f), 1, nearPlane, farPlane);

				return mat * Math::Matrix4::CreateLookAt(light->GetPosition(), light->GetPosition() + directions[face], ups[face]).GetTransposed();
			}

			void PointShadowCaster::DrawFace(const std::vector<Renderable*>& renderables, ShaderProperties* shader, Light* light, int i)
			{
				//auto matrix = GetLightMatrix()* light->GetViewMatrix();
				framebuffers[i]->Bind();
				glViewport(0, 0, depthTexture->GetWidth(), depthTexture->GetHeight());
				glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

				const auto& matrices = shader->GetMatrices();
				matrices.View = GetCameraMatrice(i,light);



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

				Framebuffer::BindDefault();
			}
			void PointShadowCaster::Init(ScreenDataProvider* dataProvider)
			{
				auto size = dataProvider->GetScreenSize();
				CubeTexture::Configuration conf;
				conf.Format = GL_RED;
				conf.InternalFormat = GL_R32F;
				conf.DataType = GL_FLOAT;
				conf.Width = size.X;
				conf.Height = size.Y;

				depthTexture = Resources::Resource<CubeTexture>(std::make_unique<CubeTexture>(conf));

				std::vector<Resources::Resource<Texture>> textures;

				for (int i = 0; i < 6; i++)
				{
					framebuffers[i] = std::make_unique<Framebuffer>(true, textures, dataProvider);
					framebuffers[i]->Bind();
					framebuffers[i]->AddTexture(depthTexture->GetTextureID(), GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i);
					GLenum temp = GL_TEXTURE_CUBE_MAP_POSITIVE_X;
					temp = GL_TEXTURE_CUBE_MAP_NEGATIVE_X;
					temp = GL_TEXTURE_CUBE_MAP_POSITIVE_Y;
					temp = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y;
					temp = GL_TEXTURE_CUBE_MAP_POSITIVE_Z;
					temp = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z;
				}
				Framebuffer::BindDefault();
			}

			void PointShadowCaster::SetLightDataInShader(const ShaderProperties::Light& lightProperties, Light* light)
			{
				lightProperties.PointShadowMap = depthTexture;
			}

			void PointShadowCaster::RenderDepthMap(const std::vector<Renderable*>& renderables, ShaderProperties* shader, Light* light)
			{
				

				for (int i = 0; i<6; i++)
					DrawFace(renderables, shader, light, i);
			}

			void PointShadowCaster::Deinitialize()
			{

			}

			float PointShadowCaster::GetNearPlane() const
			{
				return nearPlane;
			}

			void PointShadowCaster::SetNearPlane(float value)
			{
				nearPlane = value;
			}

			float PointShadowCaster::GetFarPlane() const
			{
				return farPlane;
			}

			void PointShadowCaster::SetFarPlane(float value)
			{
				farPlane = value;
			}
		}
	}
}