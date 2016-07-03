#include "Component.hpp"

namespace EngineQ
{
	Component::Component(Scripting::ScriptEngine& scriptEngine, Scripting::ScriptClass sclass, Entity& entity)
		: Object{ scriptEngine, sclass }, entity{ entity }
	{
	}

	Entity& Component::GetEntity()
	{
		return this->entity;
	}

	const Entity& Component::GetEntity() const
	{
		return this->entity;
	}
}