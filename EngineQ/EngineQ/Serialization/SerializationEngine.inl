namespace EngineQ
{
	namespace Serialization
	{
		template<typename Type, bool serializable>
		inline void* SerializationEngine::SerializableResolver<Type, serializable>::GetId(const Type* value)
		{
			return static_cast<void*>(static_cast<Serializable*>(const_cast<Type*>(value)));
		}

		template<typename Type, bool serializable>
		inline Type* SerializationEngine::SerializableResolver<Type, serializable>::GetAddress(const void* address)
		{
			return static_cast<Type*>(static_cast<Serializable*>(const_cast<void*>(address)));
		}

		template<typename Type>
		inline void* SerializationEngine::SerializableResolver<Type, false>::GetId(const Type* value)
		{
			return static_cast<void*>(const_cast<Type*>(value));
		}

		template<typename Type>
		inline Type* SerializationEngine::SerializableResolver<Type, false>::GetAddress(const void* address)
		{
			return static_cast<Type*>(const_cast<void*>(address));
		}

		template<typename Type>
		void SerializationEngine::Register(const std::string& name)
		{
			std::type_index idx{ typeid(Type) };

			TypeInfo info{ name, [](Deserializer& deserializer) { return SerializationEngine::GetId(new Type{ deserializer }); } };

			SerializationEngine::types.insert(std::make_pair(idx, info));
		}

		template<typename Type>
		SerializationEngine::TypeInfo& SerializationEngine::GetType(const Type& value)
		{
			auto it = SerializationEngine::types.find(std::type_index{ typeid(value) });
			if (it == SerializationEngine::types.end())
				throw std::runtime_error{ std::string{ "Type " } +typeid(value).name() + " is not registered" };

			return it->second;
		}

		template<typename Type>
		SerializationEngine::TypeInfo& SerializationEngine::GetType()
		{
			auto it = SerializationEngine::types.find(std::type_index{ typeid(Type) });
			if (it == SerializationEngine::types.end())
				throw std::runtime_error{ std::string{ "Type " } +typeid(Type).name() + " is not registered" };

			return it->second;
		}

		template<typename Type>
		void* SerializationEngine::GetId(const Type* value)
		{
			return SerializableResolver<Type, std::is_assignable<Serializable*, Type*>::value>::GetId(value);
		}

		template<typename Type>
		Type* SerializationEngine::GetAddress(const void* value)
		{
			return SerializableResolver<Type, std::is_assignable<Serializable*, Type*>::value>::GetAddress(value);
		}
	}
}