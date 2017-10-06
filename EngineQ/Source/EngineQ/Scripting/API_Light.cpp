#include "API_Light.hpp"

// Other projects
//#include "EngineQRenderer/Graphics/ShaderProperties.hpp"
//#include "EngineQRenderer/Graphics/Mesh.hpp"

// This project
#include "EngineQ/Objects/Light.hpp"
#include "ScriptEngine.hpp"


namespace EngineQ
{
	namespace Scripting
	{

		void API_Light::API_GetAmbientColor(const Object& lightBase, Math::Vector3& value)
		{
			const Light& light = static_cast<const Light&>(lightBase);

			value = light.GetAmbientColor();
		}

		void API_Light::API_SetAmbientColor(Object& lightBase, const Math::Vector3& value)
		{
			Light& light = static_cast<Light&>(lightBase);

			light.SetAmbientColor(value);
		}

		void API_Light::API_GetDiffuseColor(const Object& lightBase, Math::Vector3& value)
		{
			const Light& light = static_cast<const Light&>(lightBase);

			value = light.GetDiffuseColor();
		}

		void API_Light::API_SetDiffuseColor(Object& lightBase, const Math::Vector3& value)
		{
			Light& light = static_cast<Light&>(lightBase);

			light.SetDiffuseColor(value);
		}

		void API_Light::API_GetSpecularColor(const Object& lightBase, Math::Vector3& value)
		{
			const Light& light = static_cast<const Light&>(lightBase);

			value = light.GetSpecularColor();
		}

		void API_Light::API_SetSpecularColor(Object& lightBase, const Math::Vector3& value)
		{
			Light& light = static_cast<Light&>(lightBase);

			light.SetSpecularColor(value);
		}

		void API_Light::API_GetLightType(const Object& lightBase, Graphics::Shadows::Light::Type& value)
		{
			const Light& light = static_cast<const Light&>(lightBase);

			value = light.GetLightType();
		}

		void API_Light::API_SetLightType(Object& lightBase, Graphics::Shadows::Light::Type value)
		{
			Light& light = static_cast<Light&>(lightBase);

			light.SetLightType(value);
		}

		void API_Light::API_GetTextureSize(const Object& lightBase, Math::Vector2i& value)
		{
			const Light& light = static_cast<const Light&>(lightBase);

			value = light.GetShadowTextureSize();
		}

		void API_Light::API_SetTextureSize(Object& lightBase, const Math::Vector2i& value)
		{
			Light& light = static_cast<Light&>(lightBase);

			light.SetShadowTextureSize(value);
		}

		void API_Light::API_GetCastShadows(const Object& lightBase, bool& value)
		{
			const Light& light = static_cast<const Light&>(lightBase);

			value = light.GetCastShadows();
		}

		void API_Light::API_SetCastShadows(Object& lightBase, bool value)
		{
			Light& light = static_cast<Light&>(lightBase);

			light.SetCastShadows(value);
		}

		void API_Light::API_GetDistance(const Object& lightBase, float& value)
		{
			const Light& light = static_cast<const Light&>(lightBase);

			value = light.GetDistance();
		}

		void API_Light::API_SetDistance(Object& lightBase, float value)
		{
			Light& light = static_cast<Light&>(lightBase);

			light.SetDistance(value);
		}

		void API_Light::API_GetRange(const Object& lightBase, float& value)
		{
			const Light& light = static_cast<const Light&>(lightBase);

			value = light.GetRange();
		}

		void API_Light::API_SetRange(Object& lightBase, float value)
		{
			Light& light = static_cast<Light&>(lightBase);

			light.SetRange(value);
		}

		void API_Light::API_Register(ScriptEngine& scriptEngine)
		{
			scriptEngine.API_Register("EngineQ.Light::API_GetAmbientColor", API_GetAmbientColor);
			scriptEngine.API_Register("EngineQ.Light::API_SetAmbientColor", API_SetAmbientColor);
			scriptEngine.API_Register("EngineQ.Light::API_GetDiffuseColor", API_GetDiffuseColor);
			scriptEngine.API_Register("EngineQ.Light::API_SetDiffuseColor", API_SetDiffuseColor);
			scriptEngine.API_Register("EngineQ.Light::API_GetSpecularColor", API_GetSpecularColor);
			scriptEngine.API_Register("EngineQ.Light::API_SetSpecularColor", API_SetSpecularColor);
			scriptEngine.API_Register("EngineQ.Light::API_GetLightType", API_GetLightType);
			scriptEngine.API_Register("EngineQ.Light::API_SetLightType", API_SetLightType);
			scriptEngine.API_Register("EngineQ.Light::API_GetTextureSize", API_GetTextureSize);
			scriptEngine.API_Register("EngineQ.Light::API_SetTextureSize", API_SetTextureSize);
			scriptEngine.API_Register("EngineQ.Light::API_GetCastShadows", API_GetCastShadows);
			scriptEngine.API_Register("EngineQ.Light::API_SetCastShadows", API_SetCastShadows);
			scriptEngine.API_Register("EngineQ.Light::API_GetDistance", API_GetDistance);
			scriptEngine.API_Register("EngineQ.Light::API_SetDistance", API_SetDistance);
			scriptEngine.API_Register("EngineQ.Light::API_GetRange", API_GetRange);
			scriptEngine.API_Register("EngineQ.Light::API_SetRange", API_SetRange);
		}
	}
}