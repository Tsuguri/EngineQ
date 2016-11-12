#ifndef ENGINEQ_QOBJECT_HPP
#define ENGINEQ_QOBJECT_HPP

#include "../Serialization/Types.hpp"
#include "../Scripting/Types.hpp"

#include <Utilities/Immovable.hpp>
#include "../Serialization/Serializable.hpp"

namespace EngineQ
{
	class Object : public Serialization::Serializable, private Utilities::Immovable
	{
	protected:
		Scripting::ScriptEngine& scriptEngine;
	
	private:
		Scripting::ScriptClass sclass;
	
	protected:
		const Scripting::ScriptHandle managedHandle;

	public:
		/*
	#pragma region Serialization
		
		Object(Serialization::Deserializer& deserializer);
		virtual void Serialize(Serialization::Serializer& serializer) const override;

	#pragma endregion
		*/

		Object(Scripting::ScriptEngine& scriptEngine, Scripting::ScriptClass sclass);
		virtual ~Object();

		Object* GetNativeObject(Scripting::ScriptObject managed) const;
		Scripting::ScriptObject GetManagedObject() const;
		Scripting::ScriptClass GetManagedClass() const;

		const Scripting::ScriptEngine& GetScriptEngine() const;
	};
}

#endif // !ENGINEQ_QOBJECT_HPP
