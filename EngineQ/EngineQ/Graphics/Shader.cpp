#include "Shader.hpp"

namespace EngineQ
{
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

		UniformLocation Shader::GetUniformLocation(std::string name)
		{
			GLint location = glGetUniformLocation(this->programId, name.c_str());
			if (location < 0)
				throw ShaderArgumentException{ "Uniform \"" + name + "\" location not found" };

			return UniformLocation(location);
		}

		Nullable<UniformLocation> Shader::TryGetUniformLocation(std::string name)
		{
			GLint location = glGetUniformLocation(this->programId, name.c_str());
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

		void Shader::Bind(UniformLocation location, Vector2 value)
		{
			glUniform2f(location.location, value.X, value.Y);
		}

		void Shader::Bind(UniformLocation location, Vector3 value)
		{
			glUniform3f(location.location, value.X, value.Y, value.Z);
		}

		void Shader::Bind(UniformLocation location, Vector4 value)
		{
			glUniform4f(location.location, value.X, value.Y, value.Z, value.W);
		}

		void Shader::Bind(UniformLocation location, Matrix3 value)
		{
			glUniformMatrix3fv(location.location, 1, GL_FALSE, &value.Values[0]);
		}

		void Shader::Bind(UniformLocation location, Matrix4 value)
		{
			glUniformMatrix4fv(location.location, 1, GL_TRUE, &value.Values[0]);
		}
	}
}