#include "API_ShaderProperties.hpp"

// Other projects
#include "EngineQCommon/Math/Vector3.hpp"
#include "EngineQCommon/Resources/Resource.hpp"

// This project
#include "ScriptEngine.hpp"
#include "EngineQ/EngineShaderProperties.hpp"


namespace EngineQ
{
	namespace Scripting
	{
		template<typename TResourceType>
		Resources::Resource<TResourceType> GetResource(const Scripting::ScriptEngine& scriptEngine, MonoObject* value)
		{
			using ResourceType = Resources::Resource<Graphics::Texture>;

			auto controlBlock = static_cast<ResourceType::ControlBlock*>(reinterpret_cast<ResourceType::BaseControlBlock*>(scriptEngine.GetNativeHandle(value)));

			if (controlBlock == nullptr)
				return ResourceType{};
			else
				return controlBlock->GetResource();
		}
		
		template<typename TResourceType>
		MonoObject* GetManagedResource(const Scripting::ScriptEngine& scriptEngine, ScriptEngine::Class resourceClass, const Resources::Resource<TResourceType>& resource)
		{
			auto scriptClass = scriptEngine.GetClass(resourceClass);

			if (resource == nullptr)
				return nullptr;
			
			return scriptEngine.CreateUnhandledObject(scriptClass, resource.GetControlBlock());
		}

		void API_ShaderProperties::API_GetShader(const Object& shaderPropertiesBase, MonoObject*& shader)
		{
			const auto& shaderProperties = static_cast<const EngineShaderProperties&>(shaderPropertiesBase);
			const auto& scriptEngine = shaderProperties.GetScriptEngine();

			shader = scriptEngine.CreateUnhandledObject(scriptEngine.GetClass(ScriptEngine::Class::Shader), shaderProperties.GetShader().GetControlBlock());
		}

		void API_ShaderProperties::API_GetPropertyIndex(Object& shaderPropertiesBase, MonoString* propertyName, MonoReflectionType* propertyType, int& propertyIndex)
		{
			using Class = EngineQ::Scripting::ScriptEngine::Class;

			auto& shaderProperties = static_cast<EngineShaderProperties&>(shaderPropertiesBase);
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

			auto& shaderProperties = static_cast<EngineShaderProperties&>(shaderPropertiesBase);
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

		void API_ShaderProperties::API_Set(Object& shaderPropertiesBase, int propertyIndex, MonoReflectionType* propertyType, MonoObject* const& value)
		{
			using Class = EngineQ::Scripting::ScriptEngine::Class;

			auto& shaderProperties = static_cast<EngineShaderProperties&>(shaderPropertiesBase);
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
				shaderProperties.Set(propertyIndex, GetResource<Graphics::Texture>(scriptEngine, value));	
			}
			else
			{
				scriptEngine.Throw_ArgumentException("TPropertyType", "Unknown property type");
				return;
			}
		}
		
		void API_ShaderProperties::API_GetAmbient(Object& shaderPropertiesBase, Math::Vector3f& ambient)
		{
			auto& shaderProperties = static_cast<EngineShaderProperties&>(shaderPropertiesBase);

			ambient = shaderProperties.GetMaterial().Ambient;
		}

		void API_ShaderProperties::API_SetAmbient(Object& shaderPropertiesBase, const Math::Vector3f& ambient)
		{
			auto& shaderProperties = static_cast<EngineShaderProperties&>(shaderPropertiesBase);

			shaderProperties.GetMaterial().Ambient = ambient;
		}

		void API_ShaderProperties::API_GetDiffuse(Object& shaderPropertiesBase, Math::Vector3f& diffuse)
		{
			auto& shaderProperties = static_cast<EngineShaderProperties&>(shaderPropertiesBase);

			diffuse = shaderProperties.GetMaterial().Diffuse;
		}

		void API_ShaderProperties::API_SetDiffuse(Object& shaderPropertiesBase, const Math::Vector3f& diffuse)
		{
			auto& shaderProperties = static_cast<EngineShaderProperties&>(shaderPropertiesBase);

			shaderProperties.GetMaterial().Diffuse = diffuse;
		}

		void API_ShaderProperties::API_GetSpecular(Object& shaderPropertiesBase, Math::Vector3f& specular)
		{
			auto& shaderProperties = static_cast<EngineShaderProperties&>(shaderPropertiesBase);

			specular = shaderProperties.GetMaterial().Specular;
		}

		void API_ShaderProperties::API_SetSpecular(Object& shaderPropertiesBase, const Math::Vector3f& specular)
		{
			auto& shaderProperties = static_cast<EngineShaderProperties&>(shaderPropertiesBase);

			shaderProperties.GetMaterial().Specular = specular;
		}

		void API_ShaderProperties::API_GetShininess(Object& shaderPropertiesBase, float& shininess)
		{
			auto& shaderProperties = static_cast<EngineShaderProperties&>(shaderPropertiesBase);

			shininess = shaderProperties.GetMaterial().Shininess;
		}

		void API_ShaderProperties::API_SetShininess(Object& shaderPropertiesBase, float shininess)
		{
			auto& shaderProperties = static_cast<EngineShaderProperties&>(shaderPropertiesBase);

			shaderProperties.GetMaterial().Shininess = shininess;
		}

