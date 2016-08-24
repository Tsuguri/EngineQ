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
			GLuint format = GL_RGB;
			GLuint dataType = GL_FLOAT;
		};
		class FramebufferConfiguration
		{
			std::string Name;
			bool DepthTesting;
			std::vector<TextureConfiguration> Textures;
		};

		class InputPair
		{
			GLuint Location;
			std::string Framebuffer;
			GLuint TextureNumber;
		};

		class OutputPair
		{
			std::string UniformName;
			std::string Framebuffer;
			GLuint TextureNumber;
		};

		class EffectsConfiguration
		{
			std::string ShaderName;//for resource manager
			std::vector<InputPair> Input;
		};

		class RendererConfiguration
		{
		public:
			bool DeferredEnabled;
			std::string DeferredShaderName;
			std::vector<FramebufferConfiguration> Framebuffers;
			std::vector<EffectsConfiguration> Effects;
		};


	}
}

#endif