#ifndef ENGINEQ_GRAPHICS_RENDERER_CONFIGURATION_HPP
#define ENGINEQ_GRAPHICS_RENDERER_CONFIGURATION_HPP
#include "../Libraries/GL/glew.h"
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
			std::string name;
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
			int Location=0;
			std::string Texture;
		};

		class Output
		{
		public:
			Output(std::string texture);
			std::string Texture;
		};

		class EffectConfiguration
		{
		public:
			int  Shader;//for resource manager
			std::string ClassName;//C# class name
			bool DepthTesting;
			std::vector<InputPair> Input;
			std::vector<Output> Output;
		};

		class RendererConfiguration
		{
		public:
			bool DeferredEnabled=false;
			int DeferredShaderID;
			std::vector<TextureConfiguration> Textures;
			std::vector<EffectConfiguration> Effects;

			std::vector<FramebufferConfiguration> Framebuffers;
		};


	}
}

#endif