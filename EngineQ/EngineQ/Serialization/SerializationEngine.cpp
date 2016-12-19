#include "SerializationEngine.hpp"


namespace EngineQ
{
	namespace Serialization
	{
		std::map<std::type_index, SerializationEngine::TypeInfo> SerializationEngine::types;
		SerializationEngine::Initializer SerializationEngine::initializer;

		SerializationEngine::Initializer::Initializer()
		{
		}

		SerializationEngine::TypeInfo::TypeInfo(const std::string& name, const std::function<void*(Deserializer&)>& constructor) :
			name{ name }, constructor{ constructor }
		{
		}

		SerializationEngine::TypeInfo& SerializationEngine::FindType(const std::string& name)
		{
			for (auto& typeInfo : SerializationEngine::types)
				if (typeInfo.second.name == name)
					return typeInfo.second;

			throw std::logic_error{ "Type " + name + " not found" };
		}
	}
}