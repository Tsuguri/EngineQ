namespace EngineQ
{
	namespace Graphics
	{
		template<typename TType>
		ShaderProperty<TType> ShaderProperties::CreateMockUniform(const TType& defaultValue)
		{
			this->mockUniforms.emplace_back(std::make_unique<UniformData>(defaultValue));
			auto& mockUniform = this->mockUniforms.back();
			return mockUniform->GetProperty<TType>();
		}

		template< typename TPropertyType>
		void ShaderProperties::CheckBuiltIn(ShaderProperty<TPropertyType>& property, const TPropertyType& defaultValue)
		{
			if (!property.IsSet())
				property = this->CreateMockUniform<TPropertyType>(defaultValue);
			else
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

			return uniformData.TryGetProperty<TType>();
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

		template<typename TType>
		std::vector<std::pair<std::string, ShaderProperty<TType>>> ShaderProperties::GetAllProperties()
		{
			std::vector<std::pair<std::string, ShaderProperty<TType>>> result;

			for (const auto& nameIndex : this->shaderUniformsMap)
			{
				auto& uniformProperty = this->shaderUniforms[nameIndex.second];
			
				auto property = uniformProperty.second.TryGetProperty<TType>();
				if (property != nullval)
					result.emplace_back(nameIndex.first, *property);
			}

			return result;
		}
	}
}