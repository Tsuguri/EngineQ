#include "API_Scene.hpp"

#include "ScriptEngine.hpp"

#include "../Objects/Scene.hpp"
#include "../Objects/Entity.hpp"

namespace EngineQ
{
	namespace Scripting
	{
		void API_Scene::API_CreateEntity(Scene& scene, MonoObject*& entity)
		{
			entity = scene.CreateEntity()->GetManagedObject();
		}

		void API_Scene::API_RemoveEntityIndex(Scene& scene, std::int32_t  index)
		{
			scene.RemoveEntity(index);
		}

		void API_Scene::API_RemoveEntityRef(Scene& scene, MonoObject*& entity)
		{
			scene.RemoveEntity(static_cast<Entity*>(scene.GetScriptEngine().GetNativeHandle(entity)));
		}

		void API_Scene::API_GetEntityIndex(const Scene& scene, MonoObject*& entity, std::int32_t & index)
		{
			index = static_cast<std::int32_t >(scene.GetEntityIndex(static_cast<Entity*>(scene.GetScriptEngine().GetNativeHandle(entity))));
		}

		void API_Scene::API_GetEntity(const Scene& scene, std::int32_t  index, MonoObject*& entity)
		{
			entity = scene.GetEntity(index)->GetManagedObject();
		}

		void API_Scene::API_GetEntitiesCount(const Scene& scene, std::int32_t & count)
		{
			count = static_cast<std::int32_t >(scene.GetEntitiesCount());
		}
		
		void API_Scene::API_Register(ScriptEngine& scriptEngine)
		{
			scriptEngine.API_Register("EngineQ.Scene::API_CreateEntity", API_CreateEntity);
			scriptEngine.API_Register("EngineQ.Scene::API_RemoveEntityIndex", API_RemoveEntityIndex);
			scriptEngine.API_Register("EngineQ.Scene::API_RemoveEntityRef", API_RemoveEntityRef);
			scriptEngine.API_Register("EngineQ.Scene::API_GetEntityIndex", API_GetEntityIndex);
			scriptEngine.API_Register("EngineQ.Scene::API_GetEntity", API_GetEntity);
			scriptEngine.API_Register("EngineQ.Scene::API_GetEntitiesCount", API_GetEntitiesCount);
		}
	}
}