#ifndef ENGINEQ_SCENE_HPP
#define ENGINEQ_SCENE_HPP

#include <vector>
#include <memory>

#include "Types.hpp"
#include <Graphics/Types.hpp>

#include <Graphics/Scene.hpp>
#include "Object.hpp"

namespace EngineQ
{
	class Engine;
	class Scene : public Object, public Graphics::Scene
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
		Engine* engine;
		std::vector<std::unique_ptr<Entity>> entities;
		std::vector<std::unique_ptr<Object>> removeQueue;

		bool isUpdating = false;

		std::vector<Graphics::Shadows::Light*> lights;
		std::vector<Camera*> cameras;
		std::vector<Graphics::Renderable*> renderables;
		std::vector<Script*> updateable;

		std::vector<Script*> currentUpdateable;

		Camera* activeCamera = nullptr;


		void RemovedComponent(Component& component);
		void AddedComponent(Component& component);

		void RemoveEntity(decltype(entities)::iterator it);

		template<typename TComponentType>
		void TryRemove(std::vector<TComponentType*>& components, TComponentType& component);

		template<typename TComponentType>
		auto Find(std::vector<std::unique_ptr<TComponentType>>& components, TComponentType& component) -> decltype(components.begin());

	public:
		/*
	#pragma region Serialization

		Scene(Serialization::Deserializer& deserialzier);
		virtual void Serialize(Serialization::Serializer& serializer) const override;

	#pragma endregion
		*/

		Scene(Scripting::ScriptEngine& scriptEngine, Engine* engine);
		virtual ~Scene();

		Entity& CreateEntity(bool enabled = true, const std::string& name = "");
		void RemoveEntity(const Entity& entity);
		void RemoveEntity(std::size_t index);

		void Update();

		Entity* FindEntity(const std::string& name) const;

		std::size_t GetEntityIndex(const Entity& entity) const;

		Entity& GetEntity(std::size_t index) const;
		std::size_t GetEntitiesCount() const;

		void SetActiveCamera(Camera* camera);
		Graphics::Camera* GetActiveCamera() const override;
		Camera* GetActiveEngineCamera() const;

		const std::vector<Graphics::Shadows::Light*>& GetLights() const override;

		const std::vector<Graphics::Renderable*>& GetRenderables() const override;

		void AddToRemoveQueue(std::unique_ptr<Object> object);

		bool IsUpdating() const;

		Engine* GetEngine();
	};

	template<typename TComponentType>
	void Scene::TryRemove(std::vector<TComponentType*>& components, TComponentType& component)
	{
		auto it = std::find(components.begin(), components.end(), &component);
		if (it != components.end())
			components.erase(it);
	}

	template<typename TComponentType>
	auto Scene::Find(std::vector<std::unique_ptr<TComponentType>>& components, TComponentType& component) -> decltype(components.begin())
	{
		auto it = components.begin();
		for (auto end = components.end(); it != end; ++it)
			if (it->get() == &component)
				break;

		return it;
	}
}

#endif // !ENGINEQ_SCENE_HPP
