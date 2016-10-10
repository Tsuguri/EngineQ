#ifndef ENGINEQ_GRAPHICS_SHADER_PROPERTY_HPP
#define ENGINEQ_GRAPHICS_SHADER_PROPERTY_HPP

namespace EngineQ
{
	namespace Graphics
	{
		template<typename TType>
		class ShaderProperty
		{
		private:
			TType* property = nullptr;

		public:
			ShaderProperty() = default;

			ShaderProperty(TType& property) :
				property{ &property }
			{
			}

			TType Get() const
			{
				return *this->property;
			}

			void Set(const TType& value)
			{
				*this->property = value;
			}

			ShaderProperty& operator = (const TType& value)
			{
				*this->property = value;
				return *this;
			}

			operator TType() const
			{
				return *this->property;
			}
		};
	}
}

#endif // !ENGINEQ_GRAPHICS_SHADER_PROPERTY_HPP
