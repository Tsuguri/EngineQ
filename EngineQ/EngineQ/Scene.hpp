#ifndef ENGINEQ_SCENE_HPP
#define ENGINEQ_SCENE_HPP

#include <vector>

#include "Entity.hpp"
#include "Light.hpp"
#include "Camera.hpp"
#include "Graphics/Shader.hpp"
#include "Renderable.hpp"

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
		std::vector<Graphics::Renderable*> renderables;
		Camera* activeCamera;


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

		void ActiveCamera(Camera* camera);
		Camera* ActiveCamera() const;

		std::vector<Graphics::Renderable*>::iterator RenderablesBegin();
		std::vector<Graphics::Renderable*>::iterator RenderablesEnd();
	};
}

#endif // !ENGINEQ_SCENE_HPP
