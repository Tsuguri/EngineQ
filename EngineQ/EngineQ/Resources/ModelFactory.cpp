#include "ModelFactory.hpp"

#include <unordered_map>
#include <sstream>

#include "../Libraries/TinyXML/tinyxml2.h"

#include "ResourceFactory.hpp"
#include "ModelLoader.hpp"


namespace EngineQ
{
	namespace Resources
	{
		template<typename TType>
		TType VectorFromString(std::string string)
		{
			std::stringstream stream;
			stream << "[" << string << "]";

			TType value;
			stream >> value;

			return value;
		}

		std::unique_ptr<Model>  ResourceFactory<Model>::CreateResource(ResourceManager& resourceManager, const char* filename)
		{
			static const std::unordered_map<std::string, VertexComponent> VertexComponentMap = {
				{ "Position", VertexComponent::Position },
				{ "Normal", VertexComponent::Normal },
				{ "Color", VertexComponent::Color },
				{ "TextureCoordinates", VertexComponent::TextureCoordinates },
			};

			tinyxml2::XMLDocument doc{};
			doc.LoadFile(filename);

			if (doc.Error())
				throw ResourceLoadingException{ doc.GetErrorStr1() };

			ModelLoader loader;

			VertexComponent components;
			ModelLoader::Config config;

			auto rootElement = doc.RootElement();

			auto componentsElement = rootElement->FirstChildElement("Components");
			for (auto child = componentsElement->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
			{
				VertexComponent component = VertexComponentMap.at(child->Name());
				components = components | component;

				switch (component)
				{
					case VertexComponent::Position:
					{
						auto defaultValue = child->Attribute("DefaultValue");
						if (defaultValue != nullptr)
							config.positionDefault = VectorFromString<Math::Vector3f>(defaultValue);
					}
					break;

					case VertexComponent::Normal:
					{
						auto defaultValue = child->Attribute("DefaultValue");
						if (defaultValue != nullptr)
							config.normalDefault = VectorFromString<Math::Vector3f>(defaultValue);
					}
					break;

					case VertexComponent::Color:
					{
						auto defaultValue = child->Attribute("DefaultValue");
						if (defaultValue != nullptr)
							config.colorDefault = VectorFromString<Math::Vector3f>(defaultValue);
					}
					break;

					case VertexComponent::TextureCoordinates:
					{
						auto defaultValue = child->Attribute("DefaultValue");
						if (defaultValue != nullptr)
							config.textureCoordinatesDefault = VectorFromString<Math::Vector2f>(defaultValue);
					}
					break;
				}
			}

			auto pathElement = rootElement->FirstChildElement("File");
			auto path = pathElement->Attribute("Path");

			return loader.LoadModel(path, components, config);
		}
	}
}