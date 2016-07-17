#include "Light.hpp"

#include "Serialization/SerializationRules.hpp"

namespace EngineQ
{
#pragma region Serialization

	Light::Light(Serialization::Deserializer& deserialzier) :
		Component{deserialzier}
	{
	}

	void Light::Serialize(Serialization::Serializer& serializer) const
	{
		Component::Serialize(serializer);
	}

#pragma endregion

	Light::Light(Scripting::ScriptEngine& scriptEngine, Entity& entity)
		: Component{scriptEngine, scriptEngine.GetLightClass(), entity }
	{
		// TMP
		scriptEngine.InvokeConstructor(GetManagedObject());
	}

	ComponentType Light::GetType() const
	{
		return ComponentType::Light;
	}
}