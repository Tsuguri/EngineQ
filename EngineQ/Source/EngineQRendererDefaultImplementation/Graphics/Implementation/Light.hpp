#ifndef ENGINEQ_GRAPHICS_IMPLEMENTATION_LIGHT_HPP
#define ENGINEQ_GRAPHICS_IMPLEMENTATION_LIGHT_HPP

#include "EngineQRenderer/Graphics/Shadows/Light.hpp"
#include "EngineQRenderer/Graphics/ShaderProperties.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		namespace Implementation
		{
			class Light : public Graphics::Shadows::Light
			{
				Math::Vector2i textureSize = Math::Vector2i{ 1024,1024 };
				std::unique_ptr<ShaderProperties> shaderProperties;
				bool castShadows = true;

				Math::Vector3 position;
				Math::Vector3 direction;

			public :
				virtual Math::Vector3 GetPosition() override;
				void SetPosition(Math::Vector3 newPosition);
				virtual Math::Vector3 GetDirection() override;
				void SetDirection(Math::Vector3 newDirection);
				virtual Math::Matrix4 GetViewMatrix() override;

				virtual ShaderProperties* GetShaderProperties() const override;

				virtual bool GetCastShadows() override;
				void SetCastShadows(bool value);
			};
		}
	}
}
#endif // !ENGINEQ_GRAPHICS_IMPLEMENTATION_LIGHT_HPP
