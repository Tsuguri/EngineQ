#ifndef ENGINEQ_SERIALIZATION_SERIALIZED_OBJECT_HPP
#define ENGINEQ_SERIALIZATION_SERIALIZED_OBJECT_HPP

#include <map>
#include <memory>
#include <string>

namespace EngineQ
{
	namespace Serialization
	{
		class SerializedObjectNode
		{
		public:
			std::string type;
			void* id = nullptr;

			std::string value;
			bool byValue = false;
			void* dependsId = nullptr;

			std::map<std::string, void*> referencedValues;
			std::map<std::string, void*> references;
			std::map<std::string, std::unique_ptr<SerializedObjectNode>> unreferencedValues;
		};

		struct SerializedObject
		{
			SerializedObjectNode* root;

			std::map<void*, std::unique_ptr<SerializedObjectNode>> objects;
		};
	}
}

#endif // !ENGINEQ_SERIALIZATION_SERIALIZED_OBJECT_HPP
