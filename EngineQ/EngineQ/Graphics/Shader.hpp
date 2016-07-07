#ifndef ENGINEQ_GRAPHICS_SHADER_HPP
#define ENGINEQ_GRAPHICS_SHADER_HPP

#include <memory>
#include <initializer_list>

#include "GL/glew.h"

#include "../Utilities/Uncopyable.hpp"
#include "../Utilities/Nullable.hpp"
#include "ShaderPart.hpp"
#include "UniformLocation.hpp"

#include "../Math/Vector2.hpp"
#include "../Math/Vector3.hpp"
#include "../Math/Vector4.hpp"
#include "../Math/Matrix3.hpp"
#include "../Math/Matrix4.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		using namespace ::EngineQ::Math;
		using namespace ::EngineQ::Utilities;

		class Shader : public Uncopyable
		{
		private:
			GLuint programId;

			void Create();
			void AttachShader(const ShaderPart& shader);
			void Link();

		public:
			Shader::Shader(const VertexShader& vertexShader, const FragmentShader& fragmentShader);
			Shader::Shader(const VertexShader& vertexShader, const GeometryShader& geometryShader, const FragmentShader& fragmentShader);
			Shader::Shader(const ComputeShader& computeShader);

			~Shader();

			void Activate();

			UniformLocation GetUniformLocation(std::string name);
			Nullable<UniformLocation> TryGetUniformLocation(std::string name);

			void Bind(UniformLocation location, int value);
			void Bind(UniformLocation location, float value);
			void Bind(UniformLocation location, double value);
			void Bind(UniformLocation location, Vector2 value);
			void Bind(UniformLocation location, Vector3 value);
			void Bind(UniformLocation location, Vector4 value);
			void Bind(UniformLocation location, Matrix3 value);
			void Bind(UniformLocation location, Matrix4 value);
		};
	}
}

#endif // !ENGINEQ_GRAPHICS_SHADER_HPP
