namespace EngineQ
{
	namespace Serialization
	{
		template<typename Type>
		SerializedObjectNode* Serializer::CreateReferencedNode(const Type& value)
		{
			void* id = SerializationEngine::GetId(&value);

			auto it = this->serializedObject->objects.insert(std::make_pair(id, std::make_unique<SerializedObjectNode>()));
			if (!it.second)
				throw std::runtime_error{ "Serialization error" };

			SerializedObjectNode* node = it.first->second.get();

			node->id = id;

			return node;
		}

		template<typename Type>
		std::unique_ptr<SerializedObjectNode> Serializer::CreateUnreferencedNode(const Type& value)
		{
			std::unique_ptr<SerializedObjectNode> node = std::make_unique<SerializedObjectNode>();

			return node;
		}

		template<typename Type>
		void Serializer::StoreReference(const std::string& name, const Type* reference)
		{
			if (reference == nullptr)
			{
				auto added = this->currentNode->references.insert(std::make_pair(name, nullptr));
				if (!added.second)
					throw std::logic_error{ "Value already added" };
			}
			else
			{
				void* id = SerializationEngine::GetId(reference);

				auto added = this->currentNode->references.insert(std::make_pair(name, id));
				if (!added.second)
					throw std::logic_error{ "Value already added" };

				auto it = this->serializedObject->objects.find(id);
				if (it == this->serializedObject->objects.end())
				{
					SerializedObjectNode* node = CreateReferencedNode(*reference);

					SerializedObjectNode* lastNode = this->currentNode;
					this->currentNode = node;

					SerializeValue(*reference, *this, this->currentNode->type, this->currentNode->value);

					this->currentNode = lastNode;
				}
			}
		}

		template<typename Type>
		void Serializer::StoreValueWithReference(const std::string& name, const Type* value)
		{
			auto found = this->currentNode->unreferencedValues.find(name);
			if (found != this->currentNode->unreferencedValues.end())
				throw std::logic_error{ "Value already added" };

			if (value == nullptr)
			{
				auto added = this->currentNode->referencedValues.insert(std::make_pair(name, nullptr));
				if (!added.second)
					throw std::logic_error{ "Value already added" };
			}
			else
			{
				SerializedObjectNode* node;
				void* id = SerializationEngine::GetId(value);

				auto it = this->serializedObject->objects.find(id);
				if (it != this->serializedObject->objects.end())
					throw std::logic_error{ "Value already added" };

				node = CreateReferencedNode(*value);
				node->byValue = true;
				node->dependsId = this->currentNode->id;

				auto added = this->currentNode->referencedValues.insert(std::make_pair(name, id));
				if (!added.second)
					throw std::logic_error{ "Value already added" };

				SerializedObjectNode* lastNode = this->currentNode;
				this->currentNode = node;

				SerializeValue(*value, *this, this->currentNode->type, this->currentNode->value);

				this->currentNode = lastNode;
			}
		}

		template<typename Type>
		void Serializer::StoreValue(const std::string& name, const Type* value)
		{
			auto found = this->currentNode->referencedValues.find(name);
			if (found != this->currentNode->referencedValues.end())
				throw std::logic_error{ "Value already added" };

			if (value == nullptr)
			{
				auto added = this->currentNode->unreferencedValues.insert(std::make_pair(name, nullptr));
				if (!added.second)
					throw std::logic_error{ "Value already added" };
			}
			else
			{
				std::unique_ptr<SerializedObjectNode> nodeUnique = CreateUnreferencedNode(*value);
				SerializedObjectNode* node = nodeUnique.get();

				auto added = this->currentNode->unreferencedValues.insert(std::make_pair(name, std::move(nodeUnique)));
				if (!added.second)
					throw std::logic_error{ "Value already added" };

				node->byValue = true;

				SerializedObjectNode* lastNode = this->currentNode;
				this->currentNode = node;

				SerializeValue(*value, *this, this->currentNode->type, this->currentNode->value);

				this->currentNode = lastNode;
			}
		}

		template<typename Type>
		std::shared_ptr<SerializedObject> Serializer::Serialize(const Type& serializable)
		{
			this->serializedObject = std::make_shared<SerializedObject>();

			this->currentNode = this->serializedObject->root = CreateReferencedNode(serializable);

			SerializeValue(serializable, *this, this->currentNode->type, this->currentNode->value);

			return this->serializedObject;
		}
	}
}