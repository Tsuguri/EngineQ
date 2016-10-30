namespace EngineQ
{
	namespace Graphics
	{
		template<typename TType>
		ShaderProperty<TType> ShaderProperties::CreateMockUniform()
		{
			this->mockUniforms.emplace_back(TType{});
			auto& mockUniform = this->mockUniforms.back();
			return mockUniform.GetProperty<TType>();
		}

		template< typename TPropertyType>
		void ShaderProperties::CheckBuiltIn(ShaderProperty<TPropertyType>& property, const TPropertyType& defaultValue)
		{
			if (!property.IsSet())
				property = this->CreateMockUniform<TPropertyType>();

			property = defaultValue;
		}

		template<typename TType>
		ShaderProperty<TType> ShaderProperties::GetProperty(const std::string& name)
		{
			int index = this->shaderUniformsMap.at(name);
			UniformData& uniformData = this->shaderUniforms[index].second;
			return uniformData.GetProperty<TType>();
		}

		template<typename TType>
		Utilities::Nullable<ShaderProperty<TType>> ShaderProperties::TryGetProperty(const std::string& name)
		{
			auto it = this->shaderUniformsMap.find(name);
			if (it == this->shaderUniformsMap.end())
				return nullval;

			UniformData& uniformData = this->shaderUniforms[it->second].second;

			if (!uniformData.IsType<TType>())
				return nullval;

			return uniformData.GetProperty<TType>();
		}

		template<typename TType>
		bool ShaderProperties::HasProperty(const std::string& name) const
		{
			auto it = this->shaderUniformsMap.find(name);
			if (it == this->shaderUniformsMap.end())
				return false;

			const UniformData& uniformData = this->shaderUniforms[it->second].second;
			return uniformData.IsType<TType>();
		}

		template<typename TType>
		int ShaderProperties::GetPropertyIndex(const std::string& name) const
		{
			auto it = this->shaderUniformsMap.find(name);
			if (it == this->shaderUniformsMap.end())
				return -1;

			auto index = it->second;
			const UniformData& uniformData = this->shaderUniforms[index].second;
			if (!uniformData.IsType<TType>())
				return -1;

			return static_cast<int>(index);
		}

		template<typename TType>
		void ShaderProperties::Set(int index, const TType& value)
		{
			return this->shaderUniforms[index].second.Set(value);
		}

		template<typename TType>
		TType ShaderProperties::Get(int index) const
		{
			return this->shaderUniforms[index].second.Get<TType>();
		}
	}
}