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
			bool castShadows = true;
			bool receiveShadows = true;

			virtual Graphics::ShaderProperties* GetForwardShader() const = 0;
			virtual Graphics::ShaderProperties* GetDeferredShader() const = 0;


			virtual Resources::Resource<Graphics::Mesh> GetMesh() const = 0;

			virtual Math::Vector3 GetPosition() = 0;

			virtual Math::Matrix4 GetGlobalMatrix() = 0;

			void SetCastShadows(bool val);
			bool GetCastShadows() const;

			void SetReceiveShadows(bool val);
			bool GetReceiveShadows() const;

			virtual ~Renderable() = default;
		};
	}
}
#endif // !ENGINEQ_GRAPHICS_RENDERABLE_HPP
