#include "RendererConfiguration.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		TextureConfiguration::TextureConfiguration(GLuint format, GLuint dataType) : Format(format), DataType(dataType)
		{
		}

		FramebufferConfiguration::FramebufferConfiguration() : Name(""), DepthTesting(false)
		{

		}

		FramebufferConfiguration::FramebufferConfiguration(std::string name, bool depthTesting, std::vector<TextureConfiguration> textures) : Name(name), DepthTesting(depthTesting), Textures(textures)
		{
		}



		OutputPair::OutputPair(std::string uniformName, std::string framebuffer, GLuint textureNumber) : UniformName(uniformName), Framebuffer(framebuffer), TextureNumber(textureNumber)
		{
		}
	}
}