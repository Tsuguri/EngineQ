#ifndef ENGINEQ_SCENE_HPP
#define ENGINEQ_SCENE_HPP

#include <vector>

#include "Types.hpp"
#include "../Graphics/Types.hpp"

#include "Object.hpp"

namespace EngineQ
{
	class Scene : public Object
	{
		friend class Entity;
		friend class Engine;

	private:
		std::vector<Entity*> entities;
		std::vector<const Entity*> entitiesToDelete;

		bool isUpdating = false;

		std::vector<Light*> lights;
		std::vector<Camera*> cameras;
		std::vector<Renderable*> renderables;
		Camera* activeCamera = nullptr;


		void RemovedComponent(Component& component);
		void AddedComponent(Component& component);

		void RemoveEntity_Internal(const Entity* entity, std::vector<Entity*>::iterator it);

	public:
		/*
	#pragma region Serialization

		Scene(Serialization::Deserializer& deserialzier);
		virtual void Serialize(Serialization::Serializer& serializer) const override;

	#pragma endregion
		*/

		Scene(Scripting::ScriptEngine& scriptEngine);
		~Scene();

		Entity& CreateEntity();
		void RemoveEntity(const Entity& entity);
		void RemoveEntity(std::size_t index);

		void Update();

		Entity* FindEntity(const std::string& name) const;

		std::size_t GetEntityIndex(const Entity& entity) const;

		Entity& GetEntity(std::size_t index) const;
		std::size_t GetEntitiesCount() const;

		void SetActiveCamera(Camera* camera);
		Camera* GetActiveCamera() const;

		const std::vector<Renderable*>& GetRenderables() const;
	};
}

#endif // !ENGINEQ_SCENE_HPP
