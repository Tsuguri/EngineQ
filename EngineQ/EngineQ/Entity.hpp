#ifndef ENGINEQ_ENTITY_H
#define ENGINEQ_ENTITY_H

#include <cstdint>
#include <vector>

#include "Object.hpp"
#include "Transform.hpp"
#include "Scripting/ScriptEngine.hpp"
#include "Script.hpp"

namespace EngineQ
{
	class Scene;

	class Entity : public Object
	{
		friend class Transform;
		friend class Scene;

	private:
		Scene& scene;

		std::vector<Component*> components;
		std::vector<Script*> updatable;

		Transform& transform;

		Entity(Scene& scene, Scripting::ScriptEngine& scriptEngine);

	public:
		virtual ~Entity() override;
	
		const Scene& GetScene() const;
		Scene& GetScene();

		const Transform& GetTransform() const;
		Transform& GetTransform();

		void Update();

		int GetComponentsCount() const;
		Component* GetComponent(int index) const;

		template<typename Type>
		Type* AddComponent();
		void RemoveComponent(Component& component);

		Script* AddScript(Scripting::ScriptClass sclass);
	};
}

namespace EngineQ
{
	template<typename Type>
	Type* Entity::AddComponent()
	{
		Type* component = new Type{ this->scriptEngine, *this };

		components.push_back(component);

		return component;
	}
}

#endif // !ENGINEQ_ENTITY_H