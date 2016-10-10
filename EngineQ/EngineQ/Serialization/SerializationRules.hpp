#ifndef ENGINEQ_SERIALIZATION_SERIALIZATION_RULES_HPP
#define ENGINEQ_SERIALIZATION_SERIALIZATION_RULES_HPP

#include <cstddef>
#include <string>
#include <vector>

#include "Types.hpp"
#include "../Math/Types.hpp"

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

		void SerializeValue(bool value, Serializer& serializer, std::string& type, std::string& serializedValue);
		bool DeserializeValue(Deserializer& deserializer, const bool*);

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

		void SerializeValue(Math::Vector3 value, Serializer& serializer, std::string& type, std::string& serializedValue);
		Math::Vector3 DeserializeValue(Deserializer& deserializer, const Math::Vector3*);

		void SerializeValue(Math::Quaternion value, Serializer& serializer, std::string& type, std::string& serializedValue);
		Math::Quaternion DeserializeValue(Deserializer& deserializer, const Math::Quaternion*);

		void SerializeValue(Math::Matrix4 value, Serializer& serializer, std::string& type, std::string& serializedValue);
		Math::Matrix4 DeserializeValue(Deserializer& deserializer, const Math::Matrix4*);
	}
}

#include "SerializationRules.inl"

#endif // !ENGINEQ_SERIALIZATION_SERIALIZATION_RULES_HPP
