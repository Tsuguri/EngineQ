#ifndef ENGINEQ_COMPONENT_HPP
#define ENGINEQ_COMPONENT_HPP

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
		Renderable,
	};

	class Component : public Object
	{
	private:
		Entity& entity;

	public:
	#pragma region Serialization

		Component(Serialization::Deserializer& deserialzier);
		virtual void Serialize(Serialization::Serializer& serializer) const override;

	#pragma endregion

		Component(Scripting::ScriptEngine& scriptEngine, Scripting::ScriptClass sclass, Entity& entity);
		
		Entity& GetEntity();
		const Entity& GetEntity() const;

		virtual ComponentType GetType() const = 0;
	};
}

#endif // !ENGINEQ_COMPONENT_HPP
