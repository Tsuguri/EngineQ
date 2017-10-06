#ifndef ENGINEQ_SERIALIZATION_SERIALIZER_HPP
#define ENGINEQ_SERIALIZATION_SERIALIZER_HPP

// Standard includes
#include <memory>
#include <string>

// This project
#include "Types.hpp"


namespace EngineQ
{
	namespace Serialization
	{
		class Serializer
		{
		private:
			std::shared_ptr<SerializedObject> serializedObject;
			SerializedObjectNode* currentNode;

			template<typename Type>
			SerializedObjectNode* CreateReferencedNode(const Type& value);

			template<typename Type>
			std::unique_ptr<SerializedObjectNode> CreateUnreferencedNode(const Type& value);

		public:
			template<typename Type>
			void StoreReference(const std::string& name, const Type* reference);

			template<typename Type>
			void StoreValueWithReference(const std::string& name, const Type* value);

			template<typename Type>
			void StoreValue(const std::string& name, const Type* value);

			template<typename Type>
			std::shared_ptr<SerializedObject> Serialize(const Type& serializable);
		};

		void SerializeValue(const Serializable& serializable, Serializer& serializer, std::string& type, std::string& serializedValue);
	}
}

#include "Serializer.inl"

#endif // !ENGINEQ_SERIALIZATION_SERIALIZER_HPP
