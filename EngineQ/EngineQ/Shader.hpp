#ifndef SHADERHPP
#define SHADERHPP
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
		~Shader();
		void SetAsActive() const;


	};
}

#endif
