#ifndef ENGINEQ_ENTITY_HPP
#define ENGINEQ_ENTITY_HPP

#include <vector>

#include "Types.hpp"

#include "Object.hpp"

namespace EngineQ
{
	class Entity : public Object
	{
		friend class Transform;
		friend class Scene;

	private:
		Scene& scene;

		bool isRemoveLocked = false;

		std::vector<Component*> components;
		std::vector<Script*> updatable;

		std::vector<Component*> componentsToDelete;

		Transform& transform;

		Entity(Scene& scene, Scripting::ScriptEngine& scriptEngine);

		void LockRemove();
		void UnlockRemove();

		void RemoveComponent_Internal(Component& component, std::vector<Component*>::iterator it);

		void Update();

		void AddComponent(Component* component);

	public:
	#pragma region Serialization

		Entity(Serialization::Deserializer& deserialzier);
		virtual void Serialize(Serialization::Serializer& serializer) const override;

	#pragma endregion

		virtual ~Entity() override;

		const Scene& GetScene() const;
		Scene& GetScene();

		const Transform& GetTransform() const;
		Transform& GetTransform();



		std::size_t GetComponentsCount() const;
		Component* GetComponent(std::size_t index) const;

		template<typename Type>
		Type* AddComponent();
		void RemoveComponent(Component& component);

		std::size_t GetComponentIndex(Component* component) const;

		Script* AddScript(Scripting::ScriptClass sclass);
	};
}

namespace EngineQ
{
	template<typename Type>
	Type* Entity::AddComponent()
	{
		Type* component = new Type{ this->scriptEngine, *this };

		this->AddComponent(component);

		return component;
	}
}

#endif // !ENGINEQ_ENTITY_HPP
