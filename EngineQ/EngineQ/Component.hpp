#ifndef ENGINEQ_COMPONENT_H
#define ENGINEQ_COMPONENT_H

#include "Object.hpp"

namespace EngineQ
{
	class Entity;

	class Component : public Object
	{
	private:
		Entity& entity;

	public:
		Component(Scripting::ScriptEngine& scriptEngine, Scripting::ScriptClass sclass, Entity& entity);
		
		Entity& GetEntity();
		const Entity& GetEntity() const;
	};
}

#endif // !ENGINEQ_COMPONENT_H