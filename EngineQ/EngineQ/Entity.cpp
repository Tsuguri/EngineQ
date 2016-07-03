#include "Entity.hpp"
#include "Scene.hpp"

namespace EngineQ
{
	Entity::Entity(Scene& scene, Scripting::ScriptEngine& scriptEngine) :
		Object{ scriptEngine, scriptEngine.GetEntityClass() },
		scene{ scene },
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

	const Scene& Entity::GetScene() const
	{
		return this->scene;
	}

	Scene& Entity::GetScene()
	{
		return this->scene;
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

	void Entity::RemoveComponent(Component& component)
	{
		if (&component == &this->transform)
			throw std::runtime_error("Cannot remove transform component");

		this->scene.RemovedComponent(component);

		this->components.erase(std::remove(this->components.begin(), this->components.end(), &component), this->components.end());

		delete &component;
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