#include "ShaderPart.hpp"
#include <iostream>

namespace EngineQ
{
	namespace Graphics
	{
	#pragma region ShaderPart

		ShaderPart::ShaderPart()
		{
		}

		ShaderPart::ShaderPart(const char* filePath, ShaderType shaderType)
		{
			CreateFromFile(filePath, shaderType);
		}

		void ShaderPart::CreateFromFile(const char* filename, ShaderType shaderType)
		{
			std::ifstream stream{};
			stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
			stream.open(filename);
			std::string shaderCode{ std::istreambuf_iterator<char>{ stream }, std::istreambuf_iterator<char>{} };
			CreateFromCode(shaderCode.c_str(), shaderType);
		}

		void ShaderPart::CreateFromCode(const char* shaderCode, ShaderType shaderType)
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

		ShaderType ShaderPart::GetType()
		{
			return this->type;
		}

		ShaderPart::ShaderPart(ShaderPart&& other)
			: shaderId{ other.shaderId }
		{
			other.shaderId = 0;
		}

		ShaderPart::~ShaderPart()
		{
			if (this->shaderId != 0)
			{
				glDeleteShader(this->shaderId);
				this->shaderId = 0;
			}
		}

	#pragma endregion

	#pragma region VertexShader

		VertexShader::VertexShader(const char* shaderPath)
			: ShaderPart{ shaderPath, ShaderType::VertexShader }
		{
		}

		VertexShader VertexShader::CreateFromFile(const char* filePath)
		{
			return VertexShader{ filePath };
		}

		VertexShader VertexShader::CreateFromCode(const char* shaderCode)
		{
			VertexShader shader;
			shader.ShaderPart::CreateFromCode(shaderCode, ShaderType::VertexShader);
			return shader;
		}

	#pragma endregion

	#pragma region FragmentShader

		FragmentShader::FragmentShader(const char* shaderPath)
			: ShaderPart{ shaderPath, ShaderType::FragmentShader }
		{
		}

		FragmentShader FragmentShader::CreateFromFile(const char* filePath)
		{
			return FragmentShader{ filePath };
		}

		FragmentShader FragmentShader::CreateFromCode(const char* shaderCode)
		{
			FragmentShader shader;
			shader.ShaderPart::CreateFromCode(shaderCode, ShaderType::FragmentShader);
			return shader;
		}

	#pragma endregion

	#pragma region GeometryShader

		GeometryShader::GeometryShader(const char* shaderPath)
			: ShaderPart{ shaderPath, ShaderType::GeometryShader }
		{
		}

		GeometryShader GeometryShader::CreateFromFile(const char* filePath)
		{
			return GeometryShader{ filePath };
		}

		GeometryShader GeometryShader::CreateFromCode(const char* shaderCode)
		{
			GeometryShader shader;
			shader.ShaderPart::CreateFromCode(shaderCode, ShaderType::GeometryShader);
			return shader;
		}

	#pragma endregion

	#pragma region ComputeShader
	
		ComputeShader::ComputeShader(const char* shaderPath)
			: ShaderPart{ shaderPath, ShaderType::ComputeShader }
		{
		}

		ComputeShader ComputeShader::CreateFromFile(const char* filePath)
		{
			return ComputeShader{ filePath };
		}

		ComputeShader ComputeShader::CreateFromCode(const char* shaderCode)
		{
			ComputeShader shader;
			shader.ShaderPart::CreateFromCode(shaderCode, ShaderType::ComputeShader);
			return shader;
		}

	#pragma endregion
	}
}
