#include "API_Entity.hpp"

#include "../Entity.hpp"
#include "../Transform.hpp"

namespace EngineQ
{
	namespace Scripting
	{
		void API_Entity::API_GetTransform(const Entity& entity, MonoObject*& transform)
		{
			transform = entity.GetTransform().GetManagedObject();
		}

		void API_Entity::API_GetComponentIndex(const Entity& entity, int index, MonoObject*& component)
		{
			component = entity.GetComponent(index)->GetManagedObject();
		}

		void API_Entity::API_GetComponentsCount(const Entity& entity, int& count)
		{
			count = entity.GetComponentsCount();
		}

		void API_Entity::API_GetComponentType(const Entity& entity, MonoReflectionType*& type, MonoObject*& component)
		{
			MonoClass* mclass = entity.GetScriptEngine().GetTypeClass(type);

			for (int i = 0, count = entity.GetComponentsCount(); i < count; ++i)
			{
				Component* comp = entity.GetComponent(i);
				
				if (comp->GetManagedClass() == mclass)
				{
					component = comp->GetManagedObject();
					return;
				}
			}
		}

		void API_Entity::API_AddScript(Entity& entity, MonoReflectionType*& type, MonoObject*& script)
		{
			script = entity.AddScript(entity.GetScriptEngine().GetTypeClass(type))->GetManagedObject();
		}

		void API_Entity::API_Register(ScriptEngine& scriptEngine)
		{
			scriptEngine.API_Register("EngineQ.Entity::API_GetTransform", API_GetTransform);
		
			scriptEngine.API_Register("EngineQ.Entity::API_GetComponentIndex", API_GetComponentIndex);
			scriptEngine.API_Register("EngineQ.Entity::API_GetComponentsCount", API_GetComponentsCount);
			scriptEngine.API_Register("EngineQ.Entity::API_GetComponentType", API_GetComponentType);
			scriptEngine.API_Register("EngineQ.Entity::API_AddScript", API_AddScript);
		}
	}
}