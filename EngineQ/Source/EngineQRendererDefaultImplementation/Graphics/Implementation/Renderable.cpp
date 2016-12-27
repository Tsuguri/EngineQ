#include "Renderable.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		namespace Implementation
		{
			void Renderable::SetForwardShader(Resources::Resource<Graphics::Shader> shader)
			{
				this->forwardShader = std::make_unique<ShaderProperties>(shader);
			}
			Graphics::ShaderProperties* Renderable::GetForwardShader() const
			{
				return this->forwardShader.get();
			}

			void Renderable::SetDeferredShader(Resources::Resource<Graphics::Shader> shader)
			{
				this->forwardShader = std::make_unique<ShaderProperties>(shader);
			}

			Graphics::ShaderProperties* Renderable::GetDeferredShader() const
			{
				return this->deferredShader.get();
			}

			void Renderable::SetMesh(Resources::Resource<Graphics::Mesh> mesh)
			{
				this->mesh = mesh;
			}

			Resources::Resource<Graphics::Mesh> Renderable::GetMesh() const
			{
				return this->mesh;
			}

			Math::Vector3 Renderable::GetPosition()
			{
				return Moveable::GetPosition();
			}

			Math::Matrix4 Renderable::GetGlobalMatrix()
			{
				return Moveable::GetLocalMatrix();
			}
		}
	}
}