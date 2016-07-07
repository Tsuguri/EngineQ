#ifndef ENGINEQ_LIGHT_HPP
#define ENGINEQ_LIGHT_HPP

#include "Component.hpp"

namespace EngineQ
{
	class Light : public Component
	{
	public:
		Light(Scripting::ScriptEngine& scriptEngine, Entity& entity);

		virtual ComponentType GetType() const override;
	};
}

#endif // !ENGINEQ_LIGHT_HPP
