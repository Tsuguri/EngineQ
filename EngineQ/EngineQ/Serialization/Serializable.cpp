#include "Serializable.hpp"

#include "Deserializer.hpp"

namespace EngineQ
{
	namespace Serialization
	{
		Serializable::Serializable()
		{
		}

		Serializable::Serializable(Deserializer& deserializer)
		{
			deserializer.RegisterObject(this);
		}

		void Serializable::Serialize(Serializer& serializer) const
		{
		}
	}
}