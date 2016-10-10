#include "Object.hpp"

#include "../Scripting/ScriptEngine.hpp"
#include "../Serialization/Serializer.hpp"
#include "../Serialization/Deserializer.hpp"
#include "../Serialization/SerializationRules.hpp"

namespace EngineQ
{
#pragma region Serialization

	Object::Object(Serialization::Deserializer& deserializer) : 
		Serialization::Serializable{ deserializer },
		scriptEngine{ *deserializer.GetStorage<Scripting::ScriptEngine>("scriptEngine") },
		sclass{ this->scriptEngine.GetClass(deserializer.GetValue<std::string>("cassembly"), deserializer.GetValue<std::string>("cnamespace"), deserializer.GetValue<std::string>("cname")) },
		managedHandle{ this->scriptEngine.CreateObject(this->sclass, this) }
	{
	}

	void Object::Serialize(Serialization::Serializer& serializer) const
	{
		std::string cassembly, cnamespace, cname;
		this->scriptEngine.GetClassDescription(this->sclass, cassembly, cnamespace, cname);

		serializer.StoreValue("cassembly", &cassembly);
		serializer.StoreValue("cnamespace", &cnamespace);
		serializer.StoreValue("cname", &cname);
	}

#pragma endregion

	Object::Object(Scripting::ScriptEngine& scriptEngine, Scripting::ScriptClass sclass)
		: scriptEngine{ scriptEngine }, sclass{ sclass }, managedHandle{ scriptEngine.CreateObject(sclass, this) }
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
		return this->sclass;
	}

	const Scripting::ScriptEngine& Object::GetScriptEngine() const
	{
		return this->scriptEngine;
	}
}