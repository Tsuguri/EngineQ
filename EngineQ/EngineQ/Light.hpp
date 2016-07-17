#ifndef ENGINEQ_LIGHT_HPP
#define ENGINEQ_LIGHT_HPP

#include "Component.hpp"

namespace EngineQ
{
	class Light : public Component
	{
	public:
	#pragma region Serialization

		Light(Serialization::Deserializer& deserialzier);
		virtual void Serialize(Serialization::Serializer& serializer) const override;

	#pragma endregion

		Light(Scripting::ScriptEngine& scriptEngine, Entity& entity);

		virtual ComponentType GetType() const override;
	};
}

#endif // !ENGINEQ_LIGHT_HPP
