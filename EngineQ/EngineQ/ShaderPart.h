#ifndef ENGINEQ_SHADER_PART_H
#define ENGINEQ_SHADER_PART_H

#include <memory>
#include <stdexcept>
#include <string>
#include <fstream>
#include <initializer_list>

#include "GL/glew.h"
#include "Immovable.hpp"

/*
// TMP
enum
{
	GL_VERTEX_SHADER,
	GL_FRAGMENT_SHADER,
	GL_GEOMETRY_SHADER,
	GL_COMPUTE_SHADER
};
enum
{
	GL_COMPILE_STATUS,
	GL_INFO_LOG_LENGTH
};
using GLenum = int;
using GLuint = unsigned int;
using GLint = int;
void glDeleteShader(GLuint) {};
void glShaderSource(GLuint, int, const char**, void*) {};
void glGetShaderInfoLog(GLuint, GLint, void*, char*) {};
void glCompileShader(GLuint) {};
void glGetShaderiv(GLuint, GLenum, GLint* status) { *status = 1; };
*/

namespace EngineQ
{
	enum class ShaderType : GLenum
	{
		VertexShader = GL_VERTEX_SHADER,
		FragmentShader = GL_FRAGMENT_SHADER,
		GeometryShader = GL_GEOMETRY_SHADER,
		ComputeShader = GL_COMPUTE_SHADER
	};

	class ShaderCompilationException : public std::runtime_error
	{
	public:
		ShaderCompilationException(const char* message) :
			std::runtime_error{ message }
		{
		}

		ShaderCompilationException(const std::string& message) :
			std::runtime_error{ message }
		{
		}
	};

	class ShaderLinkException : public std::runtime_error
	{
	public:
		ShaderLinkException(const char* message) :
			std::runtime_error{ message }
		{
		}

		ShaderLinkException(const std::string& message) :
			std::runtime_error{ message }
		{
		}
	};

	class ShaderArgumentException : public std::runtime_error
	{
	public:
		ShaderArgumentException(const char* message) :
			std::runtime_error{ message }
		{
		}

		ShaderArgumentException(const std::string& message) :
			std::runtime_error{ message }
		{
		}
	};

	class Uncopyable
	{
	public:
		Uncopyable() = default;

		Uncopyable(const Uncopyable&) = delete;
		Uncopyable& operator = (const Uncopyable&) = delete;
	};

	class Shader;

	class ShaderPart : public Uncopyable
	{
		friend class Shader;

	private:
		GLuint shaderId;
		ShaderType type;

	protected:
		ShaderPart()
		{
		}

		ShaderPart(const char* filePath, ShaderType shaderType)
		{
			CreateFromFile(filePath, shaderType);
		}

		void CreateFromFile(const char* filename, ShaderType shaderType)
		{
			std::ifstream stream{ filename };
			std::string shaderCode{ std::istreambuf_iterator<char>{ stream }, std::istreambuf_iterator<char>{} };

			CreateFromCode(shaderCode.c_str(), shaderType);
		}

		void CreateFromCode(const char* shaderCode, ShaderType shaderType)
		{
			this->type = shaderType;
			this->shaderId = glCreateShader(static_cast<GLenum>(shaderType));

			glShaderSource(this->shaderId, 1, &shaderCode, nullptr);
			glCompileShader(this->shaderId);

			GLint status;
			glGetShaderiv(this->shaderId, GL_COMPILE_STATUS, &status);
			if (status == 0)
			{
				GLint length;
				glGetShaderiv(this->shaderId, GL_INFO_LOG_LENGTH, &length);

				auto buffer = std::make_unique<char[]>(length);
				glGetShaderInfoLog(this->shaderId, length, nullptr, buffer.get());

				throw ShaderCompilationException{ buffer.get() };
			}
		}

	public:

		ShaderType GetType()
		{
			return type;
		}

