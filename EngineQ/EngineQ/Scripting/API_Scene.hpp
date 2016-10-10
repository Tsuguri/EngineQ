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
			static void API_CreateEntity(Scene& scene, MonoObject*& entity);
			static void API_RemoveEntityIndex(Scene& scene, std::int32_t  index);
			static void API_RemoveEntityRef(Scene& scene, MonoObject*& entity);
			static void API_GetEntityIndex(const Scene& scene, MonoObject*& entity, std::int32_t & index);
			static void API_GetEntity(const Scene& scene, std::int32_t  index, MonoObject*& entity);
			static void API_GetEntitiesCount(const Scene& scene, std::int32_t & count);

			static void API_Register(ScriptEngine& scriptEngine);
		};
	}
}

#endif // !ENGINEQ_SCRIPTING_API_SCENE_HPP
