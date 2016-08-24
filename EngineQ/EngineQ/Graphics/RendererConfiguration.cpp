#include "RendererConfiguration.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		TextureConfiguration::TextureConfiguration(GLuint format, GLuint dataType) : Format(format), DataType(dataType)
		{
		}

		FramebufferConfiguration::FramebufferConfiguration(std::string name, bool depthTesting, std::vector<TextureConfiguration> textures) : Name(name), DepthTesting(depthTesting), Textures(textures)
		{
		}

		InputPair::InputPair(GLuint location, GLuint textureNumber, std::string framebuffer) : Location(location), TextureNumber(textureNumber), Framebuffer(framebuffer)
		{
		}

		OutputPair::OutputPair(std::string uniformName, std::string framebuffer, GLuint textureNumber) : UniformName(uniformName), Framebuffer(framebuffer), TextureNumber(textureNumber)
		{
		}
	}
}