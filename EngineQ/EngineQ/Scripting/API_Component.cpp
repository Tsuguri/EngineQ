#include "API_Component.hpp"

// This project
#include "Types.hpp"
#include "ScriptEngine.hpp"
#include "EngineQ/Objects/Component.hpp"
#include "EngineQ/Objects/Entity.hpp"


namespace EngineQ
{
	namespace Scripting
	{
		void API_Component::API_GetEntity(const Object& componentBase, MonoObject*& parent)
		{
			const auto& component = static_cast<const Component&>(componentBase);

			parent = component.GetEntity().GetManagedObject();
		}

		void API_Component::API_GetEnabled(const Object& componentBase, bool& isEnabled)
		{
			const auto& component = static_cast<const Component&>(componentBase);

			isEnabled = component.IsEnabled();
		}

		void API_Component::API_SetEnabled(Object& componentBase, bool isEnabled)
		{
			auto& component = static_cast<Component&>(componentBase);

			component.SetEnabled(isEnabled);
		}

		void API_Component::API_GetEnabledInHierarchy(const Object& componentBase, bool& isEnabledInHierarchy)
		{
			const auto& component = static_cast<const Component&>(componentBase);
			
			isEnabledInHierarchy = component.IsEnabledInHierarchy();
		}

		void API_Component::API_Register(ScriptEngine& scriptEngine)
		{
			scriptEngine.API_Register("EngineQ.Component::API_GetEntity", API_GetEntity);
			scriptEngine.API_Register("EngineQ.Component::API_GetEnabled", API_GetEnabled);
			scriptEngine.API_Register("EngineQ.Component::API_SetEnabled", API_SetEnabled);
			scriptEngine.API_Register("EngineQ.Component::API_GetEnabledInHierarchy", API_GetEnabledInHierarchy);
		}
	}
}