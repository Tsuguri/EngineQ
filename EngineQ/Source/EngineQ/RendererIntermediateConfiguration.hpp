#ifndef RENDERER_INTERMEDIATE_CONFIGURATION_HPP
#define RENDERER_INTERMEDIATE_CONFIGURATION_HPP

// Standard includes
#include <unordered_map>
#include <memory>

// Other projects
#include "EngineQCommon/Libraries/TinyXML/tinyxml2.h"
#include "EngineQRenderer/Graphics/Configuration/RendererConfiguration.hpp"

// This project
#include "Resources/ResourceManager.hpp"


namespace EngineQ
{
	class IntermediateEffectConfiguration
	{
	public:
		// Effect node
		std::string ShaderName;//for resource manager
		std::string ClassName;//C# class name
		bool DepthTesting;
		bool ApplyShadowInfo;
		std::vector<Graphics::Configuration::InputPair> Input;
		std::vector<Graphics::Configuration::OutputTexture> Output;

		// Loop node
		int Iterations = -1;
		std::vector<IntermediateEffectConfiguration> Effects;

		Graphics::Configuration::EffectConfiguration ToEffectConfiguration(Resources::ResourceManager* manager);

		static IntermediateEffectConfiguration Load(tinyxml2::XMLElement* element);
	};


	class IntermediateRenderingUnitConfiguration
	{
	public:
		Graphics::Configuration::RendererConfiguration Renderer;
		std::vector<Graphics::Configuration::TextureConfiguration> Textures;
		std::vector<IntermediateEffectConfiguration> Effects;

		Graphics::Configuration::RenderingUnitConfiguration ToRenderingUnitConfiguration(Resources::ResourceManager* manager);

		static IntermediateRenderingUnitConfiguration Load(tinyxml2::XMLElement* element);
		static IntermediateRenderingUnitConfiguration Load(std::string filePath);
	};
}
#endif