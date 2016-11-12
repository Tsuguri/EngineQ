#ifndef RENDERER_INTERMEDIATE_CONFIGURATION_HPP
#define RENDERER_INTERMEDIATE_CONFIGURATION_HPP


#include <unordered_map>
#include "Graphics\Configuration\RendererConfiguration.hpp"
#include <memory>
#include "Resources\ResourceManager.hpp"
namespace EngineQ
{
	class IntermediateEffectConfiguration
	{
	public:
		std::string Shader;//for resource manager
		std::string ClassName;//C# class name
		bool DepthTesting;
		std::vector<Graphics::Configuration::InputPair> Input;
		std::vector<Graphics::Configuration::OutputTexture> Output;

		Graphics::Configuration::EffectConfiguration ToEffectConfiguration(Resources::ResourceManager* manager);

		static IntermediateEffectConfiguration Load(tinyxml2::XMLElement* element);


	};


	class RenderingUnitConfiguration
	{
	public:
		Graphics::Configuration::RendererConfiguration Renderer;
		std::vector<Graphics::Configuration::TextureConfiguration> Textures;
		std::vector<IntermediateEffectConfiguration> Effects;

		static RenderingUnitConfiguration Load(tinyxml2::XMLElement* element);
		static RenderingUnitConfiguration Load(std::string filePath);
	};
}
#endif