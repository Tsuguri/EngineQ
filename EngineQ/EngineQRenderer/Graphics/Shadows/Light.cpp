#include "Light.hpp"

#include "../Renderable.hpp"
#include "../Mesh.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		namespace Shadows
		{
			void Light::Init()
			{
				glGenFramebuffers(1, &depthMapFBO);
				auto size = screenDataProvider->GetScreenSize();

				GLuint depthMap;
				glGenTextures(1, &depthMap);
				glBindTexture(GL_TEXTURE_2D, depthMap);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
					size.X, size.Y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

				glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
				glDrawBuffer(GL_NONE);
				glReadBuffer(GL_NONE);
				glBindFramebuffer(GL_FRAMEBUFFER, 0);

				GLfloat near_plane = 1.0f, far_plane = 7.5f;
				Math::Matrix4 lightProjection = Math::Matrix4::CreateOrtho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
				Math::Matrix4 lightView = Math::Matrix4::CreateLookAt(GetPosition(), Math::Vector3{ 0,0,0 }, Math::Vector3{ 0,1,0 });
			}
			Light::Light(Utils::ScreenDataProvider* screenDataProvider) : screenDataProvider(screenDataProvider)
			{			
			}

			void Light::RenderDepthMap(const std::vector<Renderable*>& renderables) const
			{
				auto shader = GetShaderProperties();
				if (shader == nullptr)
					return;
				auto size = screenDataProvider->GetScreenSize();
				glViewport(0, 0, size.X, size.Y);
				glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
				glClear(GL_DEPTH_BUFFER_BIT);
				
				//enable shader
				//send matrices
				// get positionmatrix, etc	
				
				const auto& matrices = shader->GetMatrices();
				matrices.View = lightMatrix;

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
		}
	}
}