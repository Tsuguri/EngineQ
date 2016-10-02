#include "Deserializer.hpp"

namespace EngineQ
{
	namespace Serialization
	{
		Deserializer::Data::Data(std::shared_ptr<SerializedObject> serializedObject) :
			serializedObject{ serializedObject }
		{
		}

		Deserializer::Deserializer(Deserializer& deserializer, SerializedObjectNode* node) :
			data{ deserializer.data }, currentNode{ node }
		{
		}

		void* Deserializer::GetReferenceToReference(SerializedObjectNode* node)
		{
			// Create object
			SerializedObjectNode* oldNode = this->currentNode;
			this->currentNode = node;

			void* object = SerializationEngine::FindType(this->currentNode->type).constructor(*this);

			this->currentNode = oldNode;

			return object;
		}

		void* Deserializer::GetReferenceToValue(const std::string& name, SerializedObjectNode* node)
		{
			// Create depended object
			SerializedObjectNode* dependedNode = this->data->serializedObject->objects.at(node->dependsId).get();

			if (dependedNode->byValue)
				throw std::logic_error{ "Invalid declaration order of \"" + name + "\" in \"" + dependedNode->type + "\"" };

			auto it2 = this->data->createdObjects.find(node->dependsId);
			if (it2 != this->data->createdObjects.end())
				throw std::logic_error{ "Invalid declaration order of \"" + name + "\" in \"" + dependedNode->type + "\"" };

			// Create depended object cont...
			GetReferenceToReference(dependedNode);

			auto it3 = this->data->createdObjects.find(node->id);
			// Object not found
			if (it3 == this->data->createdObjects.end())
				throw std::runtime_error{ "Object not found" };

			return it3->second;
		}

		void Deserializer::RegisterObject(Serializable* object)
		{
			if (this->alternativePlace != nullptr)
			{
				auto ret = this->data->createdObjects.insert(std::make_pair(this->currentNode->id, this->alternativePlace));
				this->alternativePlace = nullptr;

				if (!ret.second)
					throw std::runtime_error{ "Object already created" };
			}
			else
			{
				auto ret = this->data->createdObjects.insert(std::make_pair(this->currentNode->id, object));

				if (!ret.second)
					throw std::runtime_error{ "Object already created" };
			}
		}

		Deserializer::Deserializer(std::shared_ptr<SerializedObject> serializedObject) :
			data{ std::make_shared<Data>(serializedObject) }, currentNode{ serializedObject->root }
		{

		}

		Deserializer Deserializer::CreateValue(const std::string& name)
		{
			auto ref = this->currentNode->referencedValues.find(name);
			auto unref = this->currentNode->unreferencedValues.find(name);

			bool refNot = (ref == this->currentNode->referencedValues.end());
			bool unrefNot = (unref == this->currentNode->unreferencedValues.end());

			if (refNot && unrefNot)
				throw std::logic_error{ "Value " + name + " not found" };

			SerializedObjectNode* node;
			if (!refNot)
				node = this->data->serializedObject->objects.at(ref->second).get();
			else
				node = unref->second.get();

			return Deserializer{ *this, node };
		}

		const std::string& Deserializer::GetValue()
		{
			return this->currentNode->value;
		}
	}
}