#ifndef ENGINEQ_SCRIPTING_API_RESOURCE_MANAGER_HPP
#define ENGINEQ_SCRIPTING_API_RESOURCE_MANAGER_HPP

#include "Types.hpp"
#include "../Objects/Types.hpp"
#include <Resources/Resource.hpp>

namespace EngineQ
{
	namespace Scripting
	{
		class API_ResourceManager
		{
		public:
			static void API_GetInstance(MonoObject*& instance);
			static void API_IsResourceRegistered(Object& resourceMangerBase, MonoReflectionType* resourceType, MonoString* resourceId, bool& isRegistered);
			static void API_RegisterResource(Object& resourceMangerBase, MonoReflectionType* resourceType, MonoString* resourceId, MonoString* resourcePath);
			static void API_GetResource(Object& resourceMangerBase, MonoReflectionType* resourceType, MonoString* resourceId, MonoObject*& resourceObject);

			static void API_Register(ScriptEngine& scriptEngine);
		};
	}
}

#endif // !ENGINEQ_SCRIPTING_API_RESOURCE_MANAGER_HPP
