#include "Entity.hpp"
#include "Scene.hpp"

namespace EngineQ
{
	Entity::Entity(Scene& scene, Scripting::ScriptEngine& scriptEngine) :
		Object{ scriptEngine, scriptEngine.GetEntityClass() },
		scene{ scene },
		components{},
		transform{ *AddComponent<Transform>() },
		isRemoveLocked{false}
	{
		// TMP
		scriptEngine.InvokeConstructor(GetManagedObject());
	}

	Entity::~Entity()
	{
		for (auto component : components)
			delete component;
	}

	void Entity::LockRemove()
	{
		isRemoveLocked = true;
	}

	void Entity::UnlockRemove()
	{
		if (this->componentsToDelete.size() > 0)
		{
			for (auto component : this->componentsToDelete)
				RemoveComponent_Internal(*component, std::find(this->components.begin(), this->components.end(), component));
			this->componentsToDelete.clear();
		}

		isRemoveLocked = false;
	}

	void Entity::RemoveComponent_Internal(Component& component, std::vector<Component*>::iterator it)
	{
		this->components.erase(it);
		this->scene.RemovedComponent(component);
		
		// Remove from cache
		switch (component.GetType())
		{
			case ComponentType::Script:
			{
				Script& script = static_cast<Script&>(component);
				if (script.IsUpdateble())
					this->updatable.erase(std::remove(this->updatable.begin(), this->updatable.end(), &script), this->updatable.end());
			}
			break;
		}

		delete &component;
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

		auto it = std::find(this->components.begin(), this->components.end(), &component);
		if (it == this->components.end())
			throw std::runtime_error("Component not found");
		
		if (this->isRemoveLocked)
			this->componentsToDelete.push_back(&component);
		else
			RemoveComponent_Internal(component, it);
	}

	std::size_t Entity::GetComponentsCount() const
	{
		return static_cast<int>(this->components.size());
	}

	Component* Entity::GetComponent(std::size_t index) const
	{
		return this->components[index];
	}

	std::size_t Entity::GetComponentIndex(Component* component) const
	{
		for (auto it = this->components.begin(), end = this->components.end(); it != end; ++it)
			if (*it == component)
				return it - this->components.begin();

		throw std::runtime_error("Component not found");
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