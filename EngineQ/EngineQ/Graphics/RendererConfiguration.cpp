#include "RendererConfiguration.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		TextureConfiguration::TextureConfiguration(std::string name,GLuint format, GLuint dataType) : Format(format), DataType(dataType), Name(name)
		{
		}

		InputPair::InputPair(GLuint location, std::string texture) : Location(location), Texture(texture)
		{
		}

		Output::Output(std::string texture) : Texture(texture)
		{
		}
	}
}