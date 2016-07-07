#ifndef ENGINEQ_MODEL_HPP
#define ENGINEQ_MODEL_HPP
#include "Component.hpp"

namespace EngineQ
{
	class Model : public EngineQ::Component
	{
	public:
		Model(Scripting::ScriptEngine& scriptEngine, Entity& entity);
		virtual ComponentType GetType() const override;

	};
}
#endif
