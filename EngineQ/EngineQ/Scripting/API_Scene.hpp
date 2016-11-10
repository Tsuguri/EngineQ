#ifndef ENGINEQ_SCRIPTING_API_SCENE_HPP
#define ENGINEQ_SCRIPTING_API_SCENE_HPP

#include "Types.hpp"
#include "../Objects/Types.hpp"

namespace EngineQ
{
	namespace Scripting
	{
		class API_Scene
		{
		public:
			static void API_FindEntity(Object& sceneBase, MonoString* name, MonoObject*& entity);
			static void API_CreateEntity(Object& sceneBase, bool enabled, MonoString* name, MonoObject*& entity);
			static void API_RemoveEntityIndex(Object& sceneBase, std::int32_t  index);
			static void API_RemoveEntityRef(Object& sceneBase, MonoObject*& entity);
			static void API_GetEntityIndex(const Object& sceneBase, MonoObject*& entity, std::int32_t & index);
			static void API_GetEntity(const Object& sceneBase, std::int32_t  index, MonoObject*& entity);
			static void API_GetEntitiesCount(const Object& sceneBase, std::int32_t & count);

			static void API_Register(ScriptEngine& scriptEngine);
		};
	}
}

#endif // !ENGINEQ_SCRIPTING_API_SCENE_HPP
