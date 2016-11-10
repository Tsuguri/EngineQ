#ifndef ENGINEQ_SCRIPT_HPP
#define ENGINEQ_SCRIPT_HPP

#include "Component.hpp"

//	#include "../Utilities/Emiter.hpp"

namespace EngineQ
{
	class Script final : public Component
	{
	private:
		Scripting::ScriptMethod activateMethod;
		Scripting::ScriptMethod enabledMethod;
		Scripting::ScriptMethod updateMethod;
		Scripting::ScriptMethod disabledMethod;
		Scripting::ScriptMethod deactivateMethod;

		bool isActivated = false;

	protected:
		virtual void OnEnabledChanged(bool enabled) override;

		void OnActivate();
		void OnEnable();
		void OnDisable();
		void OnDeactivate();

	public:
		/*
	#pragma region Serialization

		Script(Serialization::Deserializer& deserialzier);
		virtual void Serialize(Serialization::Serializer& serializer) const override;

	#pragma endregion
		*/

		Script(Scripting::ScriptEngine& scriptEngine, Entity& entity, Scripting::ScriptClass sclass, bool enabled);

		void OnUpdate();
		
		bool IsUpdateble();

		virtual ~Script();
	};
}

#endif // !ENGINEQ_SCRIPT_HPP
