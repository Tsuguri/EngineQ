#ifndef ENGINEQ_SCENE_HPP
#define ENGINEQ_SCENE_HPP

#include <vector>
#include <memory>

#include "Types.hpp"
#include "../Graphics/Types.hpp"

#include "Object.hpp"
#include "Entity.hpp"
#include "Component.hpp"

namespace EngineQ
{
	class Scene : public Object
	{
		friend class Engine;

	public:
		class EntityCallbacks
		{
			friend class Entity;

		private:
			static void OnComponentAdded(Scene& scene, Component& component);
			static void OnComponentRemoved(Scene& scene, Component& component);
		};

	private:
		std::vector<std::unique_ptr<Entity>> entities;
		std::vector<std::unique_ptr<Object>> removeQueue;

		bool isUpdating = false;

		std::vector<Light*> lights;
		std::vector<Camera*> cameras;
		std::vector<Renderable*> renderables;
		std::vector<Script*> updateable;

		std::vector<Script*> currentUpdateable;

		Camera* activeCamera = nullptr;


		void RemovedComponent(Component& component);
		void AddedComponent(Component& component);

		void RemoveEntity(decltype(entities)::iterator it);

		template<typename TComponentType>
		void TryRemove(std::vector<TComponentType*>& components, TComponentType& component);

		template<typename TComponentType>
		auto Find(std::vector<std::unique_ptr<TComponentType>>& components, ComponentType& component) -> decltype(components.begin());

	public:
		/*
	#pragma region Serialization

		Scene(Serialization::Deserializer& deserialzier);
		virtual void Serialize(Serialization::Serializer& serializer) const override;

	#pragma endregion
		*/

		Scene(Scripting::ScriptEngine& scriptEngine);

		Entity& CreateEntity(bool enabled = true, const std::string& name = "");
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

	template<typename TComponentType>
	void Scene::TryRemove(std::vector<TComponentType*>& components, TComponentType& component)
	{
		auto it = std::find(components.begin(), components.end(), &component);
		if (it != components.end())
			components.erase(it);
	}

	template<typename TComponentType>
	auto Scene::Find(std::vector<std::unique_ptr<TComponentType>>& components, ComponentType& component) -> decltype(components.begin())
	{
		auto it = components.begin();
		for (auto end = components.end(); it != end; ++it)
			if (it->get() == &component)
				break;

		return it;
	}
}

#endif // !ENGINEQ_SCENE_HPP
