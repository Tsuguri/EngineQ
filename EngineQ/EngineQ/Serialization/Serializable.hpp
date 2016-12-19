#ifndef ENGINEQ_SERIALIZATION_SERIALIZABLE_HPP
#define ENGINEQ_SERIALIZATION_SERIALIZABLE_HPP

// This project
#include "Types.hpp"


namespace EngineQ
{
	namespace Serialization
	{
		class Serializable
		{
		protected:
			Serializable();
			Serializable(Deserializer& deserializer);

		public:
			virtual void Serialize(Serializer& serializer) const;
		};
	}
}

#endif // !ENGINEQ_SERIALIZATION_SERIALIZABLE_HPP
