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
			TextureConfiguration(std::string name="",GLuint format = GL_RGB, GLuint dataType = GL_UNSIGNED_BYTE);
			GLuint Format = GL_RGB;
			GLuint DataType = GL_UNSIGNED_BYTE;
			std::string Name;
		};

		class InputPair
		{
		public:
			InputPair(GLuint location, std::string texture, std::string locationName="");
			unsigned int Location = 0;
			std::string LocationName;
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
			bool Deffered = false;
			std::vector<Output> Output;
		};

		class RenderingUnitConfiguration
		{
		public:
			RendererConfiguration Renderer;
			std::vector<TextureConfiguration> Textures;
			std::vector<EffectConfiguration> Effects;
		};


	}
}

#endif