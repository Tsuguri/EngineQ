#ifndef ENGINEQ_COMPONENT_HPP
#define ENGINEQ_COMPONENT_HPP

// This project
#include "Object.hpp"


namespace EngineQ
{
	class Entity;

	/// <summary>
	/// Specifies all types of supported components.
	/// </summary>
	enum class ComponentType
	{
		Transform,
		Camera,
		Light,
		Script,
		Renderable,
	};

	/// <summary>
	/// Base class for all components that can be added to the <see cref="EngineQ::Entity"/>.
	/// </summary>
	/// <seealso cref="Transform"/>
	/// <seealso cref="Camera"/>
	/// <seealso cref="Light"/>
	/// <seealso cref="Renderable"/>
	/// <seealso cref="Script"/>
	class Component : public Object
	{
	public:
		/// <summary>
		/// Class providing interface methods exposed only to <see cref="EngineQ::Entity"/> class.
		/// </summary>
		class EntityCallbacks
		{
			friend class Entity;

		private:
			static void OnEnabledChanged(Component& component, bool enabled);
		};

	protected:
		Entity& entity;

	private:
		bool enabled = true;
		bool parentEnabled = true;
		const ComponentType type;


		void SetParentEnabled(bool enabled);

	protected:
		virtual void OnEnabledChanged(bool enabled);

	public:
		/*
	#pragma region Serialization

		Component(Serialization::Deserializer& deserialzier, ComponentType type);
		virtual void Serialize(Serialization::Serializer& serializer) const override;

	#pragma endregion
		*/

		Component(ComponentType type, Scripting::ScriptEngine& scriptEngine, Scripting::ScriptClass sclass, Entity& entity, bool enabled);
		virtual ~Component();
		
		/// <summary>
		/// Returns Entity owning this Component.
		/// </summary>
		/// <returns>Entity owning this Component.</returns>
		Entity& GetEntity();

		/// <summary>
		/// Returns Entity owning this Component.
		/// </summary>
		/// <returns>Entity owning this Component.</returns>
		const Entity& GetEntity() const;

		/// <summary>
		/// Specifies whether the Component is enabled. 
		/// When set to false, the Component will be disabled.
		/// Disabled components have no effect on its' parent <see cref="EngineQ::Entity"/>.
		/// </summary>
		/// <returns>true if component is enabled.</returns>
		bool IsEnabled() const;

		/// <summary>
		/// Sets whether the Component is enabled. 
		/// When set to false, the Component will be disabled.
		/// Disabled components have no effect on its' parent <see cref="EngineQ::Entity"/>.
		/// </summary>
		/// <param name="enabled">Value to set. true to enable, false to disable.</param>
		void SetEnabled(bool enabled);

		/// <summary>
		/// Specifies whether the Component is enabled in hierarchy.
		/// Component can be disabled if it is disabled itself (<see cref="Enabled"/> is set to false), or it's parent <see cref="EngineQ::Entity"/> is disabled in hierarchy (<see cref="EngineQ::Entity::EnabledInHierarchy"/> is set to false).
		/// Disabled Components have no effect on its' parent <see cref="EngineQ::Entity"/>.
		/// </summary>
		/// <returns>true if component is enabled in hierarchy.</returns>
		bool IsEnabledInHierarchy() const;

		/// <summary>
		/// Returns this component type.
		/// </summary>
		/// <returns>This component type.</returns>
		ComponentType GetType() const;
	};
}

#endif // !ENGINEQ_COMPONENT_HPP
