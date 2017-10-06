#include "RendererConfiguration.hpp"

// Standard includes
#include <iostream>
#include <fstream>


namespace EngineQ
{
	namespace Graphics
	{
		namespace Configuration
		{
			const std::unordered_map<std::string, GLuint> TextureConfiguration::internalFormats = std::unordered_map<std::string, GLuint>{
				{ "GL_ALPHA", GL_ALPHA},
				{ "GL_ALPHA4", GL_ALPHA4 },
				{ "GL_ALPHA8", GL_ALPHA8 },
				{ "GL_ALPHA12", GL_ALPHA12 },
				{ "GL_ALPHA16", GL_ALPHA16 },
				{ "GL_COMPRESSED_ALPHA", GL_COMPRESSED_ALPHA },
				{ "GL_COMPRESSED_LUMINANCE", GL_COMPRESSED_LUMINANCE },
				{ "GL_COMPRESSED_LUMINANCE_ALPHA", GL_COMPRESSED_LUMINANCE_ALPHA },
				{ "GL_COMPRESSED_INTENSITY", GL_COMPRESSED_INTENSITY },
				{ "GL_COMPRESSED_RGB", GL_COMPRESSED_RGB },
				{ "GL_COMPRESSED_RGBA", GL_COMPRESSED_RGBA },
				{ "GL_DEPTH_COMPONENT", GL_DEPTH_COMPONENT },
				{ "GL_DEPTH_COMPONENT16", GL_DEPTH_COMPONENT16 },
				{ "GL_DEPTH_COMPONENT24", GL_DEPTH_COMPONENT24 },
				{ "GL_DEPTH_COMPONENT32", GL_DEPTH_COMPONENT32 },
				{ "GL_LUMINANCE", GL_LUMINANCE },
				{ "GL_LUMINANCE4", GL_LUMINANCE4 },
				{ "GL_LUMINANCE8", GL_LUMINANCE8 },
				{ "GL_LUMINANCE12", GL_LUMINANCE12 },
				{ "GL_LUMINANCE16", GL_LUMINANCE16 },
				{ "GL_LUMINANCE_ALPHA", GL_LUMINANCE_ALPHA},
				{ "GL_LUMINANCE4_ALPHA4", GL_LUMINANCE4_ALPHA4 },
				{ "GL_LUMINANCE6_ALPHA2", GL_LUMINANCE6_ALPHA2 },
				{ "GL_LUMINANCE8_ALPHA8", GL_LUMINANCE8_ALPHA8 },
				{ "GL_LUMINANCE12_ALPHA4", GL_LUMINANCE12_ALPHA4 },
				{ "GL_LUMINANCE12_ALPHA12", GL_LUMINANCE12_ALPHA12 },
				{ "GL_LUMINANCE16_ALPHA16", GL_LUMINANCE16_ALPHA16 },
				{ "GL_INTENSITY", GL_INTENSITY },
				{ "GL_INTENSITY4", GL_INTENSITY4 },
				{ "GL_INTENSITY8", GL_INTENSITY8 },
				{ "GL_INTENSITY12", GL_INTENSITY12 },
				{ "GL_INTENSITY16", GL_INTENSITY16 },
				{ "GL_R3_G3_B2", GL_R3_G3_B2},
				{ "GL_RGB", GL_RGB },
				{ "GL_RGB4", GL_RGB4 },
				{ "GL_RGB5", GL_RGB5 },
				{ "GL_RGB8", GL_RGB8},
				{ "GL_RGB10", GL_RGB10 },
				{ "GL_RGB12", GL_RGB12 },
				{ "GL_RGB16", GL_RGB16 },
				{ "GL_RGBA", GL_RGBA },
				{ "GL_RGBA2", GL_RGBA2 },
				{ "GL_RGBA4", GL_RGBA4 },
				{ "GL_RGB5_A1", GL_RGB5_A1 },
				{ "GL_RGBA8", GL_RGBA8 },
				{ "GL_RGB10_A2", GL_RGB10_A2 },
				{ "GL_RGBA12", GL_RGBA12 },
				{ "GL_RGBA16", GL_RGBA16 },
				{ "GL_SLUMINANCE", GL_SLUMINANCE },
				{ "GL_SLUMINANCE8", GL_SLUMINANCE8 },
				{ "GL_SLUMINANCE_ALPHA", GL_SLUMINANCE_ALPHA },
				{ "GL_SLUMINANCE8_ALPHA8", GL_SLUMINANCE8_ALPHA8 },
				{ "GL_SRGB", GL_SRGB},
				{ "GL_SRGB8", GL_SRGB8 },
				{ "GL_SRGB_ALPHA", GL_SRGB_ALPHA },
				{ "GL_SRGB8_ALPHA8", GL_SRGB8_ALPHA8 },
				{ "GL_RGB16F", GL_RGB16F },
				{ "GL_RGBA16F", GL_RGBA16F },
				{ "GL_R8", GL_R8 },
				{ "GL_R16F", GL_R16F },
			};

