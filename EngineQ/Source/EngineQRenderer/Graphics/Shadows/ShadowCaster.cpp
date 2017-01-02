
// This project
#include "ShadowCaster.hpp"
#include "EngineQRenderer/Graphics/Renderable.hpp"
#include "EngineQRenderer/Graphics/ShaderProperties.hpp"
#include "EngineQRenderer/Graphics/Mesh.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		namespace Shadows
		{
			void ShadowCaster::Render(const std::vector<Renderable*>& renderables, ShaderProperties* shader)
			{
				for (auto renderable : renderables)
				{
					//render each object if cast shadows
					if (renderable->castShadows)
					{
						//bind model matrices to shader
						shader->GetMatrices().Model = renderable->GetGlobalMatrix();

						shader->Apply();
						auto mesh = renderable->GetMesh();
						glBindVertexArray(mesh->GetVao());
						glDrawElements(GL_TRIANGLES, mesh->GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
					}

				}
			}

			float ShadowCaster::GetNearPlane() const
			{
				return -1.0f;
			}

			void ShadowCaster::SetNearPlane(float value)
			{
			}

			float ShadowCaster::GetFarPlane() const
			{
				return -1.0f;
			}

			void ShadowCaster::SetFarPlane(float value)
			{
			}

			float ShadowCaster::GetRange() const
			{
				return -1.0f;
			}

			void ShadowCaster::SetRange(float value)
			{
			}

			float ShadowCaster::GetDistance() const
			{
				return -1.0f;
			}

			void ShadowCaster::SetDistance(float value)
			{
			}

		}
	}
}