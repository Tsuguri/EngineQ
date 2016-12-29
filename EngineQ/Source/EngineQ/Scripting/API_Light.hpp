#ifndef ENGINEQ_SCRIPTING_API_LIGHT_HPP
#define ENGINEQ_SCRIPTING_API_LIGHT_HPP

// Other projects
#include "EngineQRenderer/Graphics/Types.hpp"
#include "EngineQCommon/Resources/Resource.hpp"
#include "EngineQCommon/Math/Vector3.hpp"
#include "EngineQRenderer/Graphics/Shadows/Light.hpp"

// This project
#include "Types.hpp"
#include "EngineQ/Objects/Types.hpp"


namespace EngineQ
{
	namespace Scripting
	{
		class API_Light
		{
		public:

			static void API_GetAmbientColor(const Object& lightBase, Math::Vector3& value);
			static void API_SetAmbientColor(Object& lightBase, const Math::Vector3& value);
			
			static void API_GetDiffuseColor(const Object& lightBase, Math::Vector3& value);
			static void API_SetDiffuseColor(Object& lightBase, const Math::Vector3& value);

			static void API_GetSpecularColor(const Object& lightBase, Math::Vector3& value);
			static void API_SetSpecularColor(Object& lightBase, const Math::Vector3& value);

			static void API_GetLightType(const Object& lightBase, Graphics::Shadows::Light::Type& value);
			static void API_SetLightType(Object& lightBase, Graphics::Shadows::Light::Type value);

			static void API_GetTextureSize(const Object& lightBase, Math::Vector2i& value);
			static void API_SetTextureSize(Object& lightBase, const Math::Vector2i& value);

			static void API_GetCastShadows(const Object& lightBase, bool& value);
			static void API_SetCastShadows(Object& lightBase, bool value);

			static void API_GetDistance(const Object& lightBase, float& value);
			static void API_SetDistance(Object& lightBase, float value);

			static void API_GetRange(const Object& lightBase, float& value);
			static void API_SetRange(Object& lightBase, float value);


			static void API_Register(ScriptEngine& scriptEngine);
		};
	}
}

#endif // !ENGINEQ_SCRIPTING_API_LIGHT_HPP
