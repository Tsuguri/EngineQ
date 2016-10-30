#ifndef ENGINEQ_SCRIPTING_API_SHADER_PROPERTIES_HPP
#define ENGINEQ_SCRIPTING_API_SHADER_PROPERTIES_HPP

#include "Types.hpp"
#include "../Objects/Types.hpp"

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
			static void API_Set(Object& shaderPropertiesBase, int propertyIndex, MonoReflectionType* propertyType, MonoObject*& value);

			static void API_Register(ScriptEngine& scriptEngine);
		};
	}
}

#endif // !ENGINEQ_SCRIPTING_API_SHADER_PROPERTIES_HPP
