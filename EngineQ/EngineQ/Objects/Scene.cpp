#include "Scene.hpp"

#include <algorithm>

#include "Entity.hpp"
#include "Script.hpp"
#include "Component.hpp"
#include "Light.hpp"
#include "Camera.hpp"
#include "Renderable.hpp"

#include "../Scripting/ScriptEngine.hpp"
#include "../Serialization/Serializer.hpp"
#include "../Serialization/Deserializer.hpp"
#include "../Serialization/SerializationRules.hpp"


namespace EngineQ
{
	/*
#pragma region Serialization

	Scene::Scene(Serialization::Deserializer& deserialzier) :
		Object{ deserialzier },
		entities{ deserialzier.GetValue<std::vector<Entity*>>("entities") }
	{
	}

	void Scene::Serialize(Serialization::Serializer& serializer) const
	{
		Object::Serialize(serializer);
		serializer.StoreValue("entities", &this->entities);
	}

#pragma endregion
	*/

	Scene::Scene(Scripting::ScriptEngine& scriptEngine) :
		Object{ scriptEngine, scriptEngine.GetClass(Scripting::ScriptEngine::Class::Scene) }
	{
	}

	Scene::~Scene()
	{
	}

	Entity* Scene::FindEntity(const std::string& name) const
	{
		for (auto& entity : this->entities)
			if (entity->GetName() == name)
				return entity.get();

		return nullptr;
	}

	Entity& Scene::CreateEntity(bool enabled, const std::string& name)
	{
		auto entityPtr = Entity::SceneCallbacks::CreateEntity(*this, this->scriptEngine, enabled, name);
		auto& entity = *entityPtr;

		this->entities.push_back(std::move(entityPtr));

		return entity;
	}

	void Scene::RemoveEntity(const Entity& entity)
	{
		auto it = this->entities.begin();
		for (auto end = this->entities.end(); it != end; ++it)
			if (it->get() == &entity)
				break;

		if (it == this->entities.end())
			throw std::runtime_error("Entity not found");

		RemoveEntity(it);
	}

	void Scene::RemoveEntity(std::size_t index)
	{
		if (index >= this->entities.size())
			throw std::runtime_error("Index out of range");
		auto it = std::next(this->entities.begin(), index);

		RemoveEntity(it);
	}

	void Scene::Update()
	{
		isUpdating = true;

		// Copy updateable
		this->currentUpdateable = this->updateable;

		// Update entities
		for (auto script : this->currentUpdateable)
			script->OnUpdate();

		isUpdating = false;

		// Remove deleted objects
		this->removeQueue.clear();
	}

	void Scene::RemoveEntity(decltype(entities)::iterator it)
	{
		Entity* entity = it->get();

		if (this->isUpdating)
			this->removeQueue.push_back(std::move(*it));

		// Remove entity components
		this->cameras.erase(std::remove_if(this->cameras.begin(), this->cameras.end(), [=](Component* component) { return &component->GetEntity() == entity; }), this->cameras.end());
		this->lights.erase(std::remove_if(this->lights.begin(), this->lights.end(), [=](Component* component) { return &component->GetEntity() == entity; }), this->lights.end());
		this->updateable.erase(std::remove_if(this->updateable.begin(), this->updateable.end(), [=](Script* script) { return script->IsUpdateble() && &script->GetEntity() == entity; }), this->updateable.end());

		this->entities.erase(it);
	}

	void Scene::RemovedComponent(Component& component)
	{
		switch (component.GetType())
		{
			case ComponentType::Script:
			{
				auto& script = static_cast<Script&>(component);
				if (script.IsUpdateble())
					TryRemove(this->updateable, script);
			}
			break;

			case ComponentType::Camera:
			TryRemove(this->cameras, static_cast<Camera&>(component));
			break;

			case ComponentType::Light:
			TryRemove(this->lights, static_cast<Light&>(component));
			break;

			case ComponentType::Renderable:
			TryRemove(this->renderables, static_cast<Graphics::Renderable&>(static_cast<Renderable&>(component)));
			break;

			default:
			break;
		}
	}

	void Scene::AddedComponent(Component& component)
	{
		switch (component.GetType())
		{
			case ComponentType::Script:
			{
				auto& script = static_cast<Script&>(component);
				if (script.IsUpdateble())
					this->updateable.push_back(&script);
			}
			break;

			case ComponentType::Camera:
			this->cameras.push_back(static_cast<Camera*>(&component));
			break;

			case ComponentType::Light:
			this->lights.push_back(static_cast<Light*>(&component));
			break;

			case ComponentType::Renderable:
			this->renderables.push_back(static_cast<Renderable*>(&component));

			default:
			break;
		}
	}

	std::size_t Scene::GetEntityIndex(const Entity& entity) const
	{
		for (auto it = this->entities.begin(), end = this->entities.end(); it != end; ++it)
			if (it->get() == &entity)
				return it - this->entities.begin();

		throw std::runtime_error{ "Entity not found" };
	}

	Entity& Scene::GetEntity(std::size_t index) const
	{
		return *this->entities[index];
	}

	std::size_t Scene::GetEntitiesCount() const
	{
		return this->entities.size();
	}

	void Scene::SetActiveCamera(Camera* camera)
	{
		if (&camera->GetEntity().GetScene() != this)
			throw std::runtime_error{ "Camera does not belong to the scene" };

		this->activeCamera = camera;
	}

	Graphics::Camera* Scene::GetActiveCamera() const
	{
		return this->activeCamera;
	}

	Camera* Scene::GetActiveEngineCamera() const
	{
		return this->activeCamera;
	}

	const std::vector<Graphics::Renderable*>& Scene::GetRenderables() const
	{
		return this->renderables;
	}


	void Scene::EntityCallbacks::OnComponentAdded(Scene& scene, Component& component)
	{
		scene.AddedComponent(component);
	}

	void Scene::EntityCallbacks::OnComponentRemoved(Scene& scene, Component& component)
	{
		scene.RemovedComponent(component);
	}

	bool Scene::IsUpdating() const
	{
		return this->isUpdating;
	}

	void Scene::AddToRemoveQueue(std::unique_ptr<Object> object)
	{
		this->removeQueue.push_back(std::move(object));
	}
}
