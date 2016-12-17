#ifndef ENGINEQ_GRAPHICS_RENDERABLE_HPP
#define ENGINEQ_GRAPHICS_RENDERABLE_HPP

#include <Math\Vector3.hpp>

#include "ShaderProperties.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		class Renderable
		{
		public:
			bool castShadows;
			bool reveiveShadows;

			virtual Graphics::ShaderProperties* GetForwardShader() const =0;
			virtual Graphics::ShaderProperties* GetDeferredShader() const = 0;


			virtual Resources::Resource<Graphics::Mesh> GetMesh() const = 0;

			virtual Math::Vector3 GetPosition() = 0;

			virtual Math::Matrix4 GetGlobalMatrix() = 0;
		};
	}
}
#endif // !ENGINEQ_GRAPHICS_RENDERABLE_HPP
