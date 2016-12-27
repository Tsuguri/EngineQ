#include "Light.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		namespace Implementation
		{
			Math::Vector3 Light::GetPosition()
			{
				return position;
			}

			void Light::SetPosition(Math::Vector3 newPosition)
			{
				position = newPosition;
			}

			Math::Vector3 Light::GetDirection()
			{
				return direction;
			}

			void Light::SetDirection(Math::Vector3 newDirection)
			{
				direction = newDirection;
			}

			Math::Matrix4 Light::GetViewMatrix()
			{

			}

			ShaderProperties* Light::GetShaderProperties() const
			{
				return shaderProperties.get();
			}

			bool Light::GetCastShadows()
			{
				return castShadows;
			}

			void Light::SetCastShadows(bool value)
			{
				castShadows = value;
			}
		}
	}
}