#ifndef ENGINEQ_SCRIPTING_API_COMPONENT_H
#define ENGINEQ_SCRIPTING_API_COMPONENT_H

#include "ScriptEngine.hpp"
#include "../Component.hpp"

namespace EngineQ
{
	namespace Scripting
	{
		class API_Component
		{
		public:
			static void API_GetEntity(const Component& component, MonoObject*& parent);

			static void API_Register(ScriptEngine& scriptEngine);
		};
	}
}

#endif // !ENGINEQ_SCRIPTING_API_COMPONENT_H