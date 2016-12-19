#ifndef ENGINEQ_COMPONENT_HPP
#define ENGINEQ_COMPONENT_HPP

// This project
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
		friend class Entity;

	protected:
		Entity& entity;

	private:
		bool enabled = true;
		bool parentEnabled = true;

		void SetParentEnabled(bool enabled);

		const ComponentType type;

	public:
		/*
	#pragma region Serialization

		Component(Serialization::Deserializer& deserialzier, ComponentType type);
		virtual void Serialize(Serialization::Serializer& serializer) const override;

	#pragma endregion
		*/

		Component(ComponentType type, Scripting::ScriptEngine& scriptEngine, Scripting::ScriptClass sclass, Entity& entity, bool enabled);
		virtual ~Component();
		
		Entity& GetEntity();
		const Entity& GetEntity() const;

		bool IsEnabled() const;
		void SetEnabled(bool enabled);

		bool IsEnabledInHierarchy() const;

		ComponentType GetType() const;

	protected:
		virtual void OnEnabledChanged(bool enabled);
	};
}

#endif // !ENGINEQ_COMPONENT_HPP
