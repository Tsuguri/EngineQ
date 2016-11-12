#include "ShaderFactory.hpp"

#include <unordered_map>

#include <Libraries/TinyXML/tinyxml2.h>

#include "../Graphics/Shader.hpp"

namespace EngineQ
{
	namespace Resources
	{
		std::unique_ptr<Graphics::Shader> ResourceFactory<Graphics::Shader>::CreateResource(ResourceManager& resourceManager, const char* filename)
		{
			static const std::unordered_map<std::string, Graphics::ShaderType> ShaderTypeMap = {
				{ "VertexShader", Graphics::ShaderType::VertexShader },
				{ "FragmentShader", Graphics::ShaderType::FragmentShader },
				{ "GeometryShader", Graphics::ShaderType::GeometryShader },
				{ "ComputeShader", Graphics::ShaderType::ComputeShader }
			};

			tinyxml2::XMLDocument doc{};
			doc.LoadFile(filename);

			if (doc.Error())
				throw ResourceLoadingException{ doc.GetErrorStr1() };

			std::vector<Graphics::ShaderPart> shaders;

			auto rootElement = doc.RootElement();
			for (auto child = rootElement->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
			{
				const char* shaderType = child->Attribute("Type");
				const char* shaderPath = child->Attribute("Path");

				shaders.push_back(Graphics::ShaderPart{ shaderPath, ShaderTypeMap.at(shaderType) });
			}

			return std::make_unique<Graphics::Shader>(shaders);
		}
	}
}