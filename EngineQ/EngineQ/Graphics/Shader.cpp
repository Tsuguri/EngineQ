#include "Shader.hpp"

namespace EngineQ
{
	using namespace Math;
	using namespace Utilities;

	namespace Graphics
	{
		void Shader::Create()
		{
			this->programId = glCreateProgram();
		}

		void Shader::AttachShader(const ShaderPart& shader)
		{
			glAttachShader(this->programId, shader.shaderId);
		}

		void Shader::Link()
		{
			glLinkProgram(this->programId);

			GLint status;
			glGetProgramiv(this->programId, GL_LINK_STATUS, &status);
			if (status == 0)
			{
				GLint length;
				glGetProgramiv(this->programId, GL_INFO_LOG_LENGTH, &length);

				auto buffer = std::make_unique<char[]>(length);
				glGetProgramInfoLog(this->programId, length, nullptr, buffer.get());

				throw ShaderLinkException{ buffer.get() };
			}
		}

		Shader::Shader(const std::vector<ShaderPart>& shaders)
		{
			Create();
			for (const auto& shader : shaders)
				AttachShader(shader);
			Link();
		}

		Shader::Shader(const VertexShader& vertexShader, const FragmentShader& fragmentShader)
		{
			Create();
			AttachShader(vertexShader);
			AttachShader(fragmentShader);
			Link();
		}

		Shader::Shader(const VertexShader& vertexShader, const GeometryShader& geometryShader, const FragmentShader& fragmentShader)
		{
			Create();
			AttachShader(vertexShader);
			AttachShader(geometryShader);
			AttachShader(fragmentShader);
			Link();
		}

		Shader::Shader(const ComputeShader& computeShader)
		{
			Create();
			AttachShader(computeShader);
			Link();
		}

		Shader::~Shader()
		{
			if (this->programId != 0)
			{
				glDeleteProgram(this->programId);
				this->programId = 0;
			}
		}

		void Shader::Activate()
		{
			glUseProgram(this->programId);
		}

		UniformLocation Shader::GetUniformLocation(const char* name)
		{
			GLint location = glGetUniformLocation(this->programId, name);
			if (location < 0)
				throw ShaderArgumentException{ std::string{"Uniform \""} +name + "\" location not found" };

			return UniformLocation(location);
		}

		Nullable<UniformLocation> Shader::TryGetUniformLocation(const char* name)
		{
			GLint location = glGetUniformLocation(this->programId, name);
			if (location < 0)
				return Nullable<UniformLocation>();

			return Nullable<UniformLocation>{ UniformLocation{ location } };
		}

		void Shader::Bind(UniformLocation location, int value)
		{
			glUniform1i(location.location, value);
		}

		void Shader::Bind(UniformLocation location, float value)
		{
			glUniform1f(location.location, value);
		}

		void Shader::Bind(UniformLocation location, double value)
		{
			glUniform1d(location.location, value);
		}

		void Shader::Bind(UniformLocation location, const Vector2i& value)
		{
			glUniform2iv(location.location, 1, value.Values);
		}

		void Shader::Bind(UniformLocation location, const Vector3i& value)
		{
			glUniform3iv(location.location, 1, value.Values);
		}

		void Shader::Bind(UniformLocation location, const Vector4i& value)
		{
			glUniform4iv(location.location, 1, value.Values);
		}

		void Shader::Bind(UniformLocation location, const Vector2f& value)
		{
			glUniform2fv(location.location, 1, value.Values);
		}

		void Shader::Bind(UniformLocation location, const Vector3f& value)
		{
			glUniform3fv(location.location, 1, value.Values);
		}

		void Shader::Bind(UniformLocation location, const Vector4f& value)
		{
			glUniform4fv(location.location, 1, value.Values);
		}

		void Shader::Bind(UniformLocation location, const Vector2d& value)
		{
			glUniform2dv(location.location, 1, value.Values);
		}

		void Shader::Bind(UniformLocation location, const Vector3d& value)
		{
			glUniform3dv(location.location, 1, value.Values);
		}

		void Shader::Bind(UniformLocation location, const Vector4d& value)
		{
			glUniform4dv(location.location, 1, value.Values);
		}

		void Shader::Bind(UniformLocation location, const Matrix3& value)
		{
			glUniformMatrix3fv(location.location, 1, GL_TRUE, value.Values);
		}

		void Shader::Bind(UniformLocation location, const Matrix4& value)
		{
			glUniformMatrix4fv(location.location, 1, GL_TRUE, value.Values);
		}

		void Shader::Bind(UniformLocation location, const Texture& texture)
		{
			// TMP
			int textureSlot = 3;

			glActiveTexture(GL_TEXTURE0 + textureSlot);
			glBindTexture(GL_TEXTURE_2D, texture.textureId);

			glUniform1i(location.location, textureSlot);
		}
	}
}