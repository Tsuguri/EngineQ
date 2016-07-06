#ifndef ENGINEQ_SHADER_PART_H
#define ENGINEQ_SHADER_PART_H

#include <memory>
#include <stdexcept>
#include <string>
#include <fstream>

//#include "GL\glew.h"
#include "Immovable.hpp"

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
	};

	class Uncopyable
	{
	public:
		Uncopyable() = default;

		Uncopyable(const Uncopyable&) = delete;
		Uncopyable& operator = (const Uncopyable&) = delete;
	};

	class ShaderPart : public Uncopyable
	{
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

				throw ShaderCompilationException(buffer.get());
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

	class Shader;

	class UniformLocation
	{
		friend class Shader;

	private:
		const GLuint location;
	};
}

#endif // !ENGINEQ_SHADER_PART_H
