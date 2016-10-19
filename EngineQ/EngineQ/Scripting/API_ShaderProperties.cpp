#include "API_ShaderProperties.hpp"

#include "ScriptEngine.hpp"
#include "../Graphics/ShaderProperties.hpp"

namespace EngineQ
{
	namespace Scripting
	{
		void API_ShaderProperties::API_GetPropertyIndex(Object& shaderPropertiesBase, MonoString* propertyName, MonoReflectionType* propertyType, int& propertyIndex)
		{
			using Class = EngineQ::Scripting::ScriptEngine::Class;

			auto& shaderProperties = static_cast<Graphics::ShaderProperties&>(shaderPropertiesBase);
			const auto& scriptEngine = shaderProperties.GetScriptEngine();

			std::string name = scriptEngine.GetScriptStringContent(propertyName);

			MonoClass* propertyClass = scriptEngine.GetTypeClass(propertyType);
			if (propertyClass == scriptEngine.GetClass(Class::Float))
			{
				propertyIndex = shaderProperties.GetPropertyIndex<float>(name);
			}
			else if (propertyClass == scriptEngine.GetClass(Class::Integer))
			{
				propertyIndex = shaderProperties.GetPropertyIndex<int>(name);
			}
			else if (propertyClass == scriptEngine.GetClass(Class::Vector3f))
			{
				propertyIndex = shaderProperties.GetPropertyIndex<Math::Vector3f>(name);
			}
			else if (propertyClass == scriptEngine.GetClass(Class::Texture))
			{
				propertyIndex = shaderProperties.GetPropertyIndex<Resources::Resource<Graphics::Texture>>(name);
			}
			else
			{
				scriptEngine.Throw_ArgumentException("TPropertyType", "Unknown property type");
				return;
			}
		}

		void API_ShaderProperties::API_Get(Object& shaderPropertiesBase, int propertyIndex, MonoReflectionType* propertyType, MonoObject*& value)
		{
			using Class = EngineQ::Scripting::ScriptEngine::Class;

			auto& shaderProperties = static_cast<Graphics::ShaderProperties&>(shaderPropertiesBase);
			const auto& scriptEngine = shaderProperties.GetScriptEngine();

			MonoClass* propertyClass = scriptEngine.GetTypeClass(propertyType);

			if (propertyClass == scriptEngine.GetClass(Class::Float))
			{
				scriptEngine.GetValue<float>(value) = shaderProperties.Get<float>(propertyIndex);
			}
			else if (propertyClass == scriptEngine.GetClass(Class::Integer))
			{
				scriptEngine.GetValue<int>(value) = shaderProperties.Get<int>(propertyIndex);
			}
			else if (propertyClass == scriptEngine.GetClass(Class::Vector3f))
			{
				scriptEngine.GetValue<Math::Vector3f>(value) = shaderProperties.Get<Math::Vector3f>(propertyIndex);
			}
			else
			{
				scriptEngine.Throw_ArgumentException("TPropertyType", "Unknown property type");
				return;
			}
		}

		void API_ShaderProperties::API_Set(Object& shaderPropertiesBase, int propertyIndex, MonoReflectionType* propertyType, MonoObject*& value)
		{
			using Class = EngineQ::Scripting::ScriptEngine::Class;

			auto& shaderProperties = static_cast<Graphics::ShaderProperties&>(shaderPropertiesBase);
			const auto& scriptEngine = shaderProperties.GetScriptEngine();

			MonoClass* propertyClass = scriptEngine.GetTypeClass(propertyType);

			if (propertyClass == scriptEngine.GetClass(Class::Float))
			{
				shaderProperties.Set(propertyIndex, scriptEngine.GetValue<float>(value));
			}
			else if (propertyClass == scriptEngine.GetClass(Class::Integer))
			{
				shaderProperties.Set(propertyIndex, scriptEngine.GetValue<int>(value));
			}
			else if (propertyClass == scriptEngine.GetClass(Class::Vector3f))
			{
				shaderProperties.Set(propertyIndex, scriptEngine.GetValue<Math::Vector3f>(value));
			}
			else if (propertyClass == scriptEngine.GetClass(Class::Texture))
			{
				using ResourceType = Resources::Resource<Graphics::Texture>;

				auto controlBlock = static_cast<ResourceType::ControlBlock*>(reinterpret_cast<ResourceType::BaseControlBlock*>(scriptEngine.GetNativeHandle(value)));
				shaderProperties.Set(propertyIndex, controlBlock->GetResource());
			}
			else
			{
				scriptEngine.Throw_ArgumentException("TPropertyType", "Unknown property type");
				return;
			}
		}
	
		void API_ShaderProperties::API_Register(ScriptEngine& scriptEngine)
		{
			scriptEngine.API_Register("EngineQ.ShaderProperties::API_GetPropertyIndex", API_GetPropertyIndex);
			scriptEngine.API_Register("EngineQ.ShaderProperties::API_Get", API_Get);
			scriptEngine.API_Register("EngineQ.ShaderProperties::API_Set", API_Set);
		}
	}
}