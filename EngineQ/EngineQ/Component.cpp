#include "Component.hpp"

#include "Entity.hpp"
#include "Serialization/SerializationRules.hpp"

namespace EngineQ
{
#pragma region Serialization

	Component::Component(Serialization::Deserializer& deserialzier) :
		Object{deserialzier},
		entity{*deserialzier.GetReference<Entity>("entity")}
	{
	}
	
	void Component::Serialize(Serialization::Serializer& serializer) const
	{
		Object::Serialize(serializer);
		serializer.StoreReference("entity", &this->entity);
	}

#pragma endregion

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