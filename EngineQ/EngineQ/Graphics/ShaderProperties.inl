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

		template<typename TGroupType, typename TPropertyType>
		void ShaderProperties::CheckBuiltIn(TGroupType& group, ShaderProperty<TPropertyType>(TGroupType::* member))
		{
			if (!(group.*member).IsSet())
				(group.*member) = this->CreateMockUniform<TPropertyType>();
		}

		template<typename TType>
		ShaderProperty<TType> ShaderProperties::GetProperty(const std::string& name) const
		{
			return shaderUniformsMap.at(name)->GetProperty<TType>();
		}

		template<typename TType>
		bool ShaderProperties::HasProperty(const std::string& name) const
		{
			auto it = shaderUniformsMap.find(name);
			if (it == shaderUniformsMap.end())
				return false;

			return it->second->IsType<TType>();
		}
	}
}