#include "API_ResourceManager.hpp"

#include "ScriptEngine.hpp"
#include "../Resources/ResourceManager.hpp"
#include "../Engine.hpp"

namespace EngineQ
{
	namespace Scripting
	{
		void API_ResourceManager::API_GetInstance(MonoObject*& instance)
		{
			instance = EngineQ::Engine::Get().GetResourceManager().GetManagedObject();
		}

		void API_ResourceManager::API_GetResource(Object& resourceMangerBase, MonoReflectionType* resourceType, MonoString* resourceId, Resources::BaseResource::BaseControlBlock*& controlBlock)
		{
			auto& resourceManager = static_cast<Resources::ResourceManager&>(resourceMangerBase);
			const auto& scriptEngine = resourceManager.GetScriptEngine();

			MonoClass* resourceClass = scriptEngine.GetTypeClass(resourceType);

			std::string resourceIdString = scriptEngine.GetScriptStringContent(resourceId);

			if (resourceClass == scriptEngine.GetClass(ScriptEngine::Class::Shader))
			{
				controlBlock = resourceManager.GetResource<Graphics::Shader>(resourceIdString).GetControlBlock();
			}
			else if (resourceClass == scriptEngine.GetClass(ScriptEngine::Class::Texture))
			{
				controlBlock = resourceManager.GetResource<Graphics::Texture>(resourceIdString).GetControlBlock();
			}
			else
			{
				scriptEngine.Throw_ArgumentException("TResourceType", "Not supported resource type");
			}
		}

		void API_ResourceManager::API_Register(ScriptEngine& scriptEngine)
		{
			scriptEngine.API_Register("EngineQ.ResourceManager::API_GetInstance", API_GetInstance);
			scriptEngine.API_Register("EngineQ.ResourceManager::API_GetResource", API_GetResource);
		}
	}
}