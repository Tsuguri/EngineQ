#include "Serializer.hpp"

namespace EngineQ
{
	namespace Serialization
	{
		void SerializeValue(const Serializable& serializable, Serializer& serializer, std::string& type, std::string& serializedValue)
		{
			type = SerializationEngine::GetType(serializable).name;
			serializable.Serialize(serializer);
		}
	}
}