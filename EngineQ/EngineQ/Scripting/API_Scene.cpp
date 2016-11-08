#include "API_Scene.hpp"

#include "ScriptEngine.hpp"

#include "../Objects/Scene.hpp"
#include "../Objects/Entity.hpp"

namespace EngineQ
{
	namespace Scripting
	{
		void API_Scene::API_FindEntity(Object& sceneBase, MonoString* name, MonoObject*& entity)
		{
			auto& scene = static_cast<Scene&>(sceneBase);

			const auto& scriptEngine = scene.GetScriptEngine();

			auto nativeEntity = scene.FindEntity(scriptEngine.GetScriptStringContent(name));
			
			entity = (nativeEntity == nullptr ? nullptr : nativeEntity->GetManagedObject());
		}

		void API_Scene::API_CreateEntity(Object& sceneBase, MonoObject*& entity)
		{
			auto& scene = static_cast<Scene&>(sceneBase);

			entity = scene.CreateEntity().GetManagedObject();
		}

		void API_Scene::API_RemoveEntityIndex(Object& sceneBase, std::int32_t  index)
		{
			auto& scene = static_cast<Scene&>(sceneBase);

			scene.RemoveEntity(index);
		}

		void API_Scene::API_RemoveEntityRef(Object& sceneBase, MonoObject*& entity)
		{
			auto& scene = static_cast<Scene&>(sceneBase);

			scene.RemoveEntity(*static_cast<Entity*>(scene.GetScriptEngine().GetNativeHandle(entity)));
		}

		void API_Scene::API_GetEntityIndex(const Object& sceneBase, MonoObject*& entity, std::int32_t & index)
		{
			const auto& scene = static_cast<const Scene&>(sceneBase);

			index = static_cast<std::int32_t>(scene.GetEntityIndex(*static_cast<Entity*>(scene.GetScriptEngine().GetNativeHandle(entity))));
		}

		void API_Scene::API_GetEntity(const Object& sceneBase, std::int32_t  index, MonoObject*& entity)
		{
			const auto& scene = static_cast<const Scene&>(sceneBase);

			entity = scene.GetEntity(index).GetManagedObject();
		}

		void API_Scene::API_GetEntitiesCount(const Object& sceneBase, std::int32_t & count)
		{
			const auto& scene = static_cast<const Scene&>(sceneBase);

			count = static_cast<std::int32_t>(scene.GetEntitiesCount());
		}

		void API_Scene::API_Register(ScriptEngine& scriptEngine)
		{
			scriptEngine.API_Register("EngineQ.Scene::API_FindEntity", API_FindEntity);
			scriptEngine.API_Register("EngineQ.Scene::API_CreateEntity", API_CreateEntity);
			scriptEngine.API_Register("EngineQ.Scene::API_RemoveEntityIndex", API_RemoveEntityIndex);
			scriptEngine.API_Register("EngineQ.Scene::API_RemoveEntityRef", API_RemoveEntityRef);
			scriptEngine.API_Register("EngineQ.Scene::API_GetEntityIndex", API_GetEntityIndex);
			scriptEngine.API_Register("EngineQ.Scene::API_GetEntity", API_GetEntity);
			scriptEngine.API_Register("EngineQ.Scene::API_GetEntitiesCount", API_GetEntitiesCount);
		}
	}
}