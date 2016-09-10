#include "RendererConfiguration.hpp"
#include <iostream>
#include <fstream>

namespace EngineQ
{
	namespace Graphics
	{
		const std::unordered_map<std::string, GLuint> TextureConfiguration::internalFormats = std::unordered_map<std::string, GLuint>{
			{"GL_ALPHA",GL_ALPHA},
			{"GL_ALPHA4",GL_ALPHA4 },
			{"GL_ALPHA8", GL_ALPHA8 },
			{"GL_ALPHA12", GL_ALPHA12 },
			{"GL_ALPHA16", GL_ALPHA16 },
			{"GL_COMPRESSED_ALPHA", GL_COMPRESSED_ALPHA },
			{"GL_COMPRESSED_LUMINANCE",GL_COMPRESSED_LUMINANCE },
			{"GL_COMPRESSED_LUMINANCE_ALPHA", GL_COMPRESSED_LUMINANCE_ALPHA },
			{"GL_COMPRESSED_INTENSITY", GL_COMPRESSED_INTENSITY },
			{"GL_COMPRESSED_RGB", GL_COMPRESSED_RGB },
			{"GL_COMPRESSED_RGBA", GL_COMPRESSED_RGBA },
			{"GL_DEPTH_COMPONENT", GL_DEPTH_COMPONENT },
			{"GL_DEPTH_COMPONENT16", GL_DEPTH_COMPONENT16 },
			{"GL_DEPTH_COMPONENT24", GL_DEPTH_COMPONENT24 },
			{"GL_DEPTH_COMPONENT32", GL_DEPTH_COMPONENT32 },
			{"GL_LUMINANCE", GL_LUMINANCE },
			{"GL_LUMINANCE4", GL_LUMINANCE4 },
			{"GL_LUMINANCE8", GL_LUMINANCE8 },
			{"GL_LUMINANCE12", GL_LUMINANCE12 },
			{"GL_LUMINANCE16", GL_LUMINANCE16 },
			{"GL_LUMINANCE_ALPHA", GL_LUMINANCE_ALPHA},
			{"GL_LUMINANCE4_ALPHA4", GL_LUMINANCE4_ALPHA4 },
			{"GL_LUMINANCE6_ALPHA2", GL_LUMINANCE6_ALPHA2 },
			{"GL_LUMINANCE8_ALPHA8", GL_LUMINANCE8_ALPHA8 },
			{"GL_LUMINANCE12_ALPHA4", GL_LUMINANCE12_ALPHA4 },
			{"GL_LUMINANCE12_ALPHA12", GL_LUMINANCE12_ALPHA12 },
			{"GL_LUMINANCE16_ALPHA16", GL_LUMINANCE16_ALPHA16 },
			{"GL_INTENSITY", GL_INTENSITY },
			{"GL_INTENSITY4", GL_INTENSITY4 },
			{"GL_INTENSITY8", GL_INTENSITY8 },
			{"GL_INTENSITY12", GL_INTENSITY12 },
			{"GL_INTENSITY16", GL_INTENSITY16 },
			{"GL_R3_G3_B2", GL_R3_G3_B2},
			{"GL_RGB", GL_RGB },
			{"GL_RGB4", GL_RGB4 },
			{"GL_RGB5", GL_RGB5 },
			{"GL_RGB8", GL_RGB8},
			{"GL_RGB10", GL_RGB10 },
			{"GL_RGB12", GL_RGB12 },
			{"GL_RGB16", GL_RGB16 },
			{"GL_RGBA", GL_RGBA },
			{"GL_RGBA2", GL_RGBA2 },
			{"GL_RGBA4", GL_RGBA4 },
			{"GL_RGB5_A1", GL_RGB5_A1 },
			{"GL_RGBA8", GL_RGBA8 },
			{"GL_RGB10_A2", GL_RGB10_A2 },
			{"GL_RGBA12", GL_RGBA12 },
			{"GL_RGBA16", GL_RGBA16 },
			{"GL_SLUMINANCE", GL_SLUMINANCE },
			{"GL_SLUMINANCE8", GL_SLUMINANCE8 },
			{"GL_SLUMINANCE_ALPHA", GL_SLUMINANCE_ALPHA },
			{"GL_SLUMINANCE8_ALPHA8", GL_SLUMINANCE8_ALPHA8 },
			{"GL_SRGB", GL_SRGB},
			{"GL_SRGB8", GL_SRGB8 },
			{"GL_SRGB_ALPHA", GL_SRGB_ALPHA },
			{"GL_SRGB8_ALPHA8",GL_SRGB8_ALPHA8 }
		};

