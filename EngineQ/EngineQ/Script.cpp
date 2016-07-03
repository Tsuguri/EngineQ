#include "Script.hpp"

namespace EngineQ
{
	Script::Script(Scripting::ScriptEngine& scriptEngine, Entity& entity, Scripting::ScriptClass sclass)
		: Component{ scriptEngine, sclass, entity }
	{
		updateMethod = scriptEngine.GetScriptUpdateMethod(sclass, scriptEngine.GetInstance(managedHandle));
	}

	ComponentType Script::GetType() const
	{
		return ComponentType::Script;
	}

	void Script::Update()
	{
		scriptEngine.InvokeMethod(managedHandle, updateMethod, nullptr);
	}

	bool Script::IsUpdateble()
	{
		return updateMethod != nullptr;
	}
}