#include "ShaderProperties.hpp"

#include "GL/glew.h"

namespace EngineQ
{
	namespace Graphics
	{
		ShaderProperties::ShaderProperties(Shader& shader) :
			shader{ shader }
		{
			GLint uniformCount;
			glGetProgramiv(shader.programId, GL_ACTIVE_UNIFORMS, &uniformCount);

			this->usedUniforms.reserve(uniformCount);

			std::vector<GLint> nameLengths(uniformCount);
			std::vector<GLint> uniformTypes(uniformCount);

			std::vector<GLuint> uniformIndices(uniformCount);
			for (int i = 0; i < uniformCount; ++i)
				uniformIndices[i] = i;

			glGetActiveUniformsiv(shader.programId, uniformCount, uniformIndices.data(), GL_UNIFORM_NAME_LENGTH, nameLengths.data());
			glGetActiveUniformsiv(shader.programId, uniformCount, uniformIndices.data(), GL_UNIFORM_TYPE, uniformTypes.data());

			for (int i = 0; i < uniformCount; ++i)
			{
				std::string name(nameLengths[i] - 1, ' ');
				glGetActiveUniformName(shader.programId, uniformIndices[i], nameLengths[i], nullptr, &name[0]);

				UniformLocation location = shader.GetUniformLocation(name.c_str());
				auto uniformData = UniformData::FromTypeIndex(location, uniformTypes[i]);

				if (uniformData != nullval)
				{
					this->usedUniforms.push_back(*uniformData);

					UniformData* uniformData = &this->usedUniforms.back();
					this->shaderUniforms.insert({ name, uniformData });
				}
				else
				{
					// TMP
					std::cout << "Type " << uniformTypes[i] << " of property " << name << " is not supported" << std::endl;
				}
			}
		}

		void ShaderProperties::Apply() const
		{
			this->shader.Activate();
			for (const auto& uniform : usedUniforms)
				uniform.Apply(shader);
		}

		void ShaderProperties::SetBuildInProperty(int value)
		{
			this->builtInProperty = value;
		}

		int ShaderProperties::GetBuildInProperty() const
		{
			return this->builtInProperty;
		}

		template<>
		bool ShaderProperties::HasProperty<void>(const std::string& name) const
		{
			auto it = shaderUniforms.find(name);

			return it != shaderUniforms.end();
		}
	}
}