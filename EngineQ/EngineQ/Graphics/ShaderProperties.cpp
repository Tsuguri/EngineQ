#include "ShaderProperties.hpp"

#include "GL/glew.h"

namespace EngineQ
{
	namespace Graphics
	{
		ShaderProperties::ShaderProperties(Shader& shader) :
			shader{ &shader }
		{
			GLint uniformCount;
			glGetProgramiv(shader.programId, GL_ACTIVE_UNIFORMS, &uniformCount);

			this->usedUniforms.reserve(uniformCount);

			for (int i = 0; i < uniformCount; ++i)
			{
				GLuint index = i;

				GLint nameLength;
				glGetActiveUniformsiv(shader.programId, 1, &index, GL_UNIFORM_NAME_LENGTH, &nameLength);

				std::string name(nameLength - 1, '_');

				GLsizei actualNameLength;
				glGetActiveUniformName(shader.programId, index, nameLength, &actualNameLength, &name[0]);

				auto location = shader.GetUniformLocation(name.c_str());

				GLint uniformType;
				glGetActiveUniformsiv(shader.programId, 1, &index, GL_UNIFORM_TYPE, &uniformType);

				UniformData* uniformData = nullptr;
				bool skip = false;

				switch (uniformType)
				{
					case GL_FLOAT:
					this->usedUniforms.emplace_back(location, static_cast<float>(0.0f));
					break;

					case GL_FLOAT_MAT4:
					this->usedUniforms.emplace_back(location, Math::Matrix4{});
					break;

					default:
					std::cout << "Unknown type " << uniformType << ": " << name << std::endl;
					skip = true;
					break;
				}

				if (skip)
					continue;

				uniformData = &this->usedUniforms.back();
				this->shaderUniforms.insert({ name, uniformData });
			}
		}

		void ShaderProperties::Apply() const
		{
			this->shader->Activate();
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

		template<>
		bool ShaderProperties::HasProperty<void>(const std::string& name) const
		{
			auto it = shaderUniforms.find(name);

			return it != shaderUniforms.end();
		}
	}
}