#include "Entity.hpp"

#include <algorithm>

#include "Scene.hpp"
#include "Script.hpp"
#include "Transform.hpp"

#include "../Scripting/ScriptEngine.hpp"
#include "../Serialization/Serializer.hpp"
#include "../Serialization/Deserializer.hpp"
#include "../Serialization/SerializationRules.hpp"

namespace EngineQ
{
	/*
#pragma region Serialization

	Entity::Entity(Serialization::Deserializer& deserialzier) :
		Object{ deserialzier },
		scene{ *deserialzier.GetReference<Scene>("scene") },
		components{ deserialzier.GetValue<std::vector<Component*>>("components") },
		updatable{ deserialzier.GetValue<std::vector<Script*>>("updatable") },
		transform{ *deserialzier.GetReference<Transform>("transform") }
	{
	}

	void Entity::Serialize(Serialization::Serializer& serializer) const
	{
		Object::Serialize(serializer);
		serializer.StoreReference("scene", &this->scene);
		serializer.StoreValue("components", &this->components);
		serializer.StoreReference("transform", &this->transform);
		serializer.StoreValue("updatable", &this->updatable);
	}

#pragma endregion
	*/

	Entity::Entity(Scene& scene, Scripting::ScriptEngine& scriptEngine, bool enabled, const std::string& name) :
		Object{ scriptEngine, scriptEngine.GetClass(Scripting::ScriptEngine::Class::Entity) },
		scene{ scene },
		enabled{ enabled },
		components{},
		updatable{},
		transform{ AddComponent<Transform>() },
		name{ name }
	{
		// TMP
		scriptEngine.InvokeConstructor(GetManagedObject());
	}

	Entity::~Entity()
	{
		for (auto component : components)
			delete component;
	}

	void Entity::AddComponent(Component& component)
	{
		this->components.push_back(&component);

		if(component.IsEnabledInHierarchy())
			Scene::EntityCallbacks::OnComponentAdded(this->scene, component);

		this->scriptEngine.InvokeConstructor(component.GetManagedObject());
	}

	void Entity::LockRemove()
	{
		removeLocked = true;
	}

	void Entity::UnlockRemove()
	{
		if (this->componentsToDelete.size() > 0)
		{
			for (auto component : this->componentsToDelete)
				RemoveComponent_Internal(*component, std::find(this->components.begin(), this->components.end(), component));
			this->componentsToDelete.clear();
		}

		removeLocked = false;
	}

	void Entity::RemoveComponent_Internal(Component& component, std::vector<Component*>::iterator it)
	{
		if(component.IsEnabledInHierarchy())
			Scene::EntityCallbacks::OnComponentRemoved(this->scene, component);
		
		this->components.erase(it);

		// Remove from cache
		switch (component.GetType())
		{
			case ComponentType::Script:
			{
				Script& script = static_cast<Script&>(component);
				if (script.IsUpdateble() && script.IsEnabledInHierarchy())
					this->updatable.erase(std::find(this->updatable.begin(), this->updatable.end(), &script));
			}
			break;

			default:
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
			script->OnUpdate();
	}

	void Entity::RemoveComponent(Component& component)
	{
		if (&component == &this->transform)
			throw std::runtime_error("Cannot remove transform component");

		auto it = std::find(this->components.begin(), this->components.end(), &component);
		if (it == this->components.end())
			throw std::runtime_error("Component not found");

		if (this->removeLocked)
			this->componentsToDelete.push_back(&component);
		else
			RemoveComponent_Internal(component, it);
	}

	std::size_t Entity::GetComponentsCount() const
	{
		return static_cast<int>(this->components.size());
	}

	Component& Entity::GetComponent(std::size_t index) const
	{
		return *this->components[index];
	}

	std::size_t Entity::GetComponentIndex(const Component& component) const
	{
		for (auto it = this->components.begin(), end = this->components.end(); it != end; ++it)
			if (*it == &component)
				return it - this->components.begin();

		throw std::runtime_error("Component not found");
	}

	Script& Entity::AddScript(Scripting::ScriptClass sclass, bool enabled)
	{
		Script* script = new Script{ this->scriptEngine, *this, sclass, enabled };

		components.push_back(script);

		if (script->IsUpdateble() && script->IsEnabled())
			updatable.push_back(script);

		scriptEngine.InvokeConstructor(script->GetManagedObject());

		return *script;
	}

	void Entity::HierarchyEnabledChanged(bool hierarchyEnabled)
	{
		for (const auto child : this->transform.children)
			child->entity.SetParentEnabled(hierarchyEnabled);

		for (auto component : this->components)
			component->SetParentEnabled(hierarchyEnabled);

		if (hierarchyEnabled)
		{
			for (auto component : this->components)
				if (component->IsEnabled())
					Scene::EntityCallbacks::OnComponentAdded(this->scene, *component);
		}
		else
		{
			for (auto component : this->components)
				if (component->IsEnabled())
					Scene::EntityCallbacks::OnComponentRemoved(this->scene, *component);
		}
	}

	void Entity::SetParentEnabled(bool enabled)
	{
		if (this->parentEnabled == enabled)
			return;

		this->parentEnabled = enabled;

		if (this->enabled)
			HierarchyEnabledChanged(this->IsEnabledInHierarchy());
	}

	bool Entity::IsEnabled() const
	{
		return this->enabled;
	}

	void Entity::SetEnabled(bool enabled)
	{
		if (enabled == this->enabled)
			return;

		this->enabled = enabled;

		if (this->parentEnabled)
			HierarchyEnabledChanged(this->IsEnabledInHierarchy());
	}

	bool Entity::IsEnabledInHierarchy() const
	{
		return this->enabled && this->parentEnabled;
	}

	const std::string& Entity::GetName() const
	{
		return this->name;
	}

	void Entity::SetName(const std::string& name)
	{
		this->name = name;
	}



	Entity& Entity::SceneCallbacks::CreateEntity(Scene& scene, Scripting::ScriptEngine& scriptEngine, bool enabled, const std::string& name)
	{
		return *new Entity{ scene, scriptEngine, enabled, name };
	}

	void Entity::SceneCallbacks::OnUpdate(Entity& entity)
	{
		entity.Update();
	}

	void Entity::SceneCallbacks::OnUpdateBegin(Entity& entity)
	{
		entity.LockRemove();
	}

	void Entity::SceneCallbacks::OnUpdateEnd(Entity& entity)
	{
		entity.UnlockRemove();
	}

	void Entity::TransformCallbacks::OnParentChanged(Entity& entity, Transform* parent)
	{
		entity.SetParentEnabled(parent == nullptr || parent->IsEnabled());
	}

	void Entity::ComponentCallbacks::OnEnabledChanged(Entity& entity, Component& component, bool enabled)
	{
		if (enabled)
		{
			switch (component.GetType())
			{
				case ComponentType::Script:
				{
					auto& script = static_cast<Script&>(component);

					if (script.IsUpdateble())
						entity.updatable.push_back(&script);
				}
				break;

				default:
				break;
			}

			Scene::EntityCallbacks::OnComponentAdded(entity.scene, component);
		}
		else
		{
			switch (component.GetType())
			{
				case ComponentType::Script:
				{
					auto& script = static_cast<Script&>(component);

					if (script.IsUpdateble())
						entity.updatable.erase(std::find(entity.updatable.begin(), entity.updatable.end(), &script));
				}
				break;

				default:
				break;
			}

			Scene::EntityCallbacks::OnComponentRemoved(entity.scene, component);
		}
	}
}