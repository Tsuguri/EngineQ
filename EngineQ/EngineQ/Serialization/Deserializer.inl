namespace EngineQ
{
	namespace Serialization
	{
		template<typename Type>
		void Deserializer::AddStorage(const std::string& name, Type* object)
		{
			auto added = this->data->storageObjects.insert(std::make_pair(name, static_cast<void*>(object)));
			if (!added.second)
				throw std::logic_error{ "Storage with name " + name + " is already taken" };
		}

		template<typename Type>
		Type* Deserializer::GetStorage(const std::string& name)
		{
			return static_cast<Type*>(this->data->storageObjects.at(name));
		}

		template<typename Type>
		Type* Deserializer::Deserialize()
		{
			return new Type{ *this };
		}

		template<typename Type>
		Type* Deserializer::GetReference(const std::string& name)
		{
			void* id = this->currentNode->references.at(name);
			if (id == nullptr)
				return nullptr;

			SerializedObjectNode* node = this->data->serializedObject->objects.at(id).get();

			auto it = this->data->createdObjects.find(node->id);
			// Object found
			if (it != this->data->createdObjects.end())
				return SerializationEngine::GetAddress<Type>(it->second);

			if (node->byValue)
				return SerializationEngine::GetAddress<Type>(GetReferenceToValue(name, node));
			else
				return SerializationEngine::GetAddress<Type>(GetReferenceToReference(node));
		}

		template<typename Type>
		Type Deserializer::GetValue(const std::string& name, const Type& value)
		{
			SerializedObjectNode* node = this->data->serializedObject->objects.at(this->currentNode->referencedValues.at(name)).get();

			auto it = this->data->createdObjects.find(node->id);
			// Object found
			if (it != this->data->createdObjects.end())
				throw std::runtime_error{ "Value already exists" };

			// Object not found
			this->data->createdObjects.insert(std::make_pair(node->id, SerializationEngine::GetId(&value)));

			Deserializer deserializer{ *this, node };
			return DeserializeValue(deserializer, static_cast<const Type*>(nullptr));
		}

		template<typename Type>
		Type Deserializer::GetValue(const std::string& name)
		{
			SerializedObjectNode* node = this->currentNode->unreferencedValues.at(name).get();
			
			Deserializer deserializer{ *this, node };
			return DeserializeValue(deserializer, static_cast<const Type*>(nullptr));
		}
	}
}