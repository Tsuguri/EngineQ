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
	class Entity : public Object
	{
		friend class Transform;

	private:
		std::vector<Component*> components;
		std::vector<Script*> updatable;

		Transform& transform;

	public:
		Entity(Scripting::ScriptEngine& scriptEngine);
		virtual ~Entity() override;
		Entity& operator = (const Entity& other) = delete;

		const Transform& GetTransform() const;
		Transform& GetTransform();

		void Update();

		int GetComponentsCount() const;
		Component* GetComponent(int index) const;

		template<typename Type>
		Type* AddComponent();

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