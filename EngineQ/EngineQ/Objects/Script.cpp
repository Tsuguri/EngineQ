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

		this->createMethod = scriptEngine.GetScriptCreateMethod(sclass, instance);
		this->activateMethod = scriptEngine.GetScriptActivateMethod(sclass, instance);
		this->enabledMethod = scriptEngine.GetScriptEnableMethod(sclass, instance);
		this->updateMethod = scriptEngine.GetScriptUpdateMethod(sclass, instance);
		this->disabledMethod = scriptEngine.GetScriptDisableMethod(sclass, instance);
		this->deactivateMethod = scriptEngine.GetScriptDeactivateMethod(sclass, instance);
		this->destroyMethod = scriptEngine.GetScriptDestroyMethod(sclass, instance);
	}

	void Script::OnCreate()
	{
		if (this->created)
			throw std::logic_error{ "Object already created" };

		if (this->createMethod != nullptr)
			scriptEngine.InvokeMethod(this->managedHandle, this->createMethod, nullptr);

		if (this->IsEnabledInHierarchy())
		{
			this->OnActivate();
			this->OnEnable();
		}

		this->created = true;
	}

	void Script::OnActivate()
	{
		if (this->activated)
			return;

		if (this->activateMethod != nullptr)
			scriptEngine.InvokeMethod(this->managedHandle, this->activateMethod, nullptr);

		this->activated = true;
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
		if (!this->activated)
			return;

		if (this->deactivateMethod != nullptr)
			scriptEngine.InvokeMethod(this->managedHandle, this->deactivateMethod, nullptr);
	}

	void Script::OnDestroy()
	{
		if (this->destroyMethod != nullptr)
			scriptEngine.InvokeMethod(this->managedHandle, this->destroyMethod, nullptr);
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
		this->OnDestroy();
	}
}