			const std::unordered_map<std::string, GLuint> TextureConfiguration::formats = std::unordered_map<std::string, GLuint>{
				{ "GL_COLOR_INDEX", GL_COLOR_INDEX },
				{ "GL_RED", GL_RED },
				{ "GL_GREEN", GL_GREEN },
				{ "GL_BLUE", GL_BLUE },
				{ "GL_ALPHA", GL_ALPHA },
				{ "GL_RGB", GL_RGB },
				{ "GL_BGR", GL_BGR },
				{ "GL_RGBA", GL_RGBA },
				{ "GL_BGRA", GL_BGRA },
				{ "GL_LUMINANCE", GL_LUMINANCE },
				{ "GL_LUMINANCE_ALPHA", GL_LUMINANCE_ALPHA },
			};

			const std::unordered_map<std::string, GLuint> TextureConfiguration::dataTypes = std::unordered_map<std::string, GLuint>{
				{ "GL_UNSIGNED_BYTE", GL_UNSIGNED_BYTE },
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
				{ "GL_UNSIGNED_INT_10_10_10_2", GL_UNSIGNED_INT_10_10_10_2 },
				{ "GL_UNSIGNED_INT_2_10_10_10_REV", GL_UNSIGNED_INT_2_10_10_10_REV },
			};

			const std::unordered_map<std::string, GLint> TextureConfiguration::filters = std::unordered_map<std::string, GLint>{
				{ "GL_LINEAR", GL_LINEAR },
				{ "GL_NEAREST", GL_NEAREST },
				{ "GL_NEAREST_MIPMAP_NEAREST", GL_NEAREST_MIPMAP_NEAREST },
				{ "GL_LINEAR_MIPMAP_NEAREST", GL_LINEAR_MIPMAP_NEAREST },
				{ "GL_NEAREST_MIPMAP_LINEAR", GL_NEAREST_MIPMAP_LINEAR },
				{ "GL_LINEAR_MIPMAP_LINEAR", GL_LINEAR_MIPMAP_LINEAR }
			};

			const std::unordered_map<std::string, GLint> TextureConfiguration::wrapType = std::unordered_map<std::string, GLint>{
				{ "GL_CLAMP_TO_EDGE", GL_CLAMP_TO_EDGE },
				{ "GL_CLAMP_TO_BORDER", GL_CLAMP_TO_BORDER},
				{ "GL_MIRRORED_REPEAT", GL_MIRRORED_REPEAT },
				{ "GL_REPEAT", GL_REPEAT },
				{ "GL_MIRROR_CLAMP_TO_EDGE", GL_MIRROR_CLAMP_TO_EDGE }
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

				auto minFilter = element->Attribute("MinFilter");
				if (minFilter != nullptr)
				{
					auto tmp = filters.find(minFilter);
					if (tmp == filters.end())
						throw "Brak takiego typu filtra!";
					tex.MinFilter = tmp->second;
				}

				auto magFilter = element->Attribute("MagFilter");
				if (magFilter != nullptr)
				{
					auto tmp = filters.find(magFilter);
					if (tmp == filters.end())
						throw "Brak takiego typu filtra!";
					tex.MagFilter = tmp->second;
				}

				auto wrapS = element->Attribute("WrapS");
				if (wrapS != nullptr)
				{
					auto tmp = wrapType.find(wrapS);
					if (tmp == wrapType.end())
						throw "Brak takiego typu wrapowania!";
					tex.WrapS = tmp->second;
				}

				auto wrapT = element->Attribute("WrapT");
				if (wrapT != nullptr)
				{
					auto tmp = wrapType.find(wrapT);
					if (tmp == wrapType.end())
						throw "Brak takiego typu wrapowania!";
					tex.WrapT = tmp->second;
				}

				float sizeMultiplier;
				auto sizeM = element->QueryFloatAttribute("SizeMultiplier", &sizeMultiplier);
				if (sizeM == tinyxml2::XMLError::XML_SUCCESS)
				{
					tex.SizeMultiplier = sizeMultiplier;
				}

				return tex;
			}

			TextureConfiguration::TextureConfiguration(std::string name, GLuint format, GLuint dataType) : Format(format), DataType(dataType), Name(name)
			{
			}

			InputPair::InputPair(std::string texture, std::string locationName) : LocationName(locationName), Texture(texture)
			{
			}

			OutputTexture::OutputTexture(std::string texture) :
				Texture(texture), IsScreen(false)
			{
			}

			RendererConfiguration RendererConfiguration::Load(tinyxml2::XMLElement* element)
			{
				RendererConfiguration configuration;

				auto format = element->Attribute("Deffered");
				if (format != nullptr && std::strcmp(format, "true") == 0)
				{
					configuration.Deffered = true;
				}

				format = element->Attribute("GlobalShadows");
				if (format != nullptr && std::strcmp(format, "true") == 0)
				{
					configuration.GlobalShadows = true;
				}

				auto output = element->FirstChildElement();
				if (output != nullptr)
				{
					if (std::strcmp(output->Name(), "Output") != 0)
						throw "Wrong renderer configuration element!";

					for (auto outputInfo = output->FirstChildElement(); outputInfo != nullptr; outputInfo = outputInfo->NextSiblingElement())
					{
						if (strcmp(outputInfo->Name(), "ScreenTexture") == 0)
						{
							configuration.Output.push_back(OutputTexture{ std::string() });
						}
						else if (strcmp(outputInfo->Name(), "OutputTexture") == 0)
						{
							auto texture = outputInfo->Attribute("Texture");
							configuration.Output.push_back(OutputTexture{ std::string(texture) });
						}
						else
						{
							throw "No texture info";
						}
					}
				}

				return configuration;
			}
		}
	}
}