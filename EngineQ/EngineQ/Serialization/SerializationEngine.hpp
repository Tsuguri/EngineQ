#ifndef ENGINEQ_SERIALIZATION_SERIALIZATION_ENGINE_HPP
#define ENGINEQ_SERIALIZATION_SERIALIZATION_ENGINE_HPP

#include <string>
#include <functional>
#include <map>
#include <typeinfo>
#include <typeindex>

namespace EngineQ
{
	namespace Serialization
	{
		class Serializer;
		class Deserializer;
		class Serializable;

		class SerializationEngine
		{
			friend class Serializer;
			friend class Deserializer;

		public:
			struct TypeInfo
			{
				const std::string name;
				const std::function<void*(Deserializer&)> constructor;

				TypeInfo(const std::string& name, const std::function<void*(Deserializer&)>& constructor);
			};

		private:
			struct Initializer
			{
				Initializer();
			};

			// Serializable
			template<typename Type, bool serializable>
			struct SerializableResolver
			{
				static inline void* GetId(const Type* value);
				static inline Type* GetAddress(const void* address);
			};

			// Non-Serializable
			template<typename Type>
			struct SerializableResolver<Type, false>
			{
				static inline void* GetId(const Type* value);
				static inline Type* GetAddress(const void* address);
			};

			static std::map<std::type_index, TypeInfo> types;
			static Initializer initializer;

		public:
			template<typename Type>
			static void Register(const std::string& name);

			template<typename Type>
			static TypeInfo& GetType(const Type& value);

			template<typename Type>
			static TypeInfo& GetType();

			static TypeInfo& FindType(const std::string& name);

			template<typename Type>
			static void* GetId(const Type* value);

			template<typename Type>
			static Type* GetAddress(const void* value);
		};
	}
}

#include "SerializationEngine.inl"

#endif // !ENGINEQ_SERIALIZATION_SERIALIZATION_ENGINE_HPP
