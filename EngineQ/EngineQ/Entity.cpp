#include "Entity.hpp"

namespace EngineQ
{
	Entity::Entity(Scripting::ScriptEngine& scriptEngine) : 
		Object{ scriptEngine, scriptEngine.GetEntityClass() }, 
		components{}, 
		transform{ *AddComponent<Transform>() }
	{
		// TMP
		scriptEngine.InvokeConstructor(GetManagedObject());
	}
	
	Entity::~Entity()
	{
		for (Component* component : components)
			delete component;
	}

	Transform& Entity::GetTransform()
	{
		return transform;
	}

	const Transform& Entity::GetTransform() const
	{
		return transform;
	}

	void Entity::Update()
	{
		for (Script* script : updatable)
			script->Update();
	}

	int Entity::GetComponentsCount() const
	{
		return static_cast<int>(this->components.size());
	}

	Component* Entity::GetComponent(int index) const
	{
		return this->components[index];
	}

	Script* Entity::AddScript(Scripting::ScriptClass sclass)
	{
		Script* script = new Script{ this->scriptEngine, *this, sclass };

		components.push_back(script);

		if (script->IsUpdateble())
			updatable.push_back(script);

		scriptEngine.InvokeConstructor(script->GetManagedObject());

		return script;
	}
}