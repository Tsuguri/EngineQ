#ifndef ENGINEQ_GRAPHICS_SHADER_PROPERTIES_HPP
#define ENGINEQ_GRAPHICS_SHADER_PROPERTIES_HPP

#include <vector>
#include <map>

#include "Shader.hpp"
#include "ShaderUniformData.hpp"
#include "ShaderProperty.hpp"

#include "../Math/Matrix4.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		class ShaderProperties : private Utilities::Immovable
		{
		private:
			using UniformData = ShaderUniformData<
				Pair<GL_BOOL, GLboolean>,
				Pair<GL_INT, GLint>,
				Pair<GL_FLOAT, GLfloat>,
				Pair<GL_FLOAT_VEC2, Math::Vector2_t<GLfloat>>,
				Pair<GL_FLOAT_VEC3, Math::Vector3_t<GLfloat>>,
				Pair<GL_FLOAT_VEC4, Math::Vector4_t<GLfloat>>,
				Pair<GL_FLOAT_MAT4, Math::Matrix4>
			>;
			
			Shader& shader;
			
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
