#ifndef ENGINEQ_GRAPHICS_SHADER_PART_HPP
#define ENGINEQ_GRAPHICS_SHADER_PART_HPP

#include <memory>
#include <string>
#include <fstream>

#include "../Utilities/Uncopyable.hpp"
#include "ShaderExceptions.hpp"

#include "GL/glew.h"

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

		class Shader;

		class ShaderPart : public Utilities::Uncopyable
		{
			friend class Shader;

		private:
			GLuint shaderId;
			ShaderType type;

		protected:
			ShaderPart();
			ShaderPart(const char* filePath, ShaderType shaderType);

			void CreateFromFile(const char* filename, ShaderType shaderType);
			void CreateFromCode(const char* shaderCode, ShaderType shaderType);

		public:
			ShaderPart(ShaderPart&& other);
			~ShaderPart();

			ShaderType GetType();
		};


		class VertexShader : public ShaderPart
		{
		private:
			VertexShader() = default;

		public:
			VertexShader(const char* shaderPath);

			static VertexShader CreateFromFile(const char* filePath);
			static VertexShader CreateFromCode(const char* shaderCode);
		};


		class FragmentShader : public ShaderPart
		{
		private:
			FragmentShader() = default;

		public:
			FragmentShader(const char* shaderPath);

			static FragmentShader CreateFromFile(const char* filePath);
			static FragmentShader CreateFromCode(const char* shaderCode);
		};


		class GeometryShader : public ShaderPart
		{
		private:
			GeometryShader() = default;

		public:
			GeometryShader(const char* shaderPath);

			static GeometryShader CreateFromFile(const char* filePath);
			static GeometryShader CreateFromCode(const char* shaderCode);
		};


		class ComputeShader : public ShaderPart
		{
		private:
			ComputeShader() = default;

		public:
			ComputeShader(const char* shaderPath);

			static ComputeShader CreateFromFile(const char* filePath);
			static ComputeShader CreateFromCode(const char* shaderCode);
		};
	}
}

#endif // !ENGINEQ_GRAPHICS_SHADER_PART_HPP
