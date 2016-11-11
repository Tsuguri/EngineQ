#include "Light.hpp"

#include "../Scripting/ScriptEngine.hpp"
#include "../Serialization/Serializer.hpp"
#include "../Serialization/Deserializer.hpp"

namespace EngineQ
{
	/*
#pragma region Serialization

	Light::Light(Serialization::Deserializer& deserialzier) :
		Component{ deserialzier }
	{
	}

	void Light::Serialize(Serialization::Serializer& serializer) const
	{
		Component::Serialize(serializer);
	}

#pragma endregion
	*/

	Light::Light(Scripting::ScriptEngine& scriptEngine, Entity& entity, bool enabled)
		: Component{ ComponentType::Light, scriptEngine, scriptEngine.GetClass(Scripting::ScriptEngine::Class::Light), entity, enabled }
	{
		// TMP
		scriptEngine.InvokeConstructor(GetManagedObject());
	}
}