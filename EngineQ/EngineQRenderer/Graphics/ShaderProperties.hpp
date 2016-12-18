#ifndef ENGINEQ_GRAPHICS_SHADER_PROPERTIES_HPP
#define ENGINEQ_GRAPHICS_SHADER_PROPERTIES_HPP

#include <vector>
#include <map>

#include "Shader.hpp"
#include "ShaderUniformData.hpp"
#include "ShaderProperty.hpp"
#include "Texture.hpp"

#include <Math/Matrix4.hpp>
#include <Resources/Resource.hpp>

namespace EngineQ
{
	namespace Graphics
	{
		class ShaderProperties
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
				Pair<GL_SAMPLER_2D, Resources::Resource<Texture>>,
				Pair<GL_SAMPLER_CUBE,Resources::Resource<CubeTexture>>
			>;
			
		public:
			struct Light
			{
				ShaderProperty<Math::Vector3f> Position;
				ShaderProperty<Math::Vector3f> Ambient;
				ShaderProperty<Math::Vector3f> Diffuse;
				ShaderProperty<Math::Vector3f> Specular;
				ShaderProperty<Math::Matrix4> LightMatrix;
				ShaderProperty<Resources::Resource<Texture>> DirectionalShadowMap;
				ShaderProperty<Resources::Resource<CubeTexture>> PointShadowMap;

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

				ShaderProperty<Resources::Resource<Texture>> DiffuseTexture;
				ShaderProperty<Resources::Resource<Texture>> SpecularTexture;
				ShaderProperty<Resources::Resource<Texture>> NormalTexture;
			};

			struct Matrices
			{
				ShaderProperty<Math::Matrix4> Model;
				ShaderProperty<Math::Matrix4> View;
				ShaderProperty<Math::Matrix4> Projection;
			};

		private:
			Resources::Resource<Shader> shader;
			
			std::vector<std::pair<UniformLocation, UniformData>> shaderUniforms;
			std::map<std::string, std::size_t> shaderUniformsMap;
			
			std::vector<UniformData> mockUniforms;

			// Build-in properties
			std::vector<Light> lights;
			Material material;
			Matrices matrices;
			ShaderProperty<GLint> LightCount;

			void FinalizeBuiltIn();

			template<typename TType>
			ShaderProperty<TType> CreateMockUniform();

			template< typename TPropertyType>
			void CheckBuiltIn(ShaderProperty<TPropertyType>& property, const TPropertyType& defaultValue = TPropertyType());

			void OnUniformAdded(UniformData& data, UniformType type, const std::string& name, const std::string& translatedName);

			std::string TranslateName(std::string originalName) const;

		public:
			ShaderProperties(Resources::Resource<Shader> shader);

			Resources::Resource<Shader> GetShader() const;

			void Apply() const;

			template<typename TType>
			int GetPropertyIndex(const std::string& name) const;

			template<typename TType>
			void Set(int index, const TType& value);

			template<typename TType>
			TType Get(int index) const;

			template<typename TType = void>
			bool HasProperty(const std::string& name) const;

			template<typename TType>
			ShaderProperty<TType> GetProperty(const std::string& name);

			template<typename TType>
			Utilities::Nullable<ShaderProperty<TType>> TryGetProperty(const std::string& name);

			// Built-in properties getters
			const Matrices& GetMatrices();
			const Material& GetMaterial();
			const std::vector<Light>& GetLights();
			const ShaderProperty<GLint>& GetLightCount();
		};
	}
}

#include "ShaderProperties.inl"

#endif // !ENGINEQ_GRAPHICS_SHADER_PROPERTIES_HPP
