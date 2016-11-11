#include "API_Scene.hpp"

#include "ScriptEngine.hpp"

#include "../Objects/Scene.hpp"
#include "../Objects/Entity.hpp"
#include "../Objects/Camera.hpp"

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

		void API_Scene::API_CreateEntity(Object& sceneBase, bool enabled, MonoString* name, MonoObject*& entity)
		{
			auto& scene = static_cast<Scene&>(sceneBase);
			auto& scriptEngine = scene.GetScriptEngine();

			entity = scene.CreateEntity(enabled, scriptEngine.GetScriptStringContent(name)).GetManagedObject();
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

		void API_Scene::API_GetActiveCamera(const Object& sceneBase, MonoObject*& camera)
		{
			auto& scene = static_cast<const Scene&>(sceneBase);

			auto activeCamera = scene.GetActiveCamera();
			if (activeCamera != nullptr)
				camera = activeCamera->GetManagedObject();
			else
				camera = nullptr;
		}

		void API_Scene::API_SetActiveCamera(Object& sceneBase, MonoObject* camera)
		{
			auto& scene = static_cast<Scene&>(sceneBase);

			if (camera != nullptr)
				scene.SetActiveCamera(static_cast<Camera*>(scene.GetScriptEngine().GetNativeHandle(camera)));
			else
				scene.SetActiveCamera(nullptr);
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
			scriptEngine.API_Register("EngineQ.Scene::API_GetActiveCamera", API_GetActiveCamera);
			scriptEngine.API_Register("EngineQ.Scene::API_SetActiveCamera", API_SetActiveCamera);
		}
	}
}