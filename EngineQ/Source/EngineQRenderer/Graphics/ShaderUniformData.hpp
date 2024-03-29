#ifndef ENGINEQ_GRAPHICS_SHADER_UNIFORM_DATA_HPP
#define ENGINEQ_GRAPHICS_SHADER_UNIFORM_DATA_HPP

// Standard includes
#include <array>
#include <unordered_map>

// Other projects
#include "EngineQCommon/Utilities/Metaprogramming.hpp"
#include "EngineQCommon/Utilities/Nullable.hpp"
#include "EngineQCommon/Resources/Resource.hpp"

// This project
#include "ShaderExceptions.hpp"
#include "UniformLocation.hpp"
#include "ShaderProperty.hpp"
#include "Shader.hpp"


namespace EngineQ
{
	namespace Graphics
	{
		using UniformType = GLint;

		template<typename TType>
		struct ShaderUniformActions
		{
			static void Apply(Shader& shader, UniformLocation location, const void* value)
			{
				shader.Bind(location, *static_cast<const TType*>(value));
			}

			static void Create(char* data)
			{
				new(data) TType{};
			}

			static void Destruct(char* data)
			{
				Utilities::ObjectDestructor<TType>::Destruct(*reinterpret_cast<TType*>(data));
			}

			static void Assign(char* lhs, const char* rhs)
			{
				*reinterpret_cast<TType*>(lhs) = *reinterpret_cast<const TType*>(rhs);
			}
		};

		template<typename TType>
		struct ShaderUniformActions<Resources::Resource<TType>>
		{
			using Type = Resources::Resource<TType>;

			static void Apply(Shader& shader, UniformLocation location, const void* value)
			{
				const Type& ptr = *static_cast<const Type*>(value);
				shader.Bind(location, ptr);
			}

			static void Create(char* data)
			{
				new(data) Type{};
			}

			static void Destruct(char* data)
			{
				Utilities::ObjectDestructor<Type>::Destruct(*reinterpret_cast<Type*>(data));
			}

			static void Assign(char* lhs, const char* rhs)
			{
				*reinterpret_cast<Type*>(lhs) = *reinterpret_cast<const Type*>(rhs);
			}
		};

		template<UniformType VFirst, typename TSecond>
		struct Pair
		{
			static constexpr UniformType First = VFirst;
			using Second = TSecond;
		};

		template<typename TType>
		struct IsPair
		{
			static constexpr bool value = false;
		};

		template<UniformType VFirst, typename TSecond>
		struct IsPair<Pair<VFirst, TSecond>>
		{
			static constexpr bool value = true;
		};


		template<typename... TArgs>
		class ShaderUniformData
		{
			static_assert(sizeof...(TArgs) > 0, "List must contain at least one element");

			static_assert(Meta::SatisfyConcept<IsPair, TArgs...>::value, "Types must be of type Pair<>");
			static_assert(!Meta::HasDuplicateTypes<typename TArgs::Second...>::value, "Type list contains duplicate types");
			static_assert(!Meta::HasDuplicateValues<UniformType, TArgs::First...>::value, "Value list contains duplicate values");


		private:
			using ApplyActionType = void(*)(Shader&, UniformLocation, const void*);
			using DestructActionType = void(*)(char*);
			using ConstructActionType = void(*)(char*);
			using AssignActionType = void(*)(char*, const char*);
			using ConstructorsMapType = const std::unordered_map<UniformType, std::pair<std::size_t, ConstructActionType>>;

			static constexpr std::size_t DataSize = Meta::MaxTypeSize<typename TArgs::Second...>::value;

			static constexpr AssignActionType AssingActions[] = { &ShaderUniformActions<typename TArgs::Second>::Assign... };
			static constexpr ApplyActionType ApplyActions[] = { &ShaderUniformActions<typename TArgs::Second>::Apply... };
			static constexpr DestructActionType DestructActions[] = { &ShaderUniformActions<typename TArgs::Second>::Destruct... };
			

