#ifndef ENGINEQ_GRAPHICS_SHADER_PROPERTIES_HPP
#define ENGINEQ_GRAPHICS_SHADER_PROPERTIES_HPP

#include <vector>
#include <map>

#include "Shader.hpp"
#include "ShaderUniformData.hpp"
#include "ShaderProperty.hpp"
#include "Texture.hpp"

#include "../Math/Matrix4.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		class ShaderProperties : private Utilities::Immovable
		{
		private:
			using UniformData = ShaderUniformData<
				Pair<GL_BOOL, bool>,
				Pair<GL_INT, GLint>,
				Pair<GL_FLOAT, GLfloat>,
				Pair<GL_FLOAT_VEC2, Math::Vector2_t<GLfloat>>,
				Pair<GL_FLOAT_VEC3, Math::Vector3_t<GLfloat>>,
				Pair<GL_FLOAT_VEC4, Math::Vector4_t<GLfloat>>,
				Pair<GL_FLOAT_MAT4, Math::Matrix4>,
				Pair<GL_SAMPLER_2D, std::shared_ptr<Texture>>
			>;
			
		public:
			struct Light
			{
				ShaderProperty<Math::Vector3f> Position;
				ShaderProperty<Math::Vector3f> Ambient;
				ShaderProperty<Math::Vector3f> Diffuse;
				ShaderProperty<Math::Vector3f> Specular;

				ShaderProperty<float> Distance;

				ShaderProperty<bool> CastsShadows;
				ShaderProperty<float> FarPlane;
			};

			struct Material
			{
				ShaderProperty<Math::Vector3f> Ambient;
				ShaderProperty<Math::Vector3f> Diffuse;
				ShaderProperty<Math::Vector3f> Specular;
				ShaderProperty<float> Shininess;
			};

			struct Matrices
			{
				ShaderProperty<Math::Matrix4> Model;
				ShaderProperty<Math::Matrix4> View;
				ShaderProperty<Math::Matrix4> Projection;
			};

		private:
			Shader& shader;
			
			std::vector<std::pair<UniformLocation, UniformData>> shaderUniforms;
			std::map<std::string, UniformData*> shaderUniformsMap;
			
			std::vector<UniformData> mockUniforms;

			// Build-in properties
			std::vector<Light> lights;
			Material material;
			Matrices matrices;

			void FinalizeBuiltIn();

			template<typename TType>
			ShaderProperty<TType> CreateMockUniform();

			template<typename TGroupType, typename TPropertyType>
			void CheckBuiltIn(TGroupType& group, ShaderProperty<TPropertyType>(TGroupType::* member));

			void OnUniformAdded(UniformData& data, UniformType type, const std::string& name);

		public:
			ShaderProperties(Shader& shader);

			void Apply() const;

			template<typename TType = void>
			bool HasProperty(const std::string& name) const;

			template<typename TType>
			ShaderProperty<TType> GetProperty(const std::string& name) const;

			template<typename TType>
			Utilities::Nullable<ShaderProperty<TType>> TryGetProperty(const std::string& name) const;

			// Built-in properties getters
			const Matrices& GetMatrices();
			const Material& GetMaterial();
			const std::vector<Light>& GetLights();
		};
	}
}

#include "ShaderProperties.inl"

#endif // !ENGINEQ_GRAPHICS_SHADER_PROPERTIES_HPP