		void API_ShaderProperties::API_GetDiffuseTexture(Object& shaderPropertiesBase, MonoObject*& diffuseTexture)
		{
			auto& shaderProperties = static_cast<EngineShaderProperties&>(shaderPropertiesBase);
			auto& scriptEngine = shaderProperties.GetScriptEngine();

			diffuseTexture = GetManagedResource(scriptEngine, ScriptEngine::Class::Texture, shaderProperties.GetMaterial().DiffuseTexture.Get());
		}

		void API_ShaderProperties::API_SetDiffuseTexture(Object& shaderPropertiesBase, MonoObject* diffuseTexture)
		{
			auto& shaderProperties = static_cast<EngineShaderProperties&>(shaderPropertiesBase);
			auto& scriptEngine = shaderProperties.GetScriptEngine();

			shaderProperties.GetMaterial().DiffuseTexture = GetResource<Graphics::Texture>(scriptEngine, diffuseTexture);
		}

		void API_ShaderProperties::API_GetSpecularTexture(Object& shaderPropertiesBase, MonoObject*& specularTexture)
		{
			auto& shaderProperties = static_cast<EngineShaderProperties&>(shaderPropertiesBase);
			auto& scriptEngine = shaderProperties.GetScriptEngine();

			specularTexture = GetManagedResource(scriptEngine, ScriptEngine::Class::Texture, shaderProperties.GetMaterial().SpecularTexture.Get());
		}

		void API_ShaderProperties::API_SetSpecularTexture(Object& shaderPropertiesBase, MonoObject* specularTexture)
		{
			auto& shaderProperties = static_cast<EngineShaderProperties&>(shaderPropertiesBase);
			auto& scriptEngine = shaderProperties.GetScriptEngine();

			shaderProperties.GetMaterial().SpecularTexture = GetResource<Graphics::Texture>(scriptEngine, specularTexture);
		}

		void API_ShaderProperties::API_GetNormalTexture(Object& shaderPropertiesBase, MonoObject*& normalTexture)
		{
			auto& shaderProperties = static_cast<EngineShaderProperties&>(shaderPropertiesBase);
			auto& scriptEngine = shaderProperties.GetScriptEngine();

			normalTexture = GetManagedResource(scriptEngine, ScriptEngine::Class::Texture, shaderProperties.GetMaterial().NormalTexture.Get());
		}

		void API_ShaderProperties::API_SetNormalTexture(Object& shaderPropertiesBase, MonoObject* normalTexture)
		{
			auto& shaderProperties = static_cast<EngineShaderProperties&>(shaderPropertiesBase);
			auto& scriptEngine = shaderProperties.GetScriptEngine();

			shaderProperties.GetMaterial().NormalTexture = GetResource<Graphics::Texture>(scriptEngine, normalTexture);
		}


		void API_ShaderProperties::API_Register(ScriptEngine& scriptEngine)
		{
			scriptEngine.API_Register("EngineQ.ShaderProperties::API_GetShader", API_GetShader);
			scriptEngine.API_Register("EngineQ.ShaderProperties::API_GetPropertyIndex", API_GetPropertyIndex);
			
			scriptEngine.API_Register("EngineQ.ShaderProperties::API_Get", API_Get);
			scriptEngine.API_Register("EngineQ.ShaderProperties::API_Set", API_Set);

			scriptEngine.API_Register("EngineQ.ShaderProperties::API_GetAmbient", API_GetAmbient);
			scriptEngine.API_Register("EngineQ.ShaderProperties::API_SetAmbient", API_SetAmbient);

			scriptEngine.API_Register("EngineQ.ShaderProperties::API_GetDiffuse", API_GetDiffuse);
			scriptEngine.API_Register("EngineQ.ShaderProperties::API_SetDiffuse", API_SetDiffuse);

			scriptEngine.API_Register("EngineQ.ShaderProperties::API_GetSpecular", API_GetSpecular);
			scriptEngine.API_Register("EngineQ.ShaderProperties::API_SetSpecular", API_SetSpecular);

			scriptEngine.API_Register("EngineQ.ShaderProperties::API_GetShininess", API_GetShininess);
			scriptEngine.API_Register("EngineQ.ShaderProperties::API_SetShininess", API_SetShininess);

			scriptEngine.API_Register("EngineQ.ShaderProperties::API_GetDiffuseTexture", API_GetDiffuseTexture);
			scriptEngine.API_Register("EngineQ.ShaderProperties::API_SetDiffuseTexture", API_SetDiffuseTexture);

			scriptEngine.API_Register("EngineQ.ShaderProperties::API_GetSpecularTexture", API_GetSpecularTexture);
			scriptEngine.API_Register("EngineQ.ShaderProperties::API_SetSpecularTexture", API_SetSpecularTexture);

			scriptEngine.API_Register("EngineQ.ShaderProperties::API_GetNormalTexture", API_GetNormalTexture);
			scriptEngine.API_Register("EngineQ.ShaderProperties::API_SetNormalTexture", API_SetNormalTexture);

		}
	}
}