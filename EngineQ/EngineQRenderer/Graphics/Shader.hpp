#ifndef ENGINEQ_GRAPHICS_SHADER_HPP
#define ENGINEQ_GRAPHICS_SHADER_HPP

// Standard includes
#include <memory>
#include <vector>

// Libraries
#include <GL/glew.h>

// Other projects
#include "EngineQCommon/Utilities/Immovable.hpp"
#include "EngineQCommon/Utilities/Nullable.hpp"
#include "EngineQCommon/Math/Vector2.hpp"
#include "EngineQCommon/Math/Vector3.hpp"
#include "EngineQCommon/Math/Vector4.hpp"
#include "EngineQCommon/Math/Matrix3.hpp"
#include "EngineQCommon/Math/Matrix4.hpp"

// This project
#include "Types.hpp"
#include "ShaderPart.hpp"
#include "UniformLocation.hpp"


namespace EngineQ
{
	namespace Graphics
	{
		class Shader : private Utilities::Immovable
		{
			friend class ShaderProperties;

		private:
			GLuint programId;
			int currentTextureSlot = 0;

			void Create();
			void AttachShader(const ShaderPart& shader);
			void Link();

		public:
			Shader(const std::vector<ShaderPart>& shaders);
			Shader(const VertexShader& vertexShader, const FragmentShader& fragmentShader);
			Shader(const VertexShader& vertexShader, const GeometryShader& geometryShader, const FragmentShader& fragmentShader);
			Shader(const ComputeShader& computeShader);

			~Shader();

			void Reset();
			void Activate();

			UniformLocation GetUniformLocation(const char* name);
			Utilities::Nullable<UniformLocation> TryGetUniformLocation(const char* name);

			void Bind(UniformLocation location, int value);
			void Bind(UniformLocation location, float value);
			void Bind(UniformLocation location, double value);
			void Bind(UniformLocation location, const Math::Vector2i& value);
			void Bind(UniformLocation location, const Math::Vector3i& value);
			void Bind(UniformLocation location, const Math::Vector4i& value);
			void Bind(UniformLocation location, const Math::Vector2f& value);
			void Bind(UniformLocation location, const Math::Vector3f& value);
			void Bind(UniformLocation location, const Math::Vector4f& value);
			void Bind(UniformLocation location, const Math::Vector2d& value);
			void Bind(UniformLocation location, const Math::Vector3d& value);
			void Bind(UniformLocation location, const Math::Vector4d& value);
			void Bind(UniformLocation location, const Math::Matrix3& value);
			void Bind(UniformLocation location, const Math::Matrix4& value);

			// TMP
			void Bind(UniformLocation location, const Texture* texture);
			void Bind(UniformLocation location, const CubeTexture* texture);
		};
	}
}

#endif // !ENGINEQ_GRAPHICS_SHADER_HPP
