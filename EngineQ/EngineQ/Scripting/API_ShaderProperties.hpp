#ifndef ENGINEQ_SCRIPTING_API_SHADER_PROPERTIES_HPP
#define ENGINEQ_SCRIPTING_API_SHADER_PROPERTIES_HPP

// Other projects
#include "EngineQCommon/Math/Types.hpp"

// This project
#include "Types.hpp"
#include "EngineQ/Objects/Types.hpp"


namespace EngineQ
{
	namespace Scripting
	{
		class API_ShaderProperties
		{
		public:
			static void API_GetShader(const Object& shaderPropertiesBase, MonoObject*& shader);
			static void API_GetPropertyIndex(Object& shaderPropertiesBase, MonoString* propertyName, MonoReflectionType* propertyType, int& propertyIndex);
			
			static void API_Get(Object& shaderPropertiesBase, int propertyIndex, MonoReflectionType* propertyType, MonoObject*& value);
			static void API_Set(Object& shaderPropertiesBase, int propertyIndex, MonoReflectionType* propertyType, MonoObject* const& value);

			static void API_GetAmbient(Object& shaderPropertiesBase, Math::Vector3f& ambient);
			static void API_SetAmbient(Object& shaderPropertiesBase, const Math::Vector3f& ambient);

			static void API_GetDiffuse(Object& shaderPropertiesBase, Math::Vector3f& diffuse);
			static void API_SetDiffuse(Object& shaderPropertiesBase, const Math::Vector3f& diffuse);

			static void API_GetSpecular(Object& shaderPropertiesBase, Math::Vector3f& specular);
			static void API_SetSpecular(Object& shaderPropertiesBase, const Math::Vector3f& specular);

			static void API_GetShininess(Object& shaderPropertiesBase, float& shininess);
			static void API_SetShininess(Object& shaderPropertiesBase, float shininess);

			static void API_GetDiffuseTexture(Object& shaderPropertiesBase, MonoObject*& diffuseTexture);
			static void API_SetDiffuseTexture(Object& shaderPropertiesBase, MonoObject* diffuseTexture);

			static void API_GetSpecularTexture(Object& shaderPropertiesBase, MonoObject*& specularTexture);
			static void API_SetSpecularTexture(Object& shaderPropertiesBase, MonoObject* specularTexture);

			static void API_GetNormalTexture(Object& shaderPropertiesBase, MonoObject*& normalTexture);
			static void API_SetNormalTexture(Object& shaderPropertiesBase, MonoObject* normalTexture);


			static void API_Register(ScriptEngine& scriptEngine);
		};
	}
}

#endif // !ENGINEQ_SCRIPTING_API_SHADER_PROPERTIES_HPP
