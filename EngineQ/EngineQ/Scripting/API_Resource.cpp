#include "API_Resource.hpp"

#include "ScriptEngine.hpp"

namespace EngineQ
{
	namespace Scripting
	{
		void API_Resource::API_IncRefCounter(Resources::BaseResource::BaseControlBlock* resource)
		{
			Resources::BaseResource::BaseControlBlock::AddManagedReference(resource);
		}

		void API_Resource::API_DecRefCounter(Resources::BaseResource::BaseControlBlock* resource)
		{
			Resources::BaseResource::BaseControlBlock::RemoveManagedReference(resource);
		}

		void API_Resource::API_Register(ScriptEngine& scriptEngine)
		{
			scriptEngine.API_Register("EngineQ.Resource::API_IncRefCounter", API_IncRefCounter);
			scriptEngine.API_Register("EngineQ.Resource::API_DecRefCounter", API_DecRefCounter);
		}
	}
}