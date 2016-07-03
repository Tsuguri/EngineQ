#ifndef ENGINEQ_COMPONENT_H
#define ENGINEQ_COMPONENT_H

#include "Object.hpp"

namespace EngineQ
{
	class Entity;

	enum class ComponentType
	{
		Transform,
		Camera,
		Light,
		Script,
	};

	class Component : public Object
	{
	private:
		Entity& entity;

	public:
		Component(Scripting::ScriptEngine& scriptEngine, Scripting::ScriptClass sclass, Entity& entity);
		
		Entity& GetEntity();
		const Entity& GetEntity() const;

		virtual ComponentType GetType() const = 0;
	};
}

#endif // !ENGINEQ_COMPONENT_H