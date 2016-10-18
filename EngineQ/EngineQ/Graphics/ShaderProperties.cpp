#include "ShaderProperties.hpp"

#include "GL/glew.h"

#include "../Scripting/ScriptEngine.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		void ShaderProperties::FinalizeBuiltIn()
		{
			CheckBuiltIn(this->matrices, &Matrices::Model);
			CheckBuiltIn(this->matrices, &Matrices::View);
			CheckBuiltIn(this->matrices, &Matrices::Projection);

			CheckBuiltIn(this->material, &Material::Ambient);
			CheckBuiltIn(this->material, &Material::Diffuse);
			CheckBuiltIn(this->material, &Material::Specular);
			CheckBuiltIn(this->material, &Material::Shininess);

			for (auto& light : this->lights)
			{
				CheckBuiltIn(light, &Light::Position);
				CheckBuiltIn(light, &Light::Ambient);
				CheckBuiltIn(light, &Light::Diffuse);
				CheckBuiltIn(light, &Light::Specular);
				CheckBuiltIn(light, &Light::Distance);
				CheckBuiltIn(light, &Light::CastsShadows);
				CheckBuiltIn(light, &Light::FarPlane);
			}
		}


		void ShaderProperties::OnUniformAdded(UniformData& data, UniformType type, const std::string& name)
		{
			// TODO: Extract all built-in properties
			// we need to agree on standard uniforms names

			if (type == GL_FLOAT_MAT4 && name.find("matrices.") == 0)
			{
				if (name == "matrices.Model")
					this->matrices.Model = data.GetProperty<Math::Matrix4>();
				else if (name == "matrices.View")
					this->matrices.View = data.GetProperty<Math::Matrix4>();
				else if (name == "matrices.Projection")
					this->matrices.Projection = data.GetProperty<Math::Matrix4>();
			}

			switch (type)
			{
				case GL_FLOAT_VEC3:
				{
					if (name == "lightColor")
					{
						this->lights.emplace_back();
						auto& light = this->lights.back();
						light.Diffuse = data.GetProperty<Math::Vector3f>();
					}
				}
				break;

				default:
				break;
			}
		}

		ShaderProperties::ShaderProperties(Scripting::ScriptEngine& scriptEngine, Resources::Resource<Shader> shader) :
			Object{ scriptEngine, scriptEngine.GetClass(Scripting::ScriptEngine::Class::ShaderProperties) }, shader{ shader }
		{
			GLint uniformCount;
			glGetProgramiv(shader->programId, GL_ACTIVE_UNIFORMS, &uniformCount);

			this->shaderUniforms.reserve(uniformCount);

			std::vector<GLint> nameLengths(uniformCount);
			std::vector<GLint> uniformTypes(uniformCount);

			std::vector<GLuint> uniformIndices(uniformCount);
			for (int i = 0; i < uniformCount; ++i)
				uniformIndices[i] = i;

			glGetActiveUniformsiv(shader->programId, uniformCount, uniformIndices.data(), GL_UNIFORM_NAME_LENGTH, nameLengths.data());
			glGetActiveUniformsiv(shader->programId, uniformCount, uniformIndices.data(), GL_UNIFORM_TYPE, uniformTypes.data());

			for (int i = 0; i < uniformCount; ++i)
			{
				std::string uniformName(nameLengths[i] - 1, ' ');
				glGetActiveUniformName(shader->programId, uniformIndices[i], nameLengths[i], nullptr, &uniformName[0]);

				auto uniformData = UniformData::FromTypeIndex(uniformTypes[i]);

				if (uniformData != nullval)
				{
					UniformLocation location = shader->GetUniformLocation(uniformName.c_str());
					this->shaderUniforms.emplace_back(location, *uniformData);

					auto& uniformPair = this->shaderUniforms.back();
					this->shaderUniformsMap.emplace(uniformName, &uniformPair.second);

					this->OnUniformAdded(uniformPair.second, uniformTypes[i], uniformName);
				}
				else
				{
					// TMP
					std::cout << "Type " << uniformTypes[i] << " of property " << uniformName << " is not supported" << std::endl;
				}
			}

			this->FinalizeBuiltIn();
		}

		void ShaderProperties::Apply() const
		{
			this->shader->Activate();
			for (const auto& uniformPair : shaderUniforms)
				uniformPair.second.Apply(*shader, uniformPair.first);
		}

		const ShaderProperties::Matrices& ShaderProperties::GetMatrices()
		{
			return this->matrices;
		}

		const ShaderProperties::Material& ShaderProperties::GetMaterial()
		{
			return this->material;
		}

		const std::vector<ShaderProperties::Light>& ShaderProperties::GetLights()
		{
			return this->lights;
		}

		template<>
		bool ShaderProperties::HasProperty<void>(const std::string& name) const
		{
			auto it = shaderUniformsMap.find(name);

			return it != shaderUniformsMap.end();
		}
	}
}