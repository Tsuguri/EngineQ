#ifndef ENGINEQ_GRAPHICS_SHADER_UNIFORM_DATA_HPP
#define ENGINEQ_GRAPHICS_SHADER_UNIFORM_DATA_HPP

#include "../Utilities/Metaprogramming.hpp"
#include "ShaderExceptions.hpp"

#include "UniformLocation.hpp"
#include "ShaderProperty.hpp"
#include "Shader.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		template<typename TType>
		struct ShaderUniformActions
		{
			static void Apply(Shader& shader, UniformLocation location, const void* value)
			{
				shader.Bind(location, *static_cast<const TType*>(value));
			}
		};

		template<typename... TArgs>
		class ShaderUniformData
		{
			static_assert(!Meta::HasDuplicate<TArgs...>::value, "Type list contains duplicates");

		private:
			using ApplyActionType = void(*)(Shader&, UniformLocation, const void*);

			static constexpr ApplyActionType ApplyActions[] = { &ShaderUniformActions<TArgs>::Apply... };

			// Uniform information
			UniformLocation location;
			std::size_t type;

			// Data
			char data[Meta::MaxTypeSize<TArgs...>::value];

			template<typename TType>
			inline void StaticCheck() const
			{
				static_assert(Meta::ContainsType<TType, TArgs...>::value, "Type not supported");
			}

			template<typename TType>
			inline void DynamicCheck() const
			{
				if (this->type != Meta::TypeIndex<TType, TArgs...>::value)
					throw InvalidUniformTypeException{ "Invalid type" };
			}

		public:
			template<typename TType>
			ShaderUniformData(UniformLocation location, const TType& value) :
				location{ location }, type{ Meta::TypeIndex<TType, TArgs...>::value }
			{
				this->StaticCheck<TType>();

				new (this->data)TType{ value };
			}

			void Apply(Shader& shader) const
			{
				ApplyActions[type](shader, this->location, static_cast<const void*>(data));
			}

			template<typename TType>
			bool IsType() const
			{
				return this->type == Meta::TypeIndex<TType, TArgs...>::value;
			}

			template<typename TType>
			TType Get() const
			{
				this->StaticCheck<TType>();
				this->DynamicCheck<TType>();

				return *reinterpret_cast<const TType*>(data);
			}

			template<typename TType>
			void Set(const TType& value)
			{
				this->StaticCheck<TType>();
				this->DynamicCheck<TType>();

				*reinterpret_cast<TType*>(data) = value;
			}

			template<typename TType>
			ShaderProperty<TType> GetProperty()
			{
				this->StaticCheck<TType>();
				this->DynamicCheck<TType>();

				return ShaderProperty<TType>{ *reinterpret_cast<TType*>(data) };
			}
		};

		template<typename... TArgs>
		constexpr typename ShaderUniformData<TArgs...>::ApplyActionType ShaderUniformData<TArgs...>::ApplyActions[];

	}
}

#endif // !ENGINEQ_GRAPHICS_SHADER_UNIFORM_DATA_HPP
