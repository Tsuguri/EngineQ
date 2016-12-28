#include "Component.hpp"

// This project
#include "Entity.hpp"
#include "EngineQ/Serialization/Serializer.hpp"
#include "EngineQ/Serialization/Deserializer.hpp"
#include "EngineQ/Systems/Logger.hpp"


namespace EngineQ
{
	/*
#pragma region Serialization

	Component::Component(Serialization::Deserializer& deserialzier, ComponentType type) :
		Object{ deserialzier },
		entity{ *deserialzier.GetReference<Entity>("entity") },
		type{ type }
	{
	}

	void Component::Serialize(Serialization::Serializer& serializer) const
	{
		Object::Serialize(serializer);
		serializer.StoreReference("entity", &this->entity);
	}

#pragma endregion
	*/


	Component::Component(ComponentType type, Scripting::ScriptEngine& scriptEngine, Scripting::ScriptClass sclass, Entity& entity, bool enabled)
		: Object{ scriptEngine, sclass }, entity{ entity }, enabled{ enabled }, parentEnabled{ entity.IsEnabledInHierarchy() }, type{ type }
	{
	}

	Component::~Component()
	{
		Logger::LogMessage("  Destroying component of type ", static_cast<int>(this->type), "\n");
	}
	
	Entity& Component::GetEntity()
	{
		return this->entity;
	}

	const Entity& Component::GetEntity() const
	{
		return this->entity;
	}

	ComponentType Component::GetType() const
	{
		return this->type;
	}

	void Component::SetParentEnabled(bool enabled)
	{
		if (this->parentEnabled == enabled)
			return;

		this->parentEnabled = enabled;

		if (this->enabled)
			this->OnEnabledChanged(enabled);
	}

	bool Component::IsEnabled() const
	{
		return this->enabled;
	}

	void Component::SetEnabled(bool enabled)
	{
		if (this->enabled == enabled)
			return;

		this->enabled = enabled;

		Entity::ComponentCallbacks::OnEnabledChanged(entity, *this, this->enabled);

		if (this->parentEnabled)
			this->OnEnabledChanged(enabled);
	}

	bool Component::IsEnabledInHierarchy() const
	{
		return this->enabled && this->parentEnabled;
	}

	void Component::OnEnabledChanged(bool enabled)
	{
	}
}