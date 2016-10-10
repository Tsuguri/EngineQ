#ifndef ENGINEQ_GRAPHICS_SHADER_PART_HPP
#define ENGINEQ_GRAPHICS_SHADER_PART_HPP

#include <memory>
#include <string>
#include <fstream>

#include "../Libraries/GL/glew.h"

#include "../Utilities/Immovable.hpp"
#include "ShaderExceptions.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		enum class ShaderType : GLenum
		{
			VertexShader = GL_VERTEX_SHADER,
			FragmentShader = GL_FRAGMENT_SHADER,
			GeometryShader = GL_GEOMETRY_SHADER,
			ComputeShader = GL_COMPUTE_SHADER,
		};

		struct ShaderFromFile 
		{
			const char* shaderFile;
		
			ShaderFromFile(const char* shaderFile) :
				shaderFile{ shaderFile }
			{
			}

			operator const char* ()
			{
				return this->shaderFile;
			}
		};

		struct ShaderFromCode 
		{
			const char* shaderCode;

			explicit ShaderFromCode(const char* shaderCode) :
				shaderCode{ shaderCode }
			{
			}

			operator const char* ()
			{
				return this->shaderCode;
			}
		};

		class Shader;

		class ShaderPart : private Utilities::Immovable
		{
			friend class Shader;

		private:
			GLuint shaderId;
			ShaderType type;

			void CreateFromFile(const char* filename, ShaderType shaderType);
			void CreateFromCode(const char* shaderCode, ShaderType shaderType);

		public:
			ShaderPart(ShaderFromFile shaderFile, ShaderType shaderType);
			ShaderPart(ShaderFromCode shaderCode, ShaderType shaderType);
			
			ShaderPart(ShaderPart&& other);
			~ShaderPart();

			ShaderType GetType() const;
		};


		class VertexShader : public ShaderPart
		{
		public:
			VertexShader(ShaderFromFile shaderFile);
			VertexShader(ShaderFromCode shaderCode);
		};


		class FragmentShader : public ShaderPart
		{
		public:
			FragmentShader(ShaderFromFile shaderFile);
			FragmentShader(ShaderFromCode shaderCode);
		};


		class GeometryShader : public ShaderPart
		{
		public:
			GeometryShader(ShaderFromFile shaderFile);
			GeometryShader(ShaderFromCode shaderCode);
		};


		class ComputeShader : public ShaderPart
		{
		public:
			ComputeShader(ShaderFromFile shaderFile);
			ComputeShader(ShaderFromCode shaderCode);
		};
	}
}

#endif // !ENGINEQ_GRAPHICS_SHADER_PART_HPP
