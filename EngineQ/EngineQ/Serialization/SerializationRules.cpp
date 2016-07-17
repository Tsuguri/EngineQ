#include "SerializationRules.hpp"

namespace EngineQ
{
	namespace Serialization
	{
		void SerializeValue(const std::string& value, Serializer& serializer, std::string& type, std::string& serializedValue)
		{
			serializedValue = value;
		}

		std::string DeserializeValue(Deserializer& deserializer, const std::string*)
		{
			return deserializer.GetValue();
		}


		void SerializeValue(int value, Serializer& serializer, std::string& type, std::string& serializedValue)
		{
			serializedValue = std::to_string(value);
		}

		int DeserializeValue(Deserializer& deserializer, const int*)
		{
			return std::stoi(deserializer.GetValue());
		}


		void SerializeValue(std::size_t value, Serializer& serializer, std::string& type, std::string& serializedValue)
		{
			serializedValue = std::to_string(value);
		}

		std::size_t DeserializeValue(Deserializer& deserializer, const std::size_t*)
		{
			std::size_t ret;
			std::stringstream stream;
			stream << deserializer.GetValue();
			stream >> ret;
			return ret;
		}


		void SerializeValue(float value, Serializer& serializer, std::string& type, std::string& serializedValue)
		{
			serializedValue = std::to_string(value);
		}

		float DeserializeValue(Deserializer& deserializer, const float*)
		{
			return std::stof(deserializer.GetValue());
		}
	}
}