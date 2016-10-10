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
			static void API_GetScene(const Entity& entity, MonoObject*& scene);
			static void API_GetTransform(const Entity& entity, MonoObject*& transform);
			
			static void API_GetComponentIndex(const Entity& entity, std::int32_t index, MonoObject*& component);
			static void API_GetComponentsCount(const Entity& entity, std::int32_t & count);
			static void API_GetComponentType(const Entity& entity, MonoReflectionType*& type, MonoObject*& component);
			static void API_AddComponent(Entity& entity, MonoReflectionType*& type, MonoObject*& component);
			static void API_RemoveComponent(Entity& entity, MonoObject*& component);

			static void API_Register(ScriptEngine& scriptEngine);
		};
	}
}

#endif // !ENGINEQ_SCRIPTING_API_ENTITY_HPP
