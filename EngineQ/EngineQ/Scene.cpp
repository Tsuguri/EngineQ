#include "Scene.hpp"

namespace EngineQ
{
	Scene::Scene(Scripting::ScriptEngine& scriptEngine) :
		Object{scriptEngine, scriptEngine.GetSceneClass()}
	{

	}

	Scene::~Scene()
	{
		for (auto entity : this->entities)
			delete entity;
	}

	Entity* Scene::CreateEntity()
	{
		return new Entity{ *this, this->scriptEngine };
	}

	void Scene::RemoveEntity(Entity* entity)
	{
		RemoveEntityComponents(entity);
		this->entities.erase(std::remove(this->entities.begin(), this->entities.end(), entity), this->entities.end());
		
		delete entity;
	}

	void Scene::RemoveEntity(std::size_t index)
	{
		auto it = std::next(this->entities.begin(), index);

		RemoveEntityComponents(*it);
		this->entities.erase(it);
	}

	void Scene::RemoveEntityComponents(Entity* entity)
	{
		this->cameras.erase(std::remove_if(this->cameras.begin(), this->cameras.end(), [=](Component* component) {return &component->GetEntity() == entity; }), this->cameras.end());
		this->lights.erase(std::remove_if(this->lights.begin(), this->lights.end(), [=](Component* component) {return &component->GetEntity() == entity; }), this->lights.end());
	}

	void Scene::RemovedComponent(Component& component)
	{
		switch (component.GetType())
		{
			case ComponentType::Camera:
			{
				Camera* camera = static_cast<Camera*>(&component);
				this->cameras.erase(std::remove(this->cameras.begin(), this->cameras.end(), camera), this->cameras.end());
			}
			break;

			case ComponentType::Light:
			{
				Light* light = static_cast<Light*>(&component);
				this->lights.erase(std::remove(this->lights.begin(), this->lights.end(), light), this->lights.end());
			}
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
}