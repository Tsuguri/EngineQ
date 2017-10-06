#include "API_ResourceManager.hpp"

// This project
#include "ScriptEngine.hpp"
#include "EngineQ/Resources/ResourceManager.hpp"
#include "EngineQ/Engine.hpp"


namespace EngineQ
{
	namespace Scripting
	{
		void API_ResourceManager::API_GetInstance(MonoObject*& instance)
		{
			instance = EngineQ::Engine::Get().GetResourceManager().GetManagedObject();
		}

		void API_ResourceManager::API_IsResourceRegistered(Object& resourceMangerBase, MonoReflectionType* resourceType, MonoString* resourceId, bool& isRegistered)
		{
			using Class = ScriptEngine::Class;

			auto& resourceManager = static_cast<Resources::ResourceManager&>(resourceMangerBase);
			const auto& scriptEngine = resourceManager.GetScriptEngine();

			MonoClass* resourceClass = scriptEngine.GetTypeClass(resourceType);

			std::string resourceIdString = scriptEngine.GetScriptStringContent(resourceId);

			if (resourceClass == scriptEngine.GetClass(Class::Shader))
			{
				isRegistered = resourceManager.IsResourceRegistered<Graphics::Shader>(resourceIdString);
			}
			else if (resourceClass == scriptEngine.GetClass(Class::Texture))
			{
				isRegistered = resourceManager.IsResourceRegistered<Graphics::Texture>(resourceIdString);
			}
			else if (resourceClass == scriptEngine.GetClass(Class::Model))
			{
				isRegistered = resourceManager.IsResourceRegistered<Resources::Model>(resourceIdString);
			}
			else if (resourceClass == scriptEngine.GetClass(Class::Mesh))
			{
				isRegistered = resourceManager.IsResourceRegistered<Graphics::Mesh>(resourceIdString);
			}
			else
			{
				scriptEngine.Throw_ArgumentException("TResourceType", "Not supported resource type");
				return;
			}

			isRegistered = false;
		}

		void API_ResourceManager::API_RegisterResource(Object& resourceMangerBase, MonoReflectionType* resourceType, MonoString* resourceId, MonoString* resourcePath)
		{
			using Class = ScriptEngine::Class;

			auto& resourceManager = static_cast<Resources::ResourceManager&>(resourceMangerBase);
			const auto& scriptEngine = resourceManager.GetScriptEngine();

			MonoClass* resourceClass = scriptEngine.GetTypeClass(resourceType);

			std::string resourceIdString = scriptEngine.GetScriptStringContent(resourceId);
			std::string resourcePathString = scriptEngine.GetScriptStringContent(resourcePath);

			if (resourceClass == scriptEngine.GetClass(Class::Shader))
			{
				resourceManager.RegisterResource<Graphics::Shader>(resourceIdString, resourcePathString.c_str());
			}
			else if (resourceClass == scriptEngine.GetClass(Class::Texture))
			{
				resourceManager.RegisterResource<Graphics::Texture>(resourceIdString, resourcePathString.c_str());
			}
			else if (resourceClass == scriptEngine.GetClass(Class::Model))
			{
				resourceManager.RegisterResource<Resources::Model>(resourceIdString, resourcePathString.c_str());
			}
			else if (resourceClass == scriptEngine.GetClass(Class::Mesh))
			{
				resourceManager.RegisterResource<Graphics::Mesh>(resourceIdString, resourcePathString.c_str());
			}
			else
			{
				scriptEngine.Throw_ArgumentException("TResourceType", "Not supported resource type");
				return;
			}
		}

		void API_ResourceManager::API_GetResource(Object& resourceMangerBase, MonoReflectionType* resourceType, MonoString* resourceId, MonoObject*& resourceObject)
		{
			using Class = ScriptEngine::Class;

			auto& resourceManager = static_cast<Resources::ResourceManager&>(resourceMangerBase);
			const auto& scriptEngine = resourceManager.GetScriptEngine();

			MonoClass* resourceClass = scriptEngine.GetTypeClass(resourceType);

			std::string resourceIdString = scriptEngine.GetScriptStringContent(resourceId);

			void* controlBlock;
			if (resourceClass == scriptEngine.GetClass(Class::Shader))
			{
				controlBlock = resourceManager.GetResource<Graphics::Shader>(resourceIdString).GetControlBlock();
			}
			else if (resourceClass == scriptEngine.GetClass(Class::Texture))
			{
				controlBlock = resourceManager.GetResource<Graphics::Texture>(resourceIdString).GetControlBlock();
			}
			else if (resourceClass == scriptEngine.GetClass(Class::Model))
			{
				controlBlock = resourceManager.GetResource<Resources::Model>(resourceIdString).GetControlBlock();
			}
			else if (resourceClass == scriptEngine.GetClass(Class::Mesh))
			{
				controlBlock = resourceManager.GetResource<Graphics::Mesh>(resourceIdString).GetControlBlock();
			}
			else
			{
				scriptEngine.Throw_ArgumentException("TResourceType", "Not supported resource type");
				return;
			}

			resourceObject = scriptEngine.CreateUnhandledObject(resourceClass, controlBlock);
		}

		void API_ResourceManager::API_Register(ScriptEngine& scriptEngine)
		{
			scriptEngine.API_Register("EngineQ.ResourceManager::API_GetInstance", API_GetInstance);
			scriptEngine.API_Register("EngineQ.ResourceManager::API_IsResourceRegistered", API_IsResourceRegistered);
			scriptEngine.API_Register("EngineQ.ResourceManager::API_RegisterResource", API_RegisterResource);
			scriptEngine.API_Register("EngineQ.ResourceManager::API_GetResource", API_GetResource);
		}
	}
}