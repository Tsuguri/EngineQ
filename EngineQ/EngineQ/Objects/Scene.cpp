#include "Scene.hpp"

#include <algorithm>

#include "Entity.hpp"
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

	Scene::Scene(Scripting::ScriptEngine& scriptEngine) :
		Object{ scriptEngine, scriptEngine.GetSceneClass() }
	{
	}

	Scene::~Scene()
	{
		for (auto entity : this->entities)
			delete entity;
	}

	Entity* Scene::CreateEntity()
	{
		Entity* entity = new Entity{ *this, this->scriptEngine };
		this->entities.push_back(entity);
		return entity;
	}

	void Scene::RemoveEntity(Entity* entity)
	{
		auto it = std::find(this->entities.begin(), this->entities.end(), entity);
		if (it == this->entities.end())
			throw std::runtime_error("Entity not found");

		if (this->isUpdating)
			this->entitiesToDelete.push_back(entity);
		else
			RemoveEntity_Internal(entity, it);
	}

	void Scene::RemoveEntity(std::size_t index)
	{
		if (index >= this->entities.size())
			throw std::runtime_error("Index out of range");
		auto it = std::next(this->entities.begin(), index);

		if (this->isUpdating)
			this->entitiesToDelete.push_back(*it);
		else
			RemoveEntity_Internal(*it, it);
	}

	void Scene::Update()
	{
		isUpdating = true;

		// Lock entities
		for (auto entity : this->entities)
			entity->LockRemove();

		// Update entities
		for (size_t i = 0, size = this->entities.size(); i < size; ++i)
			this->entities[i]->Update();

		// Remove entities
		if (this->entitiesToDelete.size() > 0)
		{
			for (auto entity : this->entitiesToDelete)
				RemoveEntity_Internal(entity, std::find(this->entities.begin(), this->entities.end(), entity));
			this->entitiesToDelete.clear();
		}

		// Unlock entities
		for (auto entity : this->entities)
			entity->UnlockRemove();

		isUpdating = false;
	}

	void Scene::RemoveEntity_Internal(Entity* entity, std::vector<Entity*>::iterator it)
	{
		// Remove entity components
		this->cameras.erase(std::remove_if(this->cameras.begin(), this->cameras.end(), [=](Component* component) {return &component->GetEntity() == entity; }), this->cameras.end());
		this->lights.erase(std::remove_if(this->lights.begin(), this->lights.end(), [=](Component* component) {return &component->GetEntity() == entity; }), this->lights.end());

		this->entities.erase(it);

		delete entity;
	}

	void Scene::RemovedComponent(Component& component)
	{
		switch (component.GetType())
		{
			case ComponentType::Camera:
			{
				Camera& camera = static_cast<Camera&>(component);
				this->cameras.erase(std::remove(this->cameras.begin(), this->cameras.end(), &camera), this->cameras.end());
			}
			break;

			case ComponentType::Light:
			{
				Light& light = static_cast<Light&>(component);
				this->lights.erase(std::remove(this->lights.begin(), this->lights.end(), &light), this->lights.end());
			}
			break;
			case ComponentType::Renderable:
			{
				Renderable& renderable = static_cast<Renderable&>(component);
				this->renderables.erase(std::remove(this->renderables.begin(), this->renderables.end(), &renderable), this->renderables.end());
			}
			break;

			default:
			break;
		}
	}

	void Scene::AddedComponent(Component& component)
	{
		switch (component.GetType())
		{
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

	std::size_t Scene::GetEntityIndex(Entity* entity) const
	{
		auto it = std::find(this->entities.begin(), this->entities.end(), entity);

		if (it == this->entities.end())
			return static_cast<std::size_t>(-1);

		return it - this->entities.begin();
	}

	Entity* Scene::GetEntity(std::size_t index) const
	{
		return this->entities[index];
	}

	std::size_t Scene::GetEntitiesCount() const
	{
		return this->entities.size();
	}

	void Scene::ActiveCamera(Camera* camera)
	{
		if (camera == nullptr || &camera->GetEntity().GetScene() != this)
			return;
		activeCamera = camera;
	}

	Camera* Scene::ActiveCamera() const
	{
		return activeCamera;
	}

	std::vector<Renderable*>::iterator Scene::RenderablesBegin()
	{
		return renderables.begin();
	}

	std::vector<Renderable*>::iterator Scene::RenderablesEnd()
	{
		return renderables.end();
	}
}
