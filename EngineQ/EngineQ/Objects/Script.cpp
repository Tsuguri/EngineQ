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

	Script::Script(Scripting::ScriptEngine& scriptEngine, Entity& entity, Scripting::ScriptClass sclass)
		: Component{ ComponentType::Script, scriptEngine, sclass, entity }
	{
		updateMethod = scriptEngine.GetScriptUpdateMethod(sclass, scriptEngine.GetInstance(managedHandle));
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