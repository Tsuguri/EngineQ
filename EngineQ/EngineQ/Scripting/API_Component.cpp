#include "API_Component.hpp"

#include "Types.hpp"

#include "ScriptEngine.hpp"

#include "../Objects/Component.hpp"
#include "../Objects/Entity.hpp"

namespace EngineQ
{
	namespace Scripting
	{
		void API_Component::API_GetEntity(const Component& component, MonoObject*& parent)
		{
			parent = component.GetEntity().GetManagedObject();
		}

		void API_Component::API_Register(ScriptEngine& scriptEngine)
		{
			scriptEngine.API_Register("EngineQ.Component::API_GetEntity", API_GetEntity);
		}
	}
}