#ifndef ENGINEQ_GRAPHICS_RENDERER_CONFIGURATION_HPP
#define ENGINEQ_GRAPHICS_RENDERER_CONFIGURATION_HPP
#include "GL/glew.h"
#include <string>
#include <vector>

namespace EngineQ
{
	namespace Graphics
	{
		class TextureConfiguration
		{
		public:
			TextureConfiguration(GLuint format = GL_RGB, GLuint dataType = GL_FLOAT);
			GLuint Format = GL_RGB;
			GLuint DataType = GL_FLOAT;
		};

		class FramebufferConfiguration
		{
		public:
			FramebufferConfiguration();
			FramebufferConfiguration(std::string name, bool depthTesting, std::vector<TextureConfiguration> textures);
			std::string Name;
			bool DepthTesting=false;
			std::vector<TextureConfiguration> Textures;
		};

		class InputPair
		{
		public:
			InputPair(GLuint location, GLuint textureNumber, std::string framebuffer);
			GLuint Location=0;
			std::string Framebuffer;
			GLuint TextureNumber=0;
		};

		class OutputPair
		{
			OutputPair(std::string uniformName, std::string framebuffer, GLuint textureNumber);
			std::string UniformName;
			std::string Framebuffer;
			GLuint TextureNumber=0;
		};

		class EffectConfiguration
		{
		public:
			std::string ShaderName;//for resource manager
			std::string ClassName;//C# class name
			std::vector<InputPair> Input;
			std::vector<OutputPair> Output;
		};

		class RendererConfiguration
		{
		public:
			bool DeferredEnabled=false;
			std::string DeferredShaderName;
			std::vector<FramebufferConfiguration> Framebuffers;
			std::vector<EffectConfiguration> Effects;
		};


	}
}

#endif