namespace EngineQ
{
	namespace Graphics
	{
		template<typename TType>
		ShaderProperty<TType> ShaderProperties::GetProperty(const std::string& name) const
		{
			shaderUniforms.at(name)->GetProperty<TType>();
		}

		template<typename TType>
		bool ShaderProperties::HasProperty(const std::string& name) const
		{
			auto it = shaderUniforms.find(name);
			if (it == shaderUniforms.end())
				return false;

			return it->second->IsType<TType>();
		}

		template<>
		bool ShaderProperties::HasProperty<void>(const std::string& name) const
		{
			auto it = shaderUniforms.find(name);

			return it != shaderUniforms.end();
		}
	}
}