		const std::unordered_map<std::string, GLuint> TextureConfiguration::formats = std::unordered_map<std::string, GLuint>{
			{ "GL_COLOR_INDEX", GL_COLOR_INDEX},
			{ "GL_RED",GL_RED},
			{ "GL_GREEN",GL_GREEN},
			{ "GL_BLUE",GL_BLUE},
			{ "GL_ALPHA",GL_ALPHA},
			{ "GL_RGB",GL_RGB},
			{ "GL_BGR",GL_BGR},
			{ "GL_RGBA",GL_RGBA},
			{ "GL_BGRA",GL_BGRA},
			{ "GL_LUMINANCE",GL_LUMINANCE},
			{ "GL_LUMINANCE_ALPHA",GL_LUMINANCE_ALPHA }
		};

		const std::unordered_map<std::string, GLuint> TextureConfiguration::dataTypes = std::unordered_map<std::string, GLuint>{
			{"GL_UNSIGNED_BYTE",GL_UNSIGNED_BYTE },
			{ "GL_BYTE", GL_BYTE },
			{ "GL_UNSIGNED_SHORT", GL_UNSIGNED_SHORT },
			{ "GL_SHORT", GL_SHORT },
			{ "GL_UNSIGNED_INT", GL_UNSIGNED_INT },
			{ "GL_INT", GL_INT },
			{ "GL_FLOAT", GL_FLOAT },
			{ "GL_UNSIGNED_BYTE_3_3_2", GL_UNSIGNED_BYTE_3_3_2 },
			{ "GL_UNSIGNED_BYTE_2_3_3_REV", GL_UNSIGNED_BYTE_2_3_3_REV },
			{ "GL_UNSIGNED_SHORT_5_6_5", GL_UNSIGNED_SHORT_5_6_5 },
			{ "GL_UNSIGNED_SHORT_5_6_5_REV", GL_UNSIGNED_SHORT_5_6_5_REV },
			{ "GL_UNSIGNED_SHORT_4_4_4_4", GL_UNSIGNED_SHORT_4_4_4_4 },
			{ "GL_UNSIGNED_SHORT_4_4_4_4_REV", GL_UNSIGNED_SHORT_4_4_4_4_REV },
			{ "GL_UNSIGNED_SHORT_5_5_5_1", GL_UNSIGNED_SHORT_5_5_5_1 },
			{ "GL_UNSIGNED_SHORT_1_5_5_5_REV", GL_UNSIGNED_SHORT_1_5_5_5_REV },
			{ "GL_UNSIGNED_INT_8_8_8_8", GL_UNSIGNED_INT_8_8_8_8 },
			{ "GL_UNSIGNED_INT_8_8_8_8_REV", GL_UNSIGNED_INT_8_8_8_8_REV },
			{ "GL_UNSIGNED_INT_10_10_10_2", GL_UNSIGNED_INT_10_10_10_2},
			{ "GL_UNSIGNED_INT_2_10_10_10_REV", GL_UNSIGNED_INT_2_10_10_10_REV}
		};


		TextureConfiguration TextureConfiguration::Load(tinyxml2::XMLElement * element)
		{
			TextureConfiguration tex;
			auto name = element->Attribute("Name");
			if (name != nullptr)
				tex.Name = name;
			else
				throw "Brak nazwy tekstury";


			auto internalFormat = element->Attribute("InternalFormat");
			if (internalFormat != nullptr)
			{
				auto tmp = internalFormats.find(internalFormat);
				if (tmp == internalFormats.end())
					throw "Brak takiego formatu!";
				tex.InternalFormat = tmp->second;
			}

			auto format = element->Attribute("Format");
			if (format != nullptr)
			{
				auto tmp = formats.find(format);
				if (tmp == formats.end())
					throw "Brak takiego formatu!";
				tex.Format = tmp->second;
			}

			auto dataType = element->Attribute("DataType");
			if (dataType != nullptr)
			{
				auto tmp = dataTypes.find(dataType);
				if (tmp == dataTypes.end())
					throw "Brak takiego typu danych!";
				tex.DataType = tmp->second;
			}

			return tex;
		}

		TextureConfiguration::TextureConfiguration(std::string name, GLuint format, GLuint dataType) : Format(format), DataType(dataType), Name(name)
		{
		}

		InputPair::InputPair(GLuint location, std::string texture, std::string locationName) : Location(location), LocationName(locationName), Texture(texture)
		{
		}

