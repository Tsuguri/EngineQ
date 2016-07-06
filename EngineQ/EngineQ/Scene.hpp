#ifndef ENGINEQ_SCENE_H
#define ENGINEQ_SCENE_H

#include <vector>

#include "Entity.hpp"
#include "Light.hpp"
#include "Camera.hpp"

namespace EngineQ
{
	class Scene : public Object
	{
		friend class Entity;

	private:
		std::vector<Entity*> entities;
		std::vector<Entity*> entitiesToDelete;

		bool isUpdating;

		std::vector<Light*> lights;
		std::vector<Camera*> cameras;


		void RemovedComponent(Component& component);
		void AddedComponent(Component& component);

		void RemoveEntity_Internal(Entity* entity, std::vector<Entity*>::iterator it);

	public:
		Scene(Scripting::ScriptEngine& scriptEngine);
		~Scene();

		Entity* CreateEntity();
		void RemoveEntity(Entity* entity);
		void RemoveEntity(std::size_t index);

		void Update();

		std::size_t GetEntityIndex(Entity* entity) const;

		Entity* GetEntity(std::size_t index) const;
		std::size_t GetEntitiesCount() const;
	};
}

#endif // !ENGINEQ_SCENE_H
