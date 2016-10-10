#ifndef ENGINEQ_GRAPHICS_SHADER_PROPERTIES_HPP
#define ENGINEQ_GRAPHICS_SHADER_PROPERTIES_HPP

#include <vector>
#include <map>

#include "Shader.hpp"
#include "ShaderUniformData.hpp"
#include "ShaderProperty.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		class ShaderProperties
		{
		private:
			using UniformData = ShaderUniformData<int, float>;
			
			Shader* shader;
			
			std::vector<UniformData> usedUniforms;
			std::map<std::string, UniformData*> shaderUniforms;


			// Build-in properties
			// TMP
			ShaderProperty<int> builtInProperty;

		public:
			ShaderProperties(Shader& shader);

			void Apply() const;

			template<typename TType = void>
			bool HasProperty(const std::string& name) const;

			template<typename TType>
			ShaderProperty<TType> GetProperty(const std::string& name) const;

			// Build-in properties setters/getters
			void SetBuildInProperty(int value);
			int GetBuildInProperty() const;
		};
	}
}

#include "ShaderProperties.inl"

#endif // !ENGINEQ_GRAPHICS_SHADER_PROPERTIES_HPP
