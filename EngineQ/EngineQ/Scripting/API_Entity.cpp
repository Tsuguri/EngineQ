#include "API_Entity.hpp"

#include "ScriptEngine.hpp"

#include "../Objects/Scene.hpp"
#include "../Objects/Entity.hpp"
#include "../Objects/Transform.hpp"
#include "../Objects/Camera.hpp"
#include "../Objects/Light.hpp"
#include "../Objects/Renderable.hpp"
#include "../Objects/Script.hpp"

namespace EngineQ
{
	namespace Scripting
	{
		void API_Entity::API_GetScene(const Entity& entity, MonoObject*& scene)
		{
			scene = entity.GetScene().GetManagedObject();
		}

		void API_Entity::API_GetTransform(const Entity& entity, MonoObject*& transform)
		{
			transform = entity.GetTransform().GetManagedObject();
		}

		void API_Entity::API_GetComponentIndex(const Entity& entity, std::int32_t  index, MonoObject*& component)
		{
			component = entity.GetComponent(index)->GetManagedObject();
		}

		void API_Entity::API_GetComponentsCount(const Entity& entity, std::int32_t & count)
		{
			count = static_cast<std::int32_t>(entity.GetComponentsCount());
		}

		void API_Entity::API_GetComponentType(const Entity& entity, MonoReflectionType*& type, MonoObject*& component)
		{
			const ScriptEngine& scriptEngine = entity.GetScriptEngine();
			MonoClass* mclass = scriptEngine.GetTypeClass(type);

			for (std::size_t i = 0, count = entity.GetComponentsCount(); i < count; ++i)
			{
				Component* comp = entity.GetComponent(i);
				
				if (scriptEngine.IsDerrived(comp->GetManagedClass(), mclass))
				{
					component = comp->GetManagedObject();
					return;
				}
			}

			component = nullptr;
		}

		void API_Entity::API_AddComponent(Entity& entity, MonoReflectionType*& type, MonoObject*& component)
		{
			const ScriptEngine& scriptEngine = entity.GetScriptEngine();
			MonoClass* componentClass = scriptEngine.GetTypeClass(type);

			if (componentClass == scriptEngine.GetCameraClass())
			{
				component = entity.AddComponent<Camera>()->GetManagedObject();
			}
			else if (componentClass == scriptEngine.GetLightClass())
			{
				component = entity.AddComponent<Light>()->GetManagedObject();
			}
			else if (componentClass == scriptEngine.GetRenderableClass())
			{
				component = entity.AddComponent<Renderable>()->GetManagedObject();
			}
			else if (scriptEngine.IsScript(componentClass))
			{
				component = entity.AddScript(componentClass)->GetManagedObject();
			}
			else
			{
				scriptEngine.Throw_ArgumentException("TComponent", "Component must derive from Script class");
			}
		}

		void API_Entity::API_RemoveComponent(Entity& entity, MonoObject*& component)
		{
			const ScriptEngine& scriptEngine = entity.GetScriptEngine();

			try
			{
				entity.RemoveComponent(*static_cast<Component*>(scriptEngine.GetNativeHandle(component)));
			}
			catch (const std::exception& e)
			{
				scriptEngine.Throw_ArgumentException("component", e.what());
			}
		}

		void API_Entity::API_Register(ScriptEngine& scriptEngine)
		{
			scriptEngine.API_Register("EngineQ.Entity::API_GetScene", API_GetScene);
			scriptEngine.API_Register("EngineQ.Entity::API_GetTransform", API_GetTransform);
		
			scriptEngine.API_Register("EngineQ.Entity::API_GetComponentIndex", API_GetComponentIndex);
			scriptEngine.API_Register("EngineQ.Entity::API_GetComponentsCount", API_GetComponentsCount);
			scriptEngine.API_Register("EngineQ.Entity::API_GetComponentType", API_GetComponentType);
			scriptEngine.API_Register("EngineQ.Entity::API_AddComponent", API_AddComponent);
			scriptEngine.API_Register("EngineQ.Entity::API_RemoveComponent", API_RemoveComponent);
		}
	}
}