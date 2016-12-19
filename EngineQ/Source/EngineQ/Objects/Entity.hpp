#ifndef ENGINEQ_ENTITY_HPP
#define ENGINEQ_ENTITY_HPP

// Standard includes
#include <vector>
#include <memory>

// This project
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
			static std::unique_ptr<Entity> CreateEntity(Scene& scene, Scripting::ScriptEngine& scriptEngine, bool enabled, const std::string& name);
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

		bool enabled = true;
		bool parentEnabled = true;

		std::vector<std::unique_ptr<Component>> components;

		Transform& transform;

		std::string name;

		Entity(Scene& scene, Scripting::ScriptEngine& scriptEngine, bool enabled, const std::string& name);
		

		void AddComponent(std::unique_ptr<Component> component);

		void SetParentEnabled(bool enabled);
		void HierarchyEnabledChanged(bool hierarchyEnabled);

	public:
		/*
	#pragma region Serialization

		Entity(Serialization::Deserializer& deserialzier);
		virtual void Serialize(Serialization::Serializer& serializer) const override;

	#pragma endregion
		*/

		virtual ~Entity();

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
		Type& AddComponent(bool enabled = true);

		void RemoveComponent(Component& component);

		std::size_t GetComponentIndex(const Component& component) const;

		Script& AddScript(Scripting::ScriptClass sclass, bool enabled = true);

		const std::string& GetName() const;
		void SetName(const std::string& name);
	};
}

namespace EngineQ
{
	template<typename Type>
	Type& Entity::AddComponent(bool enabled)
	{
		auto componentPtr = std::unique_ptr<Type>{ new Type{ this->scriptEngine, *this, enabled } };
		auto& component = *componentPtr;

		this->AddComponent(std::move(componentPtr));

		return component;
	}
}

#endif // !ENGINEQ_ENTITY_HPP
