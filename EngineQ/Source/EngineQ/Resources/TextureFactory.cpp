#include "TextureFactory.hpp"

// Standard includes
#include <array>

// Other projects
#include "EngineQCommon/Libraries/TinyXML/tinyxml2.h"
#include "EngineQRenderer/Graphics/Texture.hpp"


namespace EngineQ
{
	namespace Resources
	{
		std::unique_ptr<Graphics::Texture> ResourceFactory<Graphics::Texture>::CreateResource(ResourceManager& resourceManager, const char* filename)
		{
			tinyxml2::XMLDocument doc{};
			doc.LoadFile(filename);

			if (doc.Error())
				throw ResourceLoadingException{ doc.GetErrorStr1() };

			auto rootElement = doc.RootElement();

			auto image = rootElement->FirstChildElement("Image");
			const char* path = image->Attribute("Path");

			auto mipmaps = rootElement->FirstChildElement("Mipmaps");
			bool useMipmaps = mipmaps->BoolAttribute("Use");

			return std::make_unique<Graphics::Texture>(path, useMipmaps);
		}
	}
}