		OutputTexture::OutputTexture(std::string texture) : Texture(texture)
		{
		}

		EffectConfiguration EffectConfiguration::Load(tinyxml2::XMLElement* element)
		{
			auto configuration = EffectConfiguration{};

			auto shader = element->IntAttribute("Shader");
			if (shader == 0)//default value if not exist or set to 0 - both not wanted
				throw "Shader attribute not found or equal to 0";
			configuration.Shader = shader;

			auto depth = element->BoolAttribute("DeptTesting");//default false if not exist
			configuration.DepthTesting = depth;

			auto input = element->FirstChildElement("Input");
			if (input != nullptr)
			{
				for (auto inputInfo = input->FirstChildElement(); inputInfo != nullptr; inputInfo = inputInfo->NextSiblingElement())
				{
					auto texture = inputInfo->Attribute("Texture");
					auto location = inputInfo->Attribute("Location");
					auto locationName = inputInfo->Attribute("LocationName");
					if (texture == nullptr || location == nullptr)
						throw "Missing one or both of required input info!";
					int loc = std::stoi(location);
					if (locationName == nullptr)
						configuration.Input.push_back(InputPair{ static_cast<GLuint>(loc),texture });
					else
						configuration.Input.push_back(InputPair{ static_cast<GLuint>(loc),texture,locationName });
				}
			}

			auto output = element->FirstChildElement("Output");
			if (output == nullptr || output->FirstChildElement() == nullptr)
				throw "Shader without output found";
			for (auto outputInfo = output->FirstChildElement(); outputInfo != nullptr; outputInfo = outputInfo->NextSiblingElement())
			{
				auto texture = outputInfo->Attribute("Texture");
				if (texture == nullptr)
				{
					configuration.Output.push_back(OutputTexture{ std::string("Screen") });
				}
				else
					configuration.Output.push_back(OutputTexture{ std::string(texture) });
			}


			return configuration;
		}

		RendererConfiguration RendererConfiguration::Load(tinyxml2::XMLElement* element)
		{
			RendererConfiguration configuration;

			auto format = element->Attribute("Deffered");
			if (format != nullptr && std::string(format) == "true")
			{
				configuration.Deffered = true;
			}

			auto output = element->FirstChildElement();
			if (output != nullptr)
			{
				if (std::string(output->Name()) != "Output")
					throw "Wrong renderer configuration element!";
				for (auto outputInfo = output->FirstChildElement(); outputInfo != nullptr; outputInfo = outputInfo->NextSiblingElement())
				{
					auto texture = outputInfo->Attribute("Texture");
					if (texture == nullptr)
						throw "No texture info";
					configuration.Output.push_back(OutputTexture{ std::string(texture) });
				}
			}


			return configuration;
		}

		RenderingUnitConfiguration RenderingUnitConfiguration::Load(tinyxml2::XMLElement* element)
		{
			RenderingUnitConfiguration configuration{};


			if (std::string(element->Name()) != "RenderingUnitConfiguration")
				throw "Wrong element name";


			auto textures = element->FirstChildElement("Textures");
			if (textures != nullptr)
			{
				for (auto textureInfo = textures->FirstChildElement(); textureInfo != nullptr; textureInfo = textureInfo->NextSiblingElement())
				{
					std::cout << "	" << textureInfo->Name() << std::endl;
					configuration.Textures.push_back(TextureConfiguration::Load(textureInfo));
				}
			}
			auto renderer = element->FirstChildElement("Renderer");
			if (renderer != nullptr)
			{
				configuration.Renderer = RendererConfiguration::Load(renderer);
			}
			auto effects = element->FirstChildElement("Effects");
			if (effects != nullptr)
			{
				for (auto effectInfo = effects->FirstChildElement(); effectInfo != nullptr; effectInfo = effectInfo->NextSiblingElement())
				{
					std::cout << "	" << effectInfo->Name() << std::endl;
					configuration.Effects.push_back(EffectConfiguration::Load(effectInfo));
				}
			}

			return configuration;
		}

		RenderingUnitConfiguration RenderingUnitConfiguration::Load(std::string filePath)
		{// add error checking
			tinyxml2::XMLDocument xmlDoc;
			tinyxml2::XMLError eResult = xmlDoc.LoadFile(filePath.c_str());
			if (eResult != tinyxml2::XML_SUCCESS)
				throw "Error parsing XML file";
			return Load(xmlDoc.RootElement());
		}
	}
}
