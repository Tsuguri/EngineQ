#ifndef ENGINEQ_SERIALIZATION_DESERIALIZER_HPP
#define ENGINEQ_SERIALIZATION_DESERIALIZER_HPP

// Standard includes
#include <map>
#include <memory>

// This project
#include "Types.hpp"


namespace EngineQ
{
	namespace Serialization
	{
		class Deserializer
		{
			friend class Serializable;

		private:
			struct Data
			{
				std::map<void*, void*> createdObjects;
				std::map<std::string, void*> storageObjects;
				std::shared_ptr<SerializedObject> serializedObject;

				Data(std::shared_ptr<SerializedObject> serializedObject);
			};

			std::shared_ptr<Data> data;
			SerializedObjectNode* currentNode;
			void* alternativePlace = nullptr;

			Deserializer(Deserializer& deserializer, SerializedObjectNode* node);

			void* GetReferenceToReference(SerializedObjectNode* node);
			void* GetReferenceToValue(const std::string& name, SerializedObjectNode* node);
			void RegisterObject(Serializable* object);

		public:
			Deserializer(std::shared_ptr<SerializedObject> serializedObject);

			template<typename Type>
			void AddStorage(const std::string& name, Type* object);
			
			template<typename Type>
			Type* GetStorage(const std::string& name);

			template<typename Type>
			Type* Deserialize();

			template<typename Type>
			Type* GetReference(const std::string& name);

			template<typename Type>
			Type GetValue(const std::string& name, const Type& value);

			template<typename Type>
			Type GetValue(const std::string& name);

			Deserializer CreateValue(const std::string& name);

			const std::string& GetValue();
		};
	}
}

#include "Deserializer.inl"

#endif // !ENGINEQ_SERIALIZATION_DESERIALIZER_HPP
