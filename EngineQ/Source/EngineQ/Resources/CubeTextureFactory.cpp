#include "CubeTextureFactory.hpp"

// Standard includes
#include <array>

// Other projects
#include "EngineQCommon/Libraries/TinyXML/tinyxml2.h"
#include "EngineQRenderer/Graphics/CubeTexture.hpp"


namespace EngineQ
{
	namespace Resources
	{
		void FillName(std::array<const char*, 6>& array, const char* path, int index)
		{
			if (index > 5 || index < 0)
				return;
			if (array[index] != nullptr)
				throw "Multiple images for single direction!";
			array[index] = path;
		}

		std::unique_ptr<Graphics::CubeTexture> ResourceFactory<Graphics::CubeTexture>::CreateResource(ResourceManager& resourceManager, const char* filename)
		{
			tinyxml2::XMLDocument doc{};
			doc.LoadFile(filename);

			if (doc.Error())
				throw ResourceLoadingException{ doc.GetErrorStr1() };

			auto rootElement = doc.RootElement();

			auto image = rootElement->FirstChildElement("Image");

			// top,bottom,north,south,west,east
			std::array<const char*, 6> names;
			for (int i = 0; i < names.size(); i++)
				names[i] = nullptr;

			do {
				const char* path = image->Attribute("Path");
				std::string direction = std::string(image->Attribute("Direction"));
				if (direction == "Top")
					names[0] = path;
				else if (direction == "Bottom")
					names[1] = path;
				else if (direction == "North")
					names[2] = path;
				else if (direction == "South")
					names[3] = path;
				else if (direction == "West")
					names[4] = path;
				else if (direction == "East")
					names[5] = path;
				else
					throw "Bad direction name";

			} while ((image = image->NextSiblingElement("Image")) != nullptr);


			return std::make_unique<Graphics::CubeTexture>(names);
		}
	}
}