#include "ShaderProperties.hpp"

#include <Libraries/GL/glew.h>


#include <Utilities/StringHelpers.hpp>

namespace EngineQ
{
	namespace Graphics
	{
		Resources::Resource<Shader> ShaderProperties::GetShader() const
		{
			return this->shader;
		}


		void ShaderProperties::FinalizeBuiltIn()
		{
			CheckBuiltIn(this->matrices.Model, Math::Matrix4::GetIdentity());
			CheckBuiltIn(this->matrices.View, Math::Matrix4::GetIdentity());
			CheckBuiltIn(this->matrices.Projection, Math::Matrix4::GetIdentity());

			CheckBuiltIn(this->material.Ambient, Math::Vector3(0.05f));
			CheckBuiltIn(this->material.Diffuse, Math::Vector3f(0.5f));
			CheckBuiltIn(this->material.Specular, Math::Vector3f(0.5f));
			CheckBuiltIn(this->material.Shininess, 32.0f);

			for (auto& light : this->lights)
			{
				CheckBuiltIn(light.Position);
				CheckBuiltIn(light.Ambient);
				CheckBuiltIn(light.Diffuse);
				CheckBuiltIn(light.Specular);
				CheckBuiltIn(light.Diffuse);
				CheckBuiltIn(light.CastsShadows);
				CheckBuiltIn(light.FarPlane);
			}
		}


		void ShaderProperties::OnUniformAdded(UniformData& data, UniformType type, const std::string& name, const std::string& translatedName)
		{
			// TODO: Extract all built-in properties
			// we need to agree on standard uniforms names

			if (type == GL_FLOAT_MAT4 && translatedName.find("matrices.") == 0)
			{
				auto property = data.GetProperty<Math::Matrix4>();

				if (translatedName == "matrices.model")
					this->matrices.Model = property;
				else if (translatedName == "matrices.view")
					this->matrices.View = property;
				else if (translatedName == "matrices.projection")
					this->matrices.Projection = property;
			}

			if (translatedName.find("material.") == 0)
			{
				if (type == GL_FLOAT_VEC3)
				{
					auto property = data.GetProperty<Math::Vector3f>();

					if (translatedName == "material.diffuse")
						this->material.Diffuse = property;
					else if (translatedName == "material.specular")
						this->material.Specular = property;
					else if (translatedName == "material.ambient")
						this->material.Ambient = property;
				}
				else if (type == GL_FLOAT)
				{
					auto property = data.GetProperty<float>();

					if (translatedName == "material.shininess")
						this->material.Shininess = property;
				}
				else if (type == GL_SAMPLER_2D)
				{
					auto property = data.GetProperty<Resources::Resource<Texture>>();

					if (translatedName == "material.diffuseTexture")
						this->material.DiffuseTexture = property;
					else if (translatedName == "material.specularTexture")
						this->material.SpecularTexture = property;
					else if (translatedName == "material.normalTexture")
						this->material.NormalTexture = property;
				}
			}

			if (translatedName.find("lights") == 0)
			{
				int index = 0;

				int startIndex = translatedName.find("[");
				int endIndex = translatedName.find("]");
				auto indexString = translatedName.substr(startIndex + 1, endIndex - startIndex -1);
				index = std::stoi(indexString);

				while (index >= lights.size())
					lights.push_back(Light{});
				if (translatedName.find("specular")!= std::string::npos)
				{
					auto property = data.GetProperty<Math::Vector3f>();
					lights[index].Specular = property;
				}
				else if (translatedName.find("ambient") != std::string::npos)
				{
					auto property = data.GetProperty<Math::Vector3f>();
					lights[index].Ambient = property;
				}
				else if (translatedName.find("diffuse") != std::string::npos)
				{
					auto property = data.GetProperty<Math::Vector3f>();
					lights[index].Diffuse = property;
				}
				else if (translatedName.find("position") != std::string::npos)
				{
					auto property = data.GetProperty<Math::Vector3f>();
					lights[index].Position = property;
				}
				else if (translatedName.find("lightMatrix") != std::string::npos)
				{
					auto property = data.GetProperty<Math::Matrix4>();
					lights[index].LightMatrix = property;
				}
			/*	else if (translatedName.find("shadowMap") != std::string::npos)
				{
					auto property = data.GetProperty<Resources::Resource<Texture>>();
					lights[index].ShadowMap = property;
				}*/
				
			}
		}

		std::string ShaderProperties::TranslateName(std::string name) const
		{
			constexpr const char markerText[] = "_q_";
			constexpr std::size_t markerSize = sizeof(markerText) - 1;

			std::size_t lastPos = 0;
			std::size_t pos = name.find(markerText);

			while (pos != std::string::npos)
			{
				// Nothing after
				if (pos + markerSize == name.size())
					break;

				// Array
				if (Utilities::IsDigit(name[pos + markerSize]))
				{
					name[pos] = '[';
					lastPos = name.size();

					for (std::size_t i = pos + markerSize; i < name.size(); ++i)
					{
						if (!Utilities::IsDigit(name[i]))
						{
							lastPos = i;
							break;
						}

						name[i - (markerSize - 1)] = name[i];
					}

					lastPos -= markerSize - 1;
					name[lastPos] = ']';
					for (std::size_t i = lastPos + (markerSize - 1); i < name.size(); ++i)
						name[i - (markerSize - 2)] = name[i];

					name.resize(name.size() - (markerSize - 2));
				}
				// Struct
				else
				{
					name[pos] = '.';
					for (std::size_t i = pos + markerSize; i < name.size(); ++i)
						name[i - (markerSize - 1)] = name[i];

					name.resize(name.size() - (markerSize - 1));
					lastPos = pos + 1;
				}

				pos = name.find(markerText, lastPos);
			}

			return name;
		}

		ShaderProperties::ShaderProperties(Resources::Resource<Shader> shader) :
			shader{ shader }
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
					std::string translatedName = this->TranslateName(uniformName);

					UniformLocation location = shader->GetUniformLocation(uniformName.c_str());
					this->shaderUniforms.emplace_back(location, *uniformData);

					auto& uniformPair = this->shaderUniforms.back();
					this->shaderUniformsMap.emplace(translatedName, this->shaderUniforms.size() - 1);

					this->OnUniformAdded(uniformPair.second, uniformTypes[i], uniformName, translatedName);

					// TMP
					std::cout << "SP: Added property: " << translatedName;
					if (translatedName != uniformName)
						std::cout << " (" << uniformName << ")";
					std::cout << std::endl;
				}
				else
				{
					// TMP
					std::cout << "SP: Type " << uniformTypes[i] << " of property " << uniformName << " is not supported" << std::endl;
				}
			}

			this->FinalizeBuiltIn();


		}

		void ShaderProperties::Apply() const
		{
			this->shader->Reset();
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