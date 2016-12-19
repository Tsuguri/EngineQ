#include "RendererIntermediateConfiguration.hpp"

// Other projects
#include "EngineQCommon/Resources/Resource.hpp"


namespace EngineQ
{
	Graphics::Configuration::EffectConfiguration IntermediateEffectConfiguration::ToEffectConfiguration(Resources::ResourceManager * manager)
	{
		auto configuration = Graphics::Configuration::EffectConfiguration();
		configuration.ClassName = ClassName;
		configuration.DepthTesting = DepthTesting;
		configuration.Input = Input;
		configuration.Output = Output;
		configuration.EffectShader = manager->GetResource<Graphics::Shader>(this->ShaderName);
		configuration.ApplyShadowInfo = ApplyShadowInfo;

		return configuration;
	}

	IntermediateEffectConfiguration IntermediateEffectConfiguration::Load(tinyxml2::XMLElement * element)
	{
		auto configuration = IntermediateEffectConfiguration{};

		auto shader = element->Attribute("Shader");
		if (shader == nullptr)
			throw "Shader attribute not found or equal to 0";
		configuration.ShaderName = shader;

		auto depth = element->BoolAttribute("DeptTesting");//default false if not exist
		configuration.DepthTesting = depth;
		
		auto shadows = element->BoolAttribute("ApplyShadowsData");
		configuration.ApplyShadowInfo = shadows;

		auto input = element->FirstChildElement("Input");
		if (input != nullptr)
		{
			for (auto inputInfo = input->FirstChildElement(); inputInfo != nullptr; inputInfo = inputInfo->NextSiblingElement())
			{
				auto texture = inputInfo->Attribute("Texture");
				auto locationName = inputInfo->Attribute("LocationName");
				if (locationName == nullptr)
					configuration.Input.push_back(Graphics::Configuration::InputPair{texture });
				else
					configuration.Input.push_back(Graphics::Configuration::InputPair{texture,locationName });
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
				configuration.Output.push_back(Graphics::Configuration::OutputTexture{ std::string("Screen") });
			}
			else
				configuration.Output.push_back(Graphics::Configuration::OutputTexture{ std::string(texture) });
		}


		return configuration;
	}

	Graphics::Configuration::RenderingUnitConfiguration IntermediateRenderingUnitConfiguration::ToRenderingUnitConfiguration(Resources::ResourceManager* manager)
	{
		auto configuration = Graphics::Configuration::RenderingUnitConfiguration();

		configuration.Renderer = Renderer;
		configuration.Textures = Textures;
		for (auto effect : Effects)
			configuration.Effects.push_back(effect.ToEffectConfiguration(manager));

		return configuration;
	}

	IntermediateRenderingUnitConfiguration IntermediateRenderingUnitConfiguration::Load(tinyxml2::XMLElement * element)
	{
		IntermediateRenderingUnitConfiguration configuration{};
		if (std::string(element->Name()) != "RenderingUnitConfiguration")
			throw "Wrong element name";
		auto textures = element->FirstChildElement("Textures");
		if (textures != nullptr)
		{
			for (auto textureInfo = textures->FirstChildElement(); textureInfo != nullptr; textureInfo = textureInfo->NextSiblingElement())
			{
				Logger::LogMessage("	", textureInfo->Name(), "\n");
				configuration.Textures.push_back(Graphics::Configuration::TextureConfiguration::Load(textureInfo));
			}
		}
		auto renderer = element->FirstChildElement("Renderer");
		if (renderer != nullptr)
		{
			configuration.Renderer = Graphics::Configuration::RendererConfiguration::Load(renderer);
		}
		auto effects = element->FirstChildElement("Effects");
		if (effects != nullptr)
		{
			for (auto effectInfo = effects->FirstChildElement(); effectInfo != nullptr; effectInfo = effectInfo->NextSiblingElement())
			{
				Logger::LogMessage("	", effectInfo->Name(), "\n");
				configuration.Effects.push_back(IntermediateEffectConfiguration::Load(effectInfo));
			}
		}
		return configuration;
	}

	IntermediateRenderingUnitConfiguration IntermediateRenderingUnitConfiguration::Load(std::string filePath)
	{
		tinyxml2::XMLDocument xmlDoc;
		tinyxml2::XMLError eResult = xmlDoc.LoadFile(filePath.c_str());
		if (eResult != tinyxml2::XML_SUCCESS)
			throw "Error parsing XML file";
		return Load(xmlDoc.RootElement());
	}

}
