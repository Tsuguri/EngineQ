#ifndef ENGINEQ_SCRIPT_HPP
#define ENGINEQ_SCRIPT_HPP

#include "Component.hpp"

namespace EngineQ
{
	class Script final : public Component
	{
	private:
		Scripting::ScriptMethod updateMethod;

	public:
	#pragma region Serialization

		Script(Serialization::Deserializer& deserialzier);
		virtual void Serialize(Serialization::Serializer& serializer) const override;

	#pragma endregion

		Script(Scripting::ScriptEngine& scriptEngine, Entity& entity, Scripting::ScriptClass sclass);

		virtual ComponentType GetType() const override;

		void Update();
		bool IsUpdateble();
	};
}

#endif // !ENGINEQ_SCRIPT_HPP
