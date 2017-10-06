#ifndef ENGINEQ_SCRIPTING_API_RESOURCE_HPP
#define ENGINEQ_SCRIPTING_API_RESOURCE_HPP

// Other projects
#include "EngineQCommon/Resources/Resource.hpp"

// This project
#include "Types.hpp"
#include "EngineQ/Objects/Types.hpp"


namespace EngineQ
{
	namespace Scripting
	{
		class API_Resource
		{
		public:
			static void API_IncRefCounter(Resources::BaseResource::BaseControlBlock* resource);
			static void API_DecRefCounter(Resources::BaseResource::BaseControlBlock* resource);

			static void API_Register(ScriptEngine& scriptEngine);
		};
	}
}

#endif // !ENGINEQ_SCRIPTING_API_RESOURCE_HPP
