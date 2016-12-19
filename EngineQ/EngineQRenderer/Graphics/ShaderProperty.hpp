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

			explicit ShaderProperty(TType& property) :
				property{ &property }
			{
			}

			bool IsSet() const
			{
				return (this->property != nullptr);
			}

			const TType& Get() const
			{
				return *this->property;
			}

			void Set(const TType& value) const
			{
				*this->property = value;
			}

			const ShaderProperty& operator = (const TType& value) const
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
