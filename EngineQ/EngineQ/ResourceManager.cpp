#include "ResourceManager.hpp"

namespace EngineQ
{
	ResourceManager::BaseResource::BaseResource(const std::string& path)
		: path{ path }
	{
	}

	template<>
	ResourceManager::ResourceType ResourceManager::Resource<Graphics::Shader>::GetType()
	{
		return ResourceType::Shader;
	}

	template <>
	ResourceManager::ResourceType ResourceManager::Resource<Resources::Model>::GetType()
	{
		return ResourceType::Model;
	}


	template<>
	void ResourceManager::Resource<Graphics::Shader>::Load()
	{
		static const std::unordered_map<std::string, Graphics::ShaderType> shaderTypeMap = {
			{ "VertexShader", Graphics::ShaderType::VertexShader },
			{ "FragmentShader", Graphics::ShaderType::FragmentShader },
			{ "GeometryShader", Graphics::ShaderType::GeometryShader },
			{ "ComputeShader", Graphics::ShaderType::ComputeShader }
		};


		tinyxml2::XMLDocument doc{};
		doc.LoadFile(this->path.c_str());

		if (doc.Error())
			throw ResourceFileLoadingException{ doc.GetErrorStr1() };

		std::vector<Graphics::ShaderPart> shaders;

		auto rootElement = doc.RootElement();
		for (auto child = rootElement->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
		{
			const char* shaderType = child->Attribute("Type");
			const char* shaderPath = child->Attribute("Path");

			shaders.push_back(Graphics::ShaderPart{ shaderPath, shaderTypeMap.at(shaderType) });
		}

		this->resource = std::make_shared<Graphics::Shader>(shaders);
	}

	template<>
	void ResourceManager::Resource<Resources::Model>::Load()
	{
		tinyxml2::XMLDocument doc{};

		if (doc.Error())
			throw ResourceFileLoadingException{ doc.GetErrorStr1() };

		auto rootElement = doc.RootElement();
	}

	void ResourceManager::Update()
	{
		for (auto& resourcesOfType : this->resources)
			for (auto& resource : resourcesOfType)
				resource.second->Update();
	}
}