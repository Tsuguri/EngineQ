#include "ShaderProperties.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		ShaderProperties::ShaderProperties(Shader& shader) :
			shader{ &shader }
		{

		}

		void ShaderProperties::Apply() const
		{
			for (const auto& uniform : usedUniforms)
				uniform.Apply(*shader);
		}

		void ShaderProperties::SetBuildInProperty(int value)
		{
			this->builtInProperty = value;
		}

		int ShaderProperties::GetBuildInProperty() const
		{
			return this->builtInProperty;
		}
	}
}