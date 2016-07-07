#ifndef ENGINEQ_QOBJECT_HPP
#define ENGINEQ_QOBJECT_HPP

#include "Utilities/Immovable.hpp"
#include "Scripting/ScriptEngine.hpp"

namespace EngineQ
{
	class Object : public Utilities::Immovable
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

#endif // !ENGINEQ_QOBJECT_HPP
