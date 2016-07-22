#ifndef ENGINEQ_SCENE_HPP
#define ENGINEQ_SCENE_HPP

#include <vector>

#include "Entity.hpp"
#include "Light.hpp"
#include "Camera.hpp"
#include "Graphics/Shader.hpp"
#include "Graphics/Renderable.hpp"

namespace EngineQ
{
	class Scene : public Object
	{
		friend class Entity;
		friend class Engine;

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
	#pragma region Serialization

		Scene(Serialization::Deserializer& deserialzier);
		virtual void Serialize(Serialization::Serializer& serializer) const override;

	#pragma endregion

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
