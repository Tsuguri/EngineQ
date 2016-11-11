#ifndef ENGINEQ_SCRIPTING_API_ENTITY_HPP
#define ENGINEQ_SCRIPTING_API_ENTITY_HPP

#include "Types.hpp"
#include "../Objects/Types.hpp"

namespace EngineQ
{
	namespace Scripting
	{
		class API_Entity
		{
		public:
			static void API_GetScene(const Object& entityBase, MonoObject*& scene);
			static void API_GetTransform(const Object& entityBase, MonoObject*& transform);
			
			static void API_GetComponentIndex(const Object& entityBase, std::int32_t index, MonoObject*& component);
			static void API_GetComponentsCount(const Object& entityBase, std::int32_t & count);
			static void API_GetComponentType(const Object& entityBase, MonoReflectionType*& type, MonoObject*& component);
			static void API_AddComponent(Object& entityBase, MonoReflectionType*& type, bool enabled, MonoObject*& component);
			static void API_RemoveComponent(Object& entityBase, MonoObject*& component);

			static void API_GetEnabled(const Object& entityBase, bool& enabled);
			static void API_SetEnabled(Object& entityBase, bool enabled);
			static void API_GetEnabledInHierarchy(const Object& entityBase, bool& enabledInHierarchy);
			static void API_GetName(const Object& entityBase, MonoString*& name);
			static void API_SetName(Object& entityBase, MonoString* name);
			
			static void API_Register(ScriptEngine& scriptEngine);
		};
	}
}

#endif // !ENGINEQ_SCRIPTING_API_ENTITY_HPP
