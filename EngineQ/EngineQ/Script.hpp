#ifndef ENGINEQ_SCRIPT_H
#define ENGINEQ_SCRIPT_H

#include "Component.hpp"

namespace EngineQ
{
	class Script final : public Component
	{
	private:
		Scripting::ScriptMethod updateMethod;

	public:
		Script(Scripting::ScriptEngine& scriptEngine, Entity& entity, Scripting::ScriptClass sclass);

		virtual ComponentType GetType() const override;

		void Update();
		bool IsUpdateble();
	};
}

#endif // !ENGINEQ_SCRIPT_H