#include "RendererIntermediateConfiguration.hpp"

// Other projects
#include "EngineQCommon/Resources/Resource.hpp"


namespace EngineQ
{
	Graphics::Configuration::EffectConfiguration IntermediateEffectConfiguration::ToEffectConfiguration(Resources::ResourceManager* manager)
	{
		auto configuration = Graphics::Configuration::EffectConfiguration();

		configuration.Name = this->Name;

		if (this->Iterations < 0)
		{
			configuration.ClassName = ClassName;
			configuration.ClassNamespace = ClassNamespace;
			configuration.ClassAssembly = ClassAssembly;
			configuration.DepthTesting = DepthTesting;
			configuration.Input = Input;
			configuration.Output = Output;
			configuration.EffectShader = manager->GetResource<Graphics::Shader>(this->ShaderName);
			configuration.ApplyShadowInfo = ApplyShadowInfo;
		}
		else
		{
			configuration.Iterations = this->Iterations;
			configuration.Effects.reserve(this->Effects.size());
			for (auto& effect : this->Effects)
				configuration.Effects.push_back(effect.ToEffectConfiguration(manager));
		}

		return configuration;
	}

	IntermediateEffectConfiguration IntermediateEffectConfiguration::Load(tinyxml2::XMLElement * element)
	{
		auto configuration = IntermediateEffectConfiguration{};

		auto name = element->Attribute("Name");
		if (name != nullptr)
			configuration.Name = name;

		if (std::strcmp(element->Name(), "EffectConfiguration") == 0)
		{
			auto classNode = element->FirstChildElement("Controller");
			if (classNode != nullptr)
			{
				auto className = classNode->Attribute("Class");
				if (className != nullptr)
					configuration.ClassName = className;
				else
					throw std::runtime_error{ "Invalid effect controller. Name is required" };

				auto classAssembly = classNode->Attribute("Assembly");
				if (classAssembly != nullptr)
					configuration.ClassAssembly = classAssembly;
				else
					throw std::runtime_error{ "Invalid effect controller. Assembly name is required" };

				auto classNamespace = classNode->Attribute("Namespace");
				if (classNamespace != nullptr)
					configuration.ClassNamespace = classNamespace;
			}


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
						configuration.Input.push_back(Graphics::Configuration::InputPair{ texture });
					else
						configuration.Input.push_back(Graphics::Configuration::InputPair{ texture,locationName });
				}
			}

			auto output = element->FirstChildElement("Output");
			if (output == nullptr || output->FirstChildElement() == nullptr)
				throw "Shader without output found";
			
			for (auto outputInfo = output->FirstChildElement(); outputInfo != nullptr; outputInfo = outputInfo->NextSiblingElement())
			{
				if (std::strcmp(outputInfo->Name(), "ScreenTexture") == 0)
				{
					configuration.Output.push_back(Graphics::Configuration::OutputTexture{});
				}
				else if (std::strcmp(outputInfo->Name(), "OutputTexture") == 0)
				{
					auto texture = outputInfo->Attribute("Texture");
					configuration.Output.push_back(Graphics::Configuration::OutputTexture{ std::string(texture) });
				}
				else
				{
					throw std::runtime_error{ "Invalid ouptit element" };
				}
			}
		}
		else if (std::strcmp(element->Name(), "EffectRepeat") == 0)
		{
			auto error = element->QueryIntAttribute("Iterations", &configuration.Iterations);
			if (error != tinyxml2::XML_SUCCESS || configuration.Iterations < 0)
				throw std::runtime_error{ "Invalid EffectRepeat Iterations attribute" };

			for (auto effectInfo = element->FirstChildElement(); effectInfo != nullptr; effectInfo = effectInfo->NextSiblingElement())
			{
				Logger::LogMessage("	", effectInfo->Name(), "\n");
				configuration.Effects.push_back(IntermediateEffectConfiguration::Load(effectInfo));
			}
		}
		else
		{
			throw std::runtime_error{ "Invalid Effect node" };
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
