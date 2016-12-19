#ifndef ENGINEQ_SERIALIZATION_XML_FORMATTER_HPP
#define ENGINEQ_SERIALIZATION_XML_FORMATTER_HPP

// Standard includes
#include <string>
#include <memory>
#include <sstream>

// This project
#include "Formatter.hpp"


namespace tinyxml2
{
	class XMLDocument;
	class XMLElement;
}

namespace EngineQ
{
	namespace Serialization
	{
		class XMLFormatter : public Formatter
		{
			std::string AddressToString(void* address);
			void* StringToAddress(const char* text);

			void SaveObject(tinyxml2::XMLDocument& doc, tinyxml2::XMLElement* element, const SerializedObject& serializedObject, SerializedObjectNode* objectNode);
			void LoadObject(tinyxml2::XMLElement* element, SerializedObject* serializedObject, SerializedObjectNode* node);

		public:
			virtual void Save(const char* filename, const SerializedObject& serializedObject) override;
			virtual std::shared_ptr<SerializedObject> Load(const char* filename) override;
		};
	}
}

#endif // !ENGINEQ_SERIALIZATION_XML_FORMATTER_HPP
