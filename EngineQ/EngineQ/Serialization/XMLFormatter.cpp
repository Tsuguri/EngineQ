#include "XMLFormatter.hpp"

#include <Libraries/TinyXML/tinyxml2.h>

#include "SerializedObject.hpp"

namespace EngineQ
{
	namespace Serialization
	{
		using namespace tinyxml2;

		std::string XMLFormatter::AddressToString(void* address)
		{
			std::stringstream stream;
			stream << address;
			return stream.str();
		}

		void* XMLFormatter::StringToAddress(const char* text)
		{
			void* value;
			std::stringstream stream;
			stream << text;
			stream >> value;
			return value;
		}

		void XMLFormatter::SaveObject(XMLDocument& doc, XMLElement* element, const SerializedObject& serializedObject, SerializedObjectNode* objectNode)
		{
			if (objectNode->type != "")
				element->SetAttribute("type", objectNode->type.c_str());

			if (objectNode->id != nullptr)
				element->SetAttribute("id", AddressToString(objectNode->id).c_str());

			if (objectNode->byValue)
			{
				if (objectNode->dependsId != nullptr)
					element->SetAttribute("dependedId", AddressToString(objectNode->dependsId).c_str());

				if (objectNode->value != "")
					element->SetText(objectNode->value.c_str());
			}

			for (auto& ref : objectNode->references)
			{
				XMLElement* childElement = doc.NewElement(ref.first.c_str());
				element->InsertEndChild(childElement);

				childElement->SetAttribute("refId", AddressToString(ref.second).c_str());
			}
			for (auto& refVal : objectNode->referencedValues)
			{
				XMLElement* childElement = doc.NewElement(refVal.first.c_str());
				element->InsertEndChild(childElement);

				SerializedObjectNode* child = serializedObject.objects.at(refVal.second).get();
				SaveObject(doc, childElement, serializedObject, child);
			}
			for (auto& urefVal : objectNode->unreferencedValues)
			{
				XMLElement* childElement = doc.NewElement(urefVal.first.c_str());
				element->InsertEndChild(childElement);

				SerializedObjectNode* child = urefVal.second.get();
				SaveObject(doc, childElement, serializedObject, child);
			}
		}

		void XMLFormatter::LoadObject(XMLElement* element, SerializedObject* serializedObject, SerializedObjectNode* node)
		{
			const char* refIdElement = element->Attribute("refId");
			// Reference
			if (refIdElement != nullptr)
			{
				auto added = node->references.insert(std::make_pair(element->Name(), StringToAddress(refIdElement)));
				if (!added.second)
					throw std::runtime_error{ std::string{ "Cannot add " } +element->Name() + " reference" };

				return;
			}

			// Value

			const char* idElement = element->Attribute("id");

			std::unique_ptr<SerializedObjectNode> newNode = std::make_unique<SerializedObjectNode>();
			newNode->byValue = true;

			const char* text = element->GetText();
			// Simple type
			if (text != nullptr)
			{
				newNode->value = text;
			}
			else
			{
				for (XMLElement* child = element->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
				{
					LoadObject(child, serializedObject, newNode.get());
				}
			}

			// Unreferenced value
			if (idElement == nullptr)
			{
				node->unreferencedValues.insert(std::make_pair(element->Name(), std::move(newNode)));
			}
			// Referenced value
			else
			{
				newNode->id = StringToAddress(idElement);

				const char* type = element->Attribute("type");
				if (type != nullptr)
					newNode->type = type;

				const char* dependedId = element->Attribute("dependedId");
				if (dependedId != nullptr)
					newNode->dependsId = StringToAddress(dependedId);

				node->referencedValues.insert(std::make_pair(element->Name(), newNode->id));
				serializedObject->objects.insert(std::make_pair(newNode->id, std::move(newNode)));
			}
		}

		void XMLFormatter::Save(const char* filename, const SerializedObject& serializedObject)
		{
			XMLDocument doc{};

			XMLNode* rootNode = doc.NewElement("SerializedObject");
			doc.InsertFirstChild(rootNode);

			for (auto& object : serializedObject.objects)
			{
				if (object.second->byValue)
					continue;

				SerializedObjectNode* node = object.second.get();
				XMLElement* element = doc.NewElement("Object");
				rootNode->InsertEndChild(element);

				SaveObject(doc, element, serializedObject, node);
			}

			XMLElement* element = doc.NewElement("Root");
			rootNode->InsertFirstChild(element);

			element->SetAttribute("refId", AddressToString(serializedObject.root->id).c_str());

			doc.SaveFile(filename);
		}

		std::shared_ptr<SerializedObject> XMLFormatter::Load(const char* filename)
		{
			std::shared_ptr<SerializedObject> serializedObject = std::make_shared<SerializedObject>();

			XMLDocument doc;
			doc.LoadFile(filename);

			XMLElement* root = doc.RootElement();

			void* rootId;

			for (XMLElement* element = root->FirstChildElement(); element != nullptr; element = element->NextSiblingElement())
			{
				if (std::strcmp(element->Name(), "Root") == 0)
				{
					const char* refId = element->Attribute("refId");
					if (refId == nullptr)
						throw std::runtime_error{ "Loading error" };

					rootId = StringToAddress(refId);
					continue;
				}

				std::unique_ptr<SerializedObjectNode> node = std::make_unique<SerializedObjectNode>();

				const char* type = element->Attribute("type");
				if (type != nullptr)
					node->type = type;

				const char* id = element->Attribute("id");
				if (id != nullptr)
					node->id = StringToAddress(id);

				for (XMLElement* child = element->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
				{
					LoadObject(child, serializedObject.get(), node.get());
				}

				serializedObject->objects.insert(std::make_pair(node->id, std::move(node)));
			}

			serializedObject->root = serializedObject->objects.at(rootId).get();

			return serializedObject;
		}
	}
}