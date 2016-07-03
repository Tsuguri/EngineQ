#include "Light.hpp"

namespace EngineQ
{
	Light::Light(Scripting::ScriptEngine& scriptEngine, Entity& entity)
		: Component{scriptEngine, scriptEngine.GetLightClass(), entity }
	{

	}

	ComponentType Light::GetType() const
	{
		return ComponentType::Light;
	}
}