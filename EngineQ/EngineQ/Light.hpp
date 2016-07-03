#ifndef ENGINEQ_LIGHT_H
#define ENGINEQ_LIGHT_H

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

#endif // !ENGINEQ_LIGHT_H
