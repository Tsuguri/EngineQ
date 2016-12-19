#ifndef ENGINEQ_GRAPHICS_RENDERER_CONFIGURATION_HPP
#define ENGINEQ_GRAPHICS_RENDERER_CONFIGURATION_HPP

// Standard includes
#include <string>
#include <vector>
#include <unordered_map>

// Libraries
#include <GL/glew.h>

// Other projects
#include "EngineQCommon/Libraries/TinyXML/tinyxml2.h"
#include "EngineQCommon/Resources/Resource.hpp"

// This project
#include "EngineQRenderer/Graphics/Shader.hpp"


namespace EngineQ
{
	namespace Graphics
	{
		namespace Configuration
		{
			class TextureConfiguration
			{
				static const std::unordered_map<std::string, GLuint> internalFormats;
				static const std::unordered_map<std::string, GLuint> formats;
				static const std::unordered_map<std::string, GLuint> dataTypes;
			public:
				static TextureConfiguration Load(tinyxml2::XMLElement * node);
				TextureConfiguration(std::string name = "", GLuint format = GL_RGB, GLuint dataType = GL_UNSIGNED_BYTE);
				GLuint Format = GL_RGB;
				GLuint InternalFormat = GL_RGB;
				GLuint DataType = GL_UNSIGNED_BYTE;
				std::string Name;
			};

			class InputPair
			{
			public:
				InputPair(std::string texture, std::string locationName = "");
				std::string LocationName;
				std::string Texture;
			};

			class OutputTexture
			{
			public:
				OutputTexture(std::string texture);
				std::string Texture;
			};

			class EffectConfiguration
			{
			public:
				Resources::Resource<Shader> EffectShader;
				std::string ClassName = "";//C# class name
				bool DepthTesting = false;
				bool ApplyShadowInfo = false;
				std::vector<InputPair> Input;
				std::vector<OutputTexture> Output;
			};

			class RendererConfiguration
			{
			public:
				bool Deffered = false;
				bool GlobalShadows = false;
				std::vector<OutputTexture> Output;

				static RendererConfiguration Load(tinyxml2::XMLElement* element);
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
}

#endif