#ifndef ENGINEQ_SCRIPTING_API_COMPONENT_HPP
#define ENGINEQ_SCRIPTING_API_COMPONENT_HPP

#include "Types.hpp"
#include "../Objects/Types.hpp"

namespace EngineQ
{
	namespace Scripting
	{
		class API_Component
		{
		public:
			static void API_GetEntity(const Object& componentBase, MonoObject*& parent);
			static void API_GetEnabled(const Object& componentBase, bool& isEnabled);
			static void API_SetEnabled(Object& componentBase, bool isEnabled);
			static void API_GetEnabledInHierarchy(const Object& componentBase, bool& isEnabledInHierarchy);
			
			static void API_Register(ScriptEngine& scriptEngine);
		};
	}
}

#endif // !ENGINEQ_SCRIPTING_API_COMPONENT_HPP