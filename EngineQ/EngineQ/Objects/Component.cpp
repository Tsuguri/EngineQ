#include "Component.hpp"

#include "Entity.hpp"

#include "../Serialization/Serializer.hpp"
#include "../Serialization/Deserializer.hpp"

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

	Component::Component(ComponentType type, Scripting::ScriptEngine& scriptEngine, Scripting::ScriptClass sclass, Entity& entity)
		: Object{ scriptEngine, sclass }, entity{ entity }, type{ type }
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

	ComponentType Component::GetType() const
	{
		return this->type;
	}

	void Component::SetParentEnabled(bool enabled)
	{
		this->parentEnabled = enabled;
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
	}

	bool Component::IsEnabledInHierarchy() const
	{
		return this->enabled && this->parentEnabled;
	}
}