		ShaderPart(ShaderPart&& other)
			: shaderId{ other.shaderId }
		{
			other.shaderId = 0;
		}

		~ShaderPart()
		{
			if (this->shaderId != 0)
			{
				glDeleteShader(this->shaderId);
				this->shaderId = 0;
			}
		}
	};

	class VertexShader : public ShaderPart
	{
	private:
		VertexShader()
		{
		}

	public:
		VertexShader(const char* shaderPath)
			: ShaderPart{ shaderPath, ShaderType::VertexShader }
		{
		}

		static VertexShader CreateFromFile(const char* filePath)
		{
			return VertexShader{ filePath };
		}

		static VertexShader CreateFromCode(const char* shaderCode)
		{
			VertexShader shader;
			shader.ShaderPart::CreateFromCode(shaderCode, ShaderType::VertexShader);
			return shader;
		}
	};

	class FragmentShader : public ShaderPart
	{
	private:
		FragmentShader()
		{
		}

	public:
		FragmentShader(const char* shaderPath)
			: ShaderPart{ shaderPath, ShaderType::FragmentShader }
		{
		}

		static FragmentShader CreateFromFile(const char* filePath)
		{
			return FragmentShader{ filePath };
		}

		static FragmentShader CreateFromCode(const char* shaderCode)
		{
			FragmentShader shader;
			shader.ShaderPart::CreateFromCode(shaderCode, ShaderType::FragmentShader);
			return shader;
		}
	};



	class UniformLocation
	{
		friend class Shader;

	private:
		GLint location;
	
		UniformLocation(GLint location) :
			location{ location }
		{
		}

	public:
		UniformLocation() :
			location{ -1 }
		{
		}

		operator bool()
		{
			return location >= 0;
		}
	};

	class Shader
	{
	private:
		GLuint programId;

	public:
		Shader(const std::initializer_list<ShaderPart>& shaders)
		{
			this->programId = glCreateProgram();
			for (const ShaderPart& shader : shaders)
				glAttachShader(this->programId, shader.shaderId);

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

		~Shader()
		{
			if (this->programId != 0)
			{
				glDeleteProgram(this->programId);
				this->programId = 0;
			}
		}

		void Activate()
		{
			glUseProgram(this->programId);
		}

		UniformLocation GetUniformLocation(std::string name)
		{
			GLint location = glGetUniformLocation(this->programId, name.c_str());
			if (location < 0)
				throw ShaderArgumentException{ "Uniform \"" + name + "\" location not found"  };
		
			return UniformLocation{ location };
		}

		bool TryGetUniformLocation(std::string name, UniformLocation& location)
		{
			GLint loc = glGetUniformLocation(this->programId, name.c_str());
			if (loc < 0)
				return false;

			location = UniformLocation{ loc };
			return true;
		}

		void Bind(UniformLocation location, int value)
		{
			glUniform1i(location.location, value);
		}

		void Bind(UniformLocation location, float value)
		{
			glUniform1f(location.location, value);
		}

		void Bind(UniformLocation location, double value)
		{
			glUniform1d(location.location, value);
		}

		void Bind(UniformLocation location, Vector2 value)
		{
			glUniform2f(location.location, value.X, value.Y);
		}

		void Bind(UniformLocation location, Vector3 value)
		{
			glUniform3f(location.location, value.X, value.Y, value.Z);
		}

		void Bind(UniformLocation location, Vector4 value)
		{
			glUniform4f(location.location, value.X, value.Y, value.Z, value.W);
		}

		void Bind(UniformLocation location, Matrix3 value)
		{
			glUniformMatrix3fv(location.location, 1, GL_FALSE, &value.Values[0]);
		}

		void Bind(UniformLocation location, Matrix4 value)
		{
			glUniformMatrix4fv(location.location, 1, GL_FALSE, &value.Values[0]);
		}
	};
}

#endif // !ENGINEQ_SHADER_PART_H
