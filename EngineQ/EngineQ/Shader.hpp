#ifndef ENGINEQ_SHADER_HPP
#define ENGINEQ_SHADER_HPP
#include <GL/glew.h>
#include <string>
#include <vector>

namespace EngineQ
{

	class Shader
	{
	private:
		GLuint programId;

		void PrepareShader();
		void FinalizeShader() const;
		GLuint AddShader(const char* filePath, GLenum type) const;
		static char* LoadFile(const char* filePath, char* buffer, int bufferSize);
		
	public:
		Shader(const char* vertexFile, const char* fragmentFile);
		GLuint GetProgramId();
		~Shader();
		void SetAsActive() const;


	};
}

#endif
