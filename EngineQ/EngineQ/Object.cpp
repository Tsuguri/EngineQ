#include "Object.hpp"

namespace EngineQ
{
	Object::Object(Scripting::ScriptEngine& scriptEngine, Scripting::ScriptClass sclass)
		: scriptEngine{ scriptEngine }, managedHandle{ scriptEngine.CreateObject(sclass, this) }
	{

	}

	Object::~Object()
	{
		scriptEngine.DestroyObject(this->managedHandle);
	}

	Object* Object::GetNativeObject(Scripting::ScriptObject managed) const
	{
		return this->scriptEngine.GetNativeHandle(managed);
	}

	Scripting::ScriptObject Object::GetManagedObject() const
	{
		return this->scriptEngine.GetInstance(this->managedHandle);
	}

	Scripting::ScriptClass Object::GetManagedClass() const
	{
		return scriptEngine.GetObjectClass(scriptEngine.GetInstance(managedHandle));
	}

	const Scripting::ScriptEngine& Object::GetScriptEngine() const
	{
		return this->scriptEngine;
	}
}