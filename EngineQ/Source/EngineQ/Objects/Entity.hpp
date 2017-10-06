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
	/// <summary>
	/// Abstract representation of the scene object.
	/// Provides utilities for adding and removing <see cref="Component"/>s which provide functionality for Entities.
	/// </summary>
	class Entity : public Object
	{
	public:
		/// <summary>
		/// Class providing interface methods exposed only to <see cref="Scene"/> class.
		/// </summary>
		class SceneCallbacks
		{
			friend class Scene;

		private:
			static std::unique_ptr<Entity> CreateEntity(Scene& scene, Scripting::ScriptEngine& scriptEngine, bool enabled, const std::string& name);
		};

		/// <summary>
		/// Class providing interface methods exposed only to <see cref="Transform"/> class.
		/// </summary>
		class TransformCallbacks
		{
			friend class Transform;

		private:
			static void OnParentChanged(Entity& entity, Transform* parent);
		};

		/// <summary>
		/// Class providing interface methods exposed only to <see cref="Component"/> class.
		/// </summary>
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

		/// <summary>
		/// Returns scene contaning this Entity.
		/// </summary>
		/// <returns>Scene contaning this Entity.</returns>
		const Scene& GetScene() const;
		
		/// <summary>
		/// Returns scene contaning this Entity.
		/// </summary>
		/// <returns>Scene contaning this Entity.</returns>
		Scene& GetScene();

		/// <summary>
		/// Returns <see cref="Component"/> describing position, orientation and hierarchy of this Entity on the <see cref="Scene"/>. 
		/// </summary>
		/// <returns>Transform component assigned to this Entity.</returns>
		const Transform& GetTransform() const;
		
		/// <summary>
		/// Returns <see cref="Component"/> describing position, orientation and hierarchy of this Entity on the <see cref="Scene"/>. 
		/// </summary>
		/// <returns>Transform component assigned to this Entity.</returns>
		Transform& GetTransform();
		
		/// <summary>
		/// Specifies whether the Entity is enabled. 
		/// </summary>
		/// <returns>true if Entity is enabled. Otherwise false.</returns>
		bool IsEnabled() const;

		/// <summary>
		/// Sets whether the Entity is enabled. 
		/// When set to false, the Entity will be disabled.
		/// Disabling Entity disables all children Entities and Components of this Entity. 
		/// </summary>
		/// <param name="enabled">true to enable, false to disable</param>
		void SetEnabled(bool enabled);

		/// <summary>
		/// Specifies whether the Entity is enabled in hierarchy.
		/// Entity can be disabled if it is disabled itself (<see cref="IsEnabled"/> is set to false), or it's parent <see cref="Transform::Parent"/> is disabled in hierarchy (<see cref="IsEnabledInHierarchy"/> is set to false).
		/// </summary>
		/// <returns>true when the Entity is enabled in hierarchy. Otherwise false.</returns>
		bool IsEnabledInHierarchy() const;

		/// <summary>
		/// Returns amount of <see cref="Component"/>s added to the Entity.
		/// </summary>
		/// <returns>Amount of <see cref="Component"/>s added to the Entity.</returns>
		std::size_t GetComponentsCount() const;
		
		/// <summary>
		/// Gets <see cref="Component"/> with specified index.
		/// </summary>
		/// <param name="index">Index of the <see cref="Component"/>.</param>
		/// <returns>Reference to the <see cref="Component"/> at specified index.</returns>
		Component& GetComponent(std::size_t index) const;

		/// <summary>
		/// Creates and adds <see cref="Component"/> with given type to this Entity.
		/// </summary>
		/// <typeparam name="Type">Type of the <see cref="Component"/>.</typeparam>
		/// <param name="enabled">Specifies whether <see cref="Component"/> will be created as enabled or disabled.</param>
		/// <returns>Reference to created component.</returns>
		template<typename Type>
		Type& AddComponent(bool enabled = true);

		/// <summary>
		/// Removes specified <see cref="Component"/> from this Entity and destroys it.
		/// </summary>
		/// <param name="component"><see cref="Component"/> to be removed and destroyed.</param>
		/// <exception cref="std::runtime_error">Thrown when <paramref name="component"/> is not owned by this Entity or it is <see cref="Transform"/> component.</exception>
		void RemoveComponent(Component& component);

		/// <summary>
		/// Returns index of given component.
		/// </summary>
		/// <exception cref="std::runtime_error">Thrown when component is not found.</exception>
		/// <param name="component">Component which index will be found. It must be owned by this Entity.</param>
		/// <returns>Index of given component.</returns>
		std::size_t GetComponentIndex(const Component& component) const;

		/// <summary>
		/// Adds <see cref="Script"/> component to this Entity.
		/// </summary>
		/// <param name="sclass">Script class that will be used to instantiate script in engine.</param>
		/// <param name="enabled">If set to false, the script will be in disabled state after creation. Otherwise it will be enabled.</param>
		/// <returns>Reference to added Script Component.</returns>
		Script& AddScript(Scripting::ScriptClass sclass, bool enabled = true);

		/// <summary>
		/// Returns name of this Entity.
		/// Can be used to distinguish entities and search for them on the <see cref="Scene"/>.
		/// </summary>
		/// <returns>Name of this Entity.</returns>
		const std::string& GetName() const;

		/// <summary>
		/// Sets name of this Entity.
		/// Can be used to distinguish entities and search for them on the <see cref="Scene"/>.
		/// </summary>
		/// <param name="name">Name to set.</param>
		void SetName(const std::string& name);
	};
}

#include "Entity.inl"

#endif // !ENGINEQ_ENTITY_HPP
