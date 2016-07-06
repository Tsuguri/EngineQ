#include "Shader.hpp"
#include <iostream>
#include <fstream>

namespace EngineQ
{
	void Shader::PrepareShader()
	{
		programId = glCreateProgram();
	}

	void Shader::FinalizeShader() const
	{
		glLinkProgram(programId);
		GLint success;
		glGetProgramiv(programId, GL_LINK_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetProgramInfoLog(programId, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
			std::cout << "Shader linking failure" << std::endl;
			throw 1;
		}
	}

	Shader::~Shader()
	{
		glDeleteProgram(programId);
	}

	Shader::Shader(const char* vertexFile, const char* fragmentFile)
	{
		PrepareShader();

		GLuint vertex = AddShader(vertexFile, GL_VERTEX_SHADER);
		if (vertex == 0)
		{
			std::cout << "Problem with adding vertex shader" << std::endl;
			throw 1;
		}

		GLuint fragment = AddShader(fragmentFile, GL_FRAGMENT_SHADER);
		if (fragment == 0)
		{
			std::cout << "Problem with adding fragment shader" << std::endl;
			throw 1;
		}

		glAttachShader(programId, vertex);
		glAttachShader(programId, fragment);

		FinalizeShader();
	}

	void Shader::SetAsActive() const
	{
		glUseProgram(programId);
	}



	GLuint Shader::AddShader(const char* filePath, GLenum type) const
	{
		const int maxCodeLength = 65535;

		char shaderCode[maxCodeLength] = "";
		if (LoadFile(filePath, &shaderCode[0], maxCodeLength) == nullptr)
		{
			std::cout << "Unable to read and parse shader" << std::endl;
			return 0;
		}
		GLuint shaderId = glCreateShader(type);
		if (shaderId == 0)
		{
			std::cout << "subshader creation failure" << std::endl;
			return 0;
		}
		const GLchar* source[1];
		source[0] = shaderCode;
		glShaderSource(shaderId, 1, source, nullptr);

		glCompileShader(shaderId);

		int success;
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			const int maxInfoLogSize = 2048;
			GLchar infoLog[maxInfoLogSize];
			glGetShaderInfoLog(shaderId, maxInfoLogSize, nullptr, infoLog);
			char error[maxInfoLogSize + 64] = "Warning. Shader Compilation Failed";
			strcat_s(error, static_cast<char*>(infoLog));
			std::cout << error << std::endl;
		}
		return shaderId;
	}

	char* Shader::LoadFile(const char* filePath, char* buffer, int bufferSize)
	{
		std::ifstream input{ filePath };
		if (input.fail())
			return nullptr;
		input.read(buffer, bufferSize);
		if (input.eof())
		{
			std::streamsize loaded = input.gcount();
			input.close();
			buffer[loaded] = '\0';
			return buffer;
		}
		else
		{
			input.close();
			return nullptr;
		}
	}
}
