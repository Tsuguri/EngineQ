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
		void API_Entity::API_GetScene(const Object& entityBase, MonoObject*& scene)
		{
			const auto& entity = static_cast<const Entity&>(entityBase);

			scene = entity.GetScene().GetManagedObject();
		}

		void API_Entity::API_GetTransform(const Object& entityBase, MonoObject*& transform)
		{
			const auto& entity = static_cast<const Entity&>(entityBase);
			
			transform = entity.GetTransform().GetManagedObject();
		}

		void API_Entity::API_GetComponentIndex(const Object& entityBase, std::int32_t  index, MonoObject*& component)
		{
			const auto& entity = static_cast<const Entity&>(entityBase);
			
			component = entity.GetComponent(index).GetManagedObject();
		}

		void API_Entity::API_GetComponentsCount(const Object& entityBase, std::int32_t & count)
		{
			const auto& entity = static_cast<const Entity&>(entityBase);

			count = static_cast<std::int32_t>(entity.GetComponentsCount());
		}

		void API_Entity::API_GetComponentType(const Object& entityBase, MonoReflectionType*& type, MonoObject*& component)
		{
			const auto& entity = static_cast<const Entity&>(entityBase);

			const ScriptEngine& scriptEngine = entity.GetScriptEngine();
			MonoClass* mclass = scriptEngine.GetTypeClass(type);

			for (std::size_t i = 0, count = entity.GetComponentsCount(); i < count; ++i)
			{
				Component& nativeComponent = entity.GetComponent(i);
				
				if (scriptEngine.IsDerrived(nativeComponent.GetManagedClass(), mclass))
				{
					component = nativeComponent.GetManagedObject();
					return;
				}
			}

			component = nullptr;
		}

		void API_Entity::API_AddComponent(Object& entityBase, MonoReflectionType*& type, bool enabled, MonoObject*& component)
		{
			auto& entity = static_cast<Entity&>(entityBase);

			const ScriptEngine& scriptEngine = entity.GetScriptEngine();
			MonoClass* componentClass = scriptEngine.GetTypeClass(type);

			if (componentClass == scriptEngine.GetClass(Scripting::ScriptEngine::Class::Camera))
			{
				component = entity.AddComponent<Camera>(enabled).GetManagedObject();
			}
			else if (componentClass == scriptEngine.GetClass(Scripting::ScriptEngine::Class::Light))
			{
				component = entity.AddComponent<Light>(enabled).GetManagedObject();
			}
			else if (componentClass == scriptEngine.GetClass(Scripting::ScriptEngine::Class::Renderable))
			{
				component = entity.AddComponent<Renderable>(enabled).GetManagedObject();
			}
			else if (scriptEngine.IsScript(componentClass))
			{
				component = entity.AddScript(componentClass, enabled).GetManagedObject();
			}
			else
			{
				scriptEngine.Throw_ArgumentException("TComponent", "Component must derive from Script class");
			}
		}

		void API_Entity::API_RemoveComponent(Object& entityBase, MonoObject*& component)
		{
			auto& entity = static_cast<Entity&>(entityBase);
			
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

		void API_Entity::API_GetEnabled(const Object& entityBase, bool& enabled)
		{
			const auto& entity = static_cast<const Entity&>(entityBase);

			enabled = entity.IsEnabled();
		}

		void API_Entity::API_SetEnabled(Object& entityBase, bool enabled)
		{
			auto& entity = static_cast<Entity&>(entityBase);

			entity.SetEnabled(enabled);
		}

		void API_Entity::API_GetEnabledInHierarchy(const Object& entityBase, bool& enabledInHierarchy)
		{
			const auto& entity = static_cast<const Entity&>(entityBase);

			enabledInHierarchy = entity.IsEnabledInHierarchy();
		}

		void API_Entity::API_GetName(const Object& entityBase, MonoString*& name)
		{
			const auto& entity = static_cast<const Entity&>(entityBase);

			const ScriptEngine& scriptEngine = entity.GetScriptEngine();

			name = scriptEngine.CreateScriptString(entity.GetName());
		}

		void API_Entity::API_SetName(Object& entityBase, MonoString* name)
		{
			auto& entity = static_cast<Entity&>(entityBase);

			const ScriptEngine& scriptEngine = entity.GetScriptEngine();
			
			entity.SetName(scriptEngine.GetScriptStringContent(name));
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

			scriptEngine.API_Register("EngineQ.Entity::API_GetEnabled", API_GetEnabled);
			scriptEngine.API_Register("EngineQ.Entity::API_SetEnabled", API_SetEnabled);
			scriptEngine.API_Register("EngineQ.Entity::API_GetEnabledInHierarchy", API_GetEnabledInHierarchy);
			scriptEngine.API_Register("EngineQ.Entity::API_GetName", API_GetName);
			scriptEngine.API_Register("EngineQ.Entity::API_SetName", API_SetName);
		}
	}
}