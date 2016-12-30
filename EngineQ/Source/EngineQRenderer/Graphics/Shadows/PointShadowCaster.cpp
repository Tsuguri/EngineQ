
// This project
#include "EngineQRenderer/Graphics/Renderable.hpp"
#include "EngineQRenderer/Graphics/Mesh.hpp"
#include "PointShadowCaster.hpp"
#include "EngineQRenderer/Graphics/Framebuffer.hpp"


namespace EngineQ
{
	namespace Graphics
	{
		namespace Shadows
		{
			bool PointShadowCaster::matricesComputed = false;
			Math::Matrix4 PointShadowCaster::cameraMatrices[6];

			Math::Matrix4 PointShadowCaster::GetCameraMatrice(int face)
			{
				if (!matricesComputed)
				{
					Math::Matrix4 mat = Math::Matrix4::CreateFrustum(Math::Utils::DegToRad(90.0f), 1, nearPlane, farPlane);
					cameraMatrices[0] = mat * Math::Matrix4::CreateLookAt(Math::Vector3(0.0f), Math::Vector3(1.0f, 0.0f, 0.0f), Math::Vector3(0.0f, -1.0f, 0.0f));
					cameraMatrices[1] = mat * Math::Matrix4::CreateLookAt(Math::Vector3(0.0f), Math::Vector3(-1.0f, 0.0f, 0.0f), Math::Vector3(0.0f, -1.0f, 0.0f));
					cameraMatrices[2] = mat * Math::Matrix4::CreateLookAt(Math::Vector3(0.0f), Math::Vector3(0.0f, 1.0f, 0.0f), Math::Vector3(0.0f, 0.0f, -1.0f));
					cameraMatrices[3] = mat * Math::Matrix4::CreateLookAt(Math::Vector3(0.0f), Math::Vector3(0.0f, -1.0f, 0.0f), Math::Vector3(0.0f, 0.0f, 1.0f));
					cameraMatrices[4] = mat * Math::Matrix4::CreateLookAt(Math::Vector3(0.0f), Math::Vector3(0.0f, 0.0f, 1.0f), Math::Vector3(0.0f, -1.0f, 0.0f));
					cameraMatrices[5] = mat * Math::Matrix4::CreateLookAt(Math::Vector3(0.0f), Math::Vector3(0.0f, 0.0f, -1.0f), Math::Vector3(0.0f, -1.0f, 0.0f));

				}
				return cameraMatrices[face];
			}

			void PointShadowCaster::DrawFace(const std::vector<Renderable*>& renderables, ShaderProperties* shader, Light* light, int i)
			{
				//auto matrix = GetLightMatrix()* light->GetViewMatrix();
				glViewport(0, 0, depthTexture->GetWidth(), depthTexture->GetHeight());
				framebuffers[i]->Bind();
				glClear(GL_DEPTH_BUFFER_BIT);

				const auto& matrices = shader->GetMatrices();
				matrices.View = GetCameraMatrice(i); //tu trzeba rozne kamery

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
				conf.Format = GL_DEPTH_COMPONENT;
				conf.InternalFormat = GL_DEPTH_COMPONENT;
				conf.DataType = GL_FLOAT;
				conf.Width = size.X;
				conf.Height = size.Y;

				depthTexture = Resources::Resource<CubeTexture>(std::make_unique<CubeTexture>(conf));

				std::vector<Resources::Resource<Texture>> textures;

				for (int i = 0; i < 6; i++)
				{
					framebuffers[i] = std::make_unique<Framebuffer>(false, textures, dataProvider);
					framebuffers[i]->Bind();
					framebuffers[i]->AddTexture(depthTexture->GetTextureID(), GL_DEPTH_ATTACHMENT, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i);
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