			static ConstructorsMapType ConstructorsMap;

			std::size_t type;
			std::array<char, DataSize> data;


			template<typename TType>
			inline void StaticCheck() const
			{
				static_assert(Meta::ContainsType<TType, typename TArgs::Second...>::value, "Type not supported");
			}

			template<typename TType>
			inline void DynamicCheck() const
			{
				if (this->type != Meta::TypeIndex<TType, typename TArgs::Second...>::value)
					throw InvalidUniformTypeException{ "Invalid type" };
			}

			ShaderUniformData(std::size_t type, const std::array<char, DataSize>& data) :
				type{ type }, data{ data }
			{
			}

		public:
			template<typename TType>
			ShaderUniformData(const TType& value) :
				type{ Meta::TypeIndex<TType, typename TArgs::Second...>::value }
			{
				this->StaticCheck<TType>();

				new(this->data.data()) TType{ value };
			}

			~ShaderUniformData()
			{
				DestructActions[this->type](this->data.data());
			}

			ShaderUniformData& operator = (const ShaderUniformData& other)
			{
				AssingActions[this->type](this->data.data(), other.data.data());
				return *this;
			}

			void Apply(Shader& shader, UniformLocation location) const
			{
				ApplyActions[this->type](shader, location, static_cast<const void*>(this->data.data()));
			}

			template<typename TType>
			bool IsType() const
			{
				return this->type == Meta::TypeIndex<TType, typename TArgs::Second...>::value;
			}

			template<typename TType>
			TType Get() const
			{
				this->StaticCheck<TType>();
				this->DynamicCheck<TType>();

				return *reinterpret_cast<const TType*>(data.data());
			}

			template<typename TType>
			TType& GetRef()
			{
				this->StaticCheck<TType>();
				this->DynamicCheck<TType>();

				return *reinterpret_cast<const TType*>(data.data());
			}

			template<typename TType>
			void Set(const TType& value)
			{
				this->StaticCheck<TType>();
				this->DynamicCheck<TType>();

				*reinterpret_cast<TType*>(data.data()) = value;
			}

			template<typename TType>
			ShaderProperty<TType> GetProperty()
			{
				this->StaticCheck<TType>();
				this->DynamicCheck<TType>();

				return ShaderProperty<TType>{ *reinterpret_cast<TType*>(data.data()) };
			}

			template<typename TType>
			Utilities::Nullable<ShaderProperty<TType>> TryGetProperty()
			{
				if (this->IsType<TType>())
					return ShaderProperty<TType>{ *reinterpret_cast<TType*>(data.data()) };

				return nullval;
			}
			
			static Utilities::Nullable<ShaderUniformData> FromTypeIndex(UniformType typeIndex)
			{
				auto constructIt = ConstructorsMap.find(typeIndex);
				if (constructIt == ConstructorsMap.end())
					return nullval;

				std::size_t type = constructIt->second.first;
				std::array<char, DataSize> data;

				constructIt->second.second(data.data());

				return ShaderUniformData{ type, data };
			}
		};

		template<typename... TArgs>
		constexpr typename ShaderUniformData<TArgs...>::AssignActionType ShaderUniformData<TArgs...>::AssingActions[];

		template<typename... TArgs>
		constexpr typename ShaderUniformData<TArgs...>::ApplyActionType ShaderUniformData<TArgs...>::ApplyActions[];

		template<typename... TArgs>
		constexpr typename ShaderUniformData<TArgs...>::DestructActionType ShaderUniformData<TArgs...>::DestructActions[];

		template<typename... TArgs>
		const typename ShaderUniformData<TArgs...>::ConstructorsMapType ShaderUniformData<TArgs...>::ConstructorsMap = {
			{ TArgs::First,{ Meta::TypeIndex<typename TArgs::Second, typename TArgs::Second...>::value, &ShaderUniformActions<typename TArgs::Second>::Create } }...
		};
	}
}

#endif // !ENGINEQ_GRAPHICS_SHADER_UNIFORM_DATA_HPP
