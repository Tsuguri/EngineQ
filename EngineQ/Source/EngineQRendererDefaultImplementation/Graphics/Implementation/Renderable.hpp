#ifndef ENGINEQ_GRAPHICS_IMPLEMENTATION_RENDERABLE_HPP
#define ENGINEQ_GRAPHICS_IMPLEMENTATION_RENDERABLE_HPP

#include "EngineQRenderer/Graphics/Renderable.hpp"

#include "Moveable.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		namespace Implementation
		{
			class Renderable : public Graphics::Renderable, public Moveable
			{
			private:
				std::unique_ptr<ShaderProperties> forwardShader;
				std::unique_ptr<ShaderProperties> deferredShader;
				Resources::Resource<Graphics::Mesh> mesh;

			public:

				void SetForwardShader(Resources::Resource<Graphics::Shader> shader);
				virtual Graphics::ShaderProperties* GetForwardShader() const override;
				void SetDeferredShader(Resources::Resource<Graphics::Shader> shader);
				virtual Graphics::ShaderProperties* GetDeferredShader() const override;

				void SetMesh(Resources::Resource<Graphics::Mesh> mesh);
				virtual Resources::Resource<Graphics::Mesh> GetMesh() const override;

				virtual Math::Vector3 GetPosition() override;

				virtual Math::Matrix4 GetGlobalMatrix() override;


			};
		}
	}
}
#endif // !ENGINEQ_GRAPHICS_IMPLEMENTATION_RENDERABLE_HPP
