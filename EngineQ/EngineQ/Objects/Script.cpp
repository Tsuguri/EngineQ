#include "Script.hpp"

#include "../Scripting/ScriptEngine.hpp"

namespace EngineQ
{
	/*
#pragma region Serialization

	Script::Script(Serialization::Deserializer& deserialzier) :
		Component{ deserialzier, ComponentType::Script }
	{
		updateMethod = scriptEngine.GetScriptUpdateMethod(this->GetManagedClass(), scriptEngine.GetInstance(managedHandle));
	}

	void Script::Serialize(Serialization::Serializer& serializer) const
	{
		Component::Serialize(serializer);
	}

#pragma endregion
	*/

	Script::Script(Scripting::ScriptEngine& scriptEngine, Entity& entity, Scripting::ScriptClass sclass, bool enabled)
		: Component{ ComponentType::Script, scriptEngine, sclass, entity, enabled }
	{
		auto instance = scriptEngine.GetInstance(managedHandle);

		this->activateMethod = scriptEngine.GetScriptActivatedMethod(sclass, instance);
		this->enabledMethod = scriptEngine.GetScriptEnabledMethod(sclass, instance);
		this->updateMethod = scriptEngine.GetScriptUpdateMethod(sclass, instance);
		this->disabledMethod = scriptEngine.GetScriptDisabledMethod(sclass, instance);
		this->deactivateMethod = scriptEngine.GetScriptDeactivatedMethod(sclass, instance);

		if (this->IsEnabledInHierarchy())
		{
			this->OnActivate();
			this->OnEnable();
		}
	}

	void Script::OnActivate()
	{
		if (this->isActivated)
			return;

		if (this->activateMethod != nullptr)
			scriptEngine.InvokeMethod(this->managedHandle, this->activateMethod, nullptr);

		this->isActivated = true;
	}

	void Script::OnEnable()
	{
		if (this->enabledMethod != nullptr)
			scriptEngine.InvokeMethod(this->managedHandle, this->enabledMethod, nullptr);
	}

	void Script::OnUpdate()
	{
		scriptEngine.InvokeMethod(this->managedHandle, this->updateMethod, nullptr);
	}

	void Script::OnDisable()
	{
		if (this->disabledMethod != nullptr)
			scriptEngine.InvokeMethod(this->managedHandle, this->disabledMethod, nullptr);
	}

	void Script::OnDeactivate()
	{
		if (!this->isActivated)
			return;

		if (this->deactivateMethod != nullptr)
			scriptEngine.InvokeMethod(this->managedHandle, this->deactivateMethod, nullptr);
	}

	bool Script::IsUpdateble()
	{
		return this->updateMethod != nullptr;
	}

	void Script::OnEnabledChanged(bool enabled)
	{
		if (enabled)
		{
			this->OnActivate();
			this->OnEnable();
		}
		else
		{
			this->OnDisable();
		}
	}

	Script::~Script()
	{
		if (this->IsEnabledInHierarchy())
			this->OnDisable();

		this->OnDeactivate();
	}
}