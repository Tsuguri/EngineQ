#ifndef ENGINEQ_SCRIPTING_API_ENTITY_H
#define ENGINEQ_SCRIPTING_API_ENTITY_H

#include "ScriptEngine.hpp"

namespace EngineQ
{
	namespace Scripting
	{
		class API_Entity
		{
		public:
			static void API_GetTransform(const Entity& entity, MonoObject*& transform);
			
			static void API_GetComponentIndex(const Entity& entity, int index, MonoObject*& component);
			static void API_GetComponentsCount(const Entity& entity, int& count);
			static void API_GetComponentType(const Entity& entity, MonoReflectionType*& type, MonoObject*& component);
			static void API_AddScript(Entity& entity, MonoReflectionType*& type, MonoObject*& script);

			static void API_Register(ScriptEngine& scriptEngine);
		};
	}
}

#endif // !ENGINEQ_SCRIPTING_API_ENTITY_H