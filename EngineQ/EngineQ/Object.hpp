#ifndef ENGINEQ_QOBJECT_H
#define ENGINEQ_QOBJECT_H

#include "Immovable.hpp"
#include "Scripting/ScriptEngine.hpp"

namespace EngineQ
{
	class Object : public Immovable
	{
	protected:
		const Scripting::ScriptHandle managedHandle;
		Scripting::ScriptEngine& scriptEngine;

	public:
		Object(Scripting::ScriptEngine& scriptEngine, Scripting::ScriptClass sclass);
		virtual ~Object();

		Object* GetNativeObject(Scripting::ScriptObject managed) const;
		Scripting::ScriptObject GetManagedObject() const;
		Scripting::ScriptClass GetManagedClass() const;

		const Scripting::ScriptEngine& GetScriptEngine() const;
	};
}

#endif // !ENGINEQ_QOBJECT_H
