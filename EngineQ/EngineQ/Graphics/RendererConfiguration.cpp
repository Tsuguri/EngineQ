#include "RendererConfiguration.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		TextureConfiguration::TextureConfiguration(std::string name,GLuint format, GLuint dataType) : Format(format), DataType(dataType), Name(name)
		{
		}

		InputPair::InputPair(GLuint location, std::string texture, std::string locationName) : Location(location), LocationName(locationName), Texture(texture)
		{
		}

		Output::Output(std::string texture) : Texture(texture)
		{
		}
	}
}