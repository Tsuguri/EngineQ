#ifndef ENGINEQ_ENTITY_HPP
#define ENGINEQ_ENTITY_HPP

#include <vector>

#include "Types.hpp"

#include "Object.hpp"

namespace EngineQ
{
	class Entity : public Object
	{
	public:
		class SceneCallbacks
		{
			friend class Scene;

		private:
			static Entity& CreateEntity(Scene& scene, Scripting::ScriptEngine& scriptEngine);
		
			static void OnUpdate(Entity& entity);
			static void OnUpdateBegin(Entity& entity);
			static void OnUpdateEnd(Entity& entity);
		};

		class TransformCallbacks
		{
			friend class Transform;

		private:
			static void OnParentChanged(Entity& entity, Transform* parent);
		};

		class ComponentCallbacks
		{
			friend class Component;

		private:
			static void OnEnabledChanged(Entity& entity, Component& component, bool enabled);
		};

	private:
		Scene& scene;

		bool removeLocked = false;

		bool enabled = true;
		bool parentEnabled = true;

		std::vector<Component*> components;
		std::vector<Script*> updatable;

		std::vector<Component*> componentsToDelete;

		Transform& transform;

		std::string name;

		Entity(Scene& scene, Scripting::ScriptEngine& scriptEngine);

		void LockRemove();
		void UnlockRemove();

		void RemoveComponent_Internal(Component& component, std::vector<Component*>::iterator it);

		void Update();

		void AddComponent(Component& component);

		void SetParentEnabled(bool enabled);
		void HierarchyEnabledChanged(bool hierarchyEnabled);

	public:
		/*
	#pragma region Serialization

		Entity(Serialization::Deserializer& deserialzier);
		virtual void Serialize(Serialization::Serializer& serializer) const override;

	#pragma endregion
		*/

		virtual ~Entity() override;

		const Scene& GetScene() const;
		Scene& GetScene();

		const Transform& GetTransform() const;
		Transform& GetTransform();

		bool IsEnabled() const;
		void SetEnabled(bool enabled);

		bool IsEnabledInHierarchy() const;


		std::size_t GetComponentsCount() const;
		Component& GetComponent(std::size_t index) const;

		template<typename Type>
		Type& AddComponent();
		void RemoveComponent(Component& component);

		std::size_t GetComponentIndex(const Component& component) const;

		Script& AddScript(Scripting::ScriptClass sclass);

		const std::string& GetName() const;
		void SetName(const std::string& name);
	};
}

namespace EngineQ
{
	template<typename Type>
	Type& Entity::AddComponent()
	{
		Type& component = *new Type{ this->scriptEngine, *this };

		this->AddComponent(component);

		return component;
	}
}

#endif // !ENGINEQ_ENTITY_HPP
