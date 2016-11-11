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
		transform{ AddComponent<Transform>() },
		name{ name }
	{
		// TMP
		scriptEngine.InvokeConstructor(GetManagedObject());
	}

	Entity::~Entity()
	{
	}

	void Entity::AddComponent(std::unique_ptr<Component> componentPtr)
	{
		Component& component = *componentPtr;
		this->components.push_back(std::move(componentPtr));

		if (component.IsEnabledInHierarchy())
			Scene::EntityCallbacks::OnComponentAdded(this->scene, component);

		this->scriptEngine.InvokeConstructor(component.GetManagedObject());
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

	void Entity::RemoveComponent(Component& component)
	{
		if (&component == &this->transform)
			throw std::runtime_error("Cannot remove transform component");

		auto it = this->components.begin();
		for (auto end = this->components.end(); it != end; ++it)
			if (it->get() == &component)
				break;

		if (it == this->components.end())
			throw std::runtime_error("Component not found");

		Scene::EntityCallbacks::OnComponentRemoved(this->scene, component);

		if (this->scene.IsUpdating())
			this->scene.AddToRemoveQueue(std::move(*it));

		this->components.erase(it);
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
			if (it->get() == &component)
				return it - this->components.begin();

		throw std::runtime_error("Component not found");
	}

	Script& Entity::AddScript(Scripting::ScriptClass sclass, bool enabled)
	{
		auto scriptPtr = std::unique_ptr<Script>(new Script{ this->scriptEngine, *this, sclass, enabled });
		auto& script = *scriptPtr;

		this->AddComponent(std::move(scriptPtr));

		script.OnCreate();

		return script;
	}

	void Entity::HierarchyEnabledChanged(bool hierarchyEnabled)
	{
		for (const auto child : this->transform.children)
			child->entity.SetParentEnabled(hierarchyEnabled);

		for (auto& component : this->components)
			component->SetParentEnabled(hierarchyEnabled);

		if (hierarchyEnabled)
		{
			for (auto& component : this->components)
				if (component->IsEnabled())
					Scene::EntityCallbacks::OnComponentAdded(this->scene, *component);
		}
		else
		{
			for (auto& component : this->components)
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



	std::unique_ptr<Entity> Entity::SceneCallbacks::CreateEntity(Scene& scene, Scripting::ScriptEngine& scriptEngine, bool enabled, const std::string& name)
	{
		return std::unique_ptr<Entity>{new Entity{ scene, scriptEngine, enabled, name }};
	}

	void Entity::TransformCallbacks::OnParentChanged(Entity& entity, Transform* parent)
	{
		entity.SetParentEnabled(parent == nullptr || parent->IsEnabled());
	}

	void Entity::ComponentCallbacks::OnEnabledChanged(Entity& entity, Component& component, bool enabled)
	{
		if (enabled)
			Scene::EntityCallbacks::OnComponentAdded(entity.scene, component);
		else
			Scene::EntityCallbacks::OnComponentRemoved(entity.scene, component);
	}
}