#include "ShaderPart.hpp"
#include <iostream>

namespace EngineQ
{
	namespace Graphics
	{
	#pragma region ShaderPart

		ShaderPart::ShaderPart(ShaderFromFile shaderPath, ShaderType shaderType)
		{
			CreateFromFile(shaderPath, shaderType);
		}

		ShaderPart::ShaderPart(ShaderFromCode shaderCode, ShaderType shaderType)
		{
			CreateFromCode(shaderCode, shaderType);
		}

		void ShaderPart::CreateFromFile(const char* filename, ShaderType shaderType)
		{
			std::ifstream stream;;
			stream.exceptions(std::ifstream::badbit | std::ifstream::failbit);
			stream.open(filename);

			std::string shaderCode{ std::istreambuf_iterator<char>{ stream }, std::istreambuf_iterator<char>{} };

			stream.close();

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

		ShaderPart::ShaderPart(ShaderPart&& other) :
			type{ other.type }, shaderId{ other.shaderId }
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

		VertexShader::VertexShader(ShaderFromFile shaderPath) :
			ShaderPart{ shaderPath, ShaderType::VertexShader }
		{
		}

		VertexShader::VertexShader(ShaderFromCode shaderCode) :
			ShaderPart{ shaderCode, ShaderType::VertexShader }
		{
		}

	#pragma endregion

	#pragma region FragmentShader

		FragmentShader::FragmentShader(ShaderFromFile shaderPath) :
			ShaderPart{ shaderPath, ShaderType::FragmentShader }
		{
		}

		FragmentShader::FragmentShader(ShaderFromCode shaderCode) :
			ShaderPart{ shaderCode, ShaderType::FragmentShader }
		{
		}

	#pragma endregion

	#pragma region GeometryShader

		GeometryShader::GeometryShader(ShaderFromFile shaderPath) :
			ShaderPart{ shaderPath, ShaderType::GeometryShader }
		{
		}

		GeometryShader::GeometryShader(ShaderFromCode shaderCode) :
			ShaderPart{ shaderCode, ShaderType::GeometryShader }
		{
		}

	#pragma endregion

	#pragma region ComputeShader

		ComputeShader::ComputeShader(ShaderFromFile shaderPath) :
			ShaderPart{ shaderPath, ShaderType::ComputeShader }
		{
		}

		ComputeShader::ComputeShader(ShaderFromCode shaderCode) :
			ShaderPart{ shaderCode, ShaderType::ComputeShader }
		{
		}

	#pragma endregion
	}
}
