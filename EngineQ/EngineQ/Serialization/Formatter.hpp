#ifndef ENGINEQ_SERIALIZATION_FORMATTER_HPP
#define ENGINEQ_SERIALIZATION_FORMATTER_HPP

// Standard includes
#include <memory>

// This project
#include "Types.hpp"


namespace EngineQ
{
	namespace Serialization
	{
		class Formatter
		{
		public:
			virtual void Save(const char* filename, const SerializedObject& serializedObject) = 0;
			virtual std::shared_ptr<SerializedObject> Load(const char* flename) = 0;
		};
	}
}

#endif // !ENGINEQ_SERIALIZATION_FORMATTER_HPP
