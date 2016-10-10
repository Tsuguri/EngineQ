namespace EngineQ
{
	namespace Graphics
	{
		template<typename TType>
		ShaderProperty<TType> ShaderProperties::GetProperty(const std::string& name) const
		{
			return shaderUniforms.at(name)->GetProperty<TType>();
		}

		template<typename TType>
		bool ShaderProperties::HasProperty(const std::string& name) const
		{
			auto it = shaderUniforms.find(name);
			if (it == shaderUniforms.end())
				return false;

			return it->second->IsType<TType>();
		}
	}
}