#ifndef ENGINEQ_SERIALIZATION_SERIALIZATION_RULES_HPP
#define ENGINEQ_SERIALIZATION_SERIALIZATION_RULES_HPP

#include <sstream>
#include <vector>

#include "Serializer.hpp"
#include "Deserializer.hpp"
#include "Serializable.hpp"

namespace EngineQ
{
	namespace Serialization
	{
		void SerializeValue(const std::string& value, Serializer& serializer, std::string& type, std::string& serializedValue);
		std::string DeserializeValue(Deserializer& deserializer, const std::string*);

		void SerializeValue(int value, Serializer& serializer, std::string& type, std::string& serializedValue);
		int DeserializeValue(Deserializer& deserializer, const int*);

		void SerializeValue(std::size_t value, Serializer& serializer, std::string& type, std::string& serializedValue);
		std::size_t DeserializeValue(Deserializer& deserializer, const std::size_t*);

		void SerializeValue(float value, Serializer& serializer, std::string& type, std::string& serializedValue);
		float DeserializeValue(Deserializer& deserializer, const float*);

		template<typename Type>
		void SerializeValue(const std::vector<Type*>& value, Serializer& serializer, std::string& type, std::string& serializedValue);
		template<typename Type>
		std::vector<Type*> DeserializeValue(Deserializer& deserializer, const std::vector<Type*>*);

		template<typename Type>
		void SerializeValue(const std::vector<Type>& value, Serializer& serializer, std::string& type, std::string& serializedValue);
		template<typename Type>
		std::vector<Type> DeserializeValue(Deserializer& deserializer, const std::vector<Type>*);
	}
}

#include "SerializationRules.inl"

#endif // !ENGINEQ_SERIALIZATION_SERIALIZATION_RULES_HPP
