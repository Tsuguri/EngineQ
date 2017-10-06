// This project
#include "Serializer.hpp"
#include "Deserializer.hpp"


namespace EngineQ
{
	namespace Serialization
	{
		template<typename Type>
		void SerializeValue(const std::vector<Type*>& value, Serializer& serializer, std::string& type, std::string& serializedValue)
		{
			std::size_t size = value.size();
			serializer.StoreValue("size", &size);
			for (std::size_t i = 0; i < size; ++i)
				serializer.StoreReference("element" + std::to_string(i), value[i]);
		}

		template<typename Type>
		std::vector<Type*> DeserializeValue(Deserializer& deserializer, const std::vector<Type*>*)
		{
			std::size_t size = deserializer.GetValue<std::size_t>("size");
			std::vector<Type*> value;
			value.reserve(size);

			for (std::size_t i = 0; i < size; ++i)
				value.push_back(deserializer.GetReference<Type>("element" + std::to_string(i)));

			return value;
		}


		template<typename Type>
		void SerializeValue(const std::vector<Type>& value, Serializer& serializer, std::string& type, std::string& serializedValue)
		{
			std::size_t size = value.size();
			serializer.StoreValue("size", &size);
			for (std::size_t i = 0; i < size; ++i)
				serializer.StoreValue("element" + std::to_string(i), &value[i]);
		}

		template<typename Type>
		std::vector<Type> DeserializeValue(Deserializer& deserializer, const std::vector<Type>*)
		{
			std::size_t size = deserializer.GetValue<std::size_t>("size");
			std::vector<Type> value;
			value.reserve(size);

			for (std::size_t i = 0; i < size; ++i)
				value.push_back(deserializer.GetValue<Type>("element" + std::to_string(i)));

			return value;
		}
	}
}