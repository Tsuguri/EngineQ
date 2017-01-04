#include <random>

#include "EngineQCommon/Resources/Resource.hpp"
#include "EngineQCommon/Libraries/TinyXML/tinyxml2.h"

#include "EngineQRenderer/Graphics/Mesh.hpp"
#include "EngineQRenderer/Graphics/Vertex.hpp"
#include "EngineQRenderer/Graphics/ShaderProperties.hpp"
#include "EngineQRenderer/Graphics/Texture.hpp"

#include "EngineQ/Engine.hpp"
#include "EngineQ/Objects/Entity.hpp"
#include "EngineQ/Objects/Transform.hpp"
#include "EngineQ/Objects/Renderable.hpp"
#include "EngineQ/Objects/Camera.hpp"
#include "EngineQ/Objects/Light.hpp"
#include "EngineQ/Resources/ModelLoader.hpp"
#include "EngineQ/Resources/ShaderFactory.hpp"


namespace Math = EngineQ::Math;


EngineQ::Engine::Config ParseConfig(const char* applicationPath, const char* path)
{
	tinyxml2::XMLDocument doc{};
	doc.LoadFile(path);

	if (doc.Error())
		throw std::runtime_error{ doc.GetErrorStr1() };

	auto rootElement = doc.RootElement();
	if (std::strcmp(rootElement->Name(), "Config") != 0)
		throw std::runtime_error{ "Invalid root node" };

	EngineQ::Engine::Config config;

	auto engineAssemblyElement = rootElement->FirstChildElement("EngineAssembly");
	config.engineAssemblyPath = engineAssemblyElement->Attribute("Path");

	auto windowElement = rootElement->FirstChildElement("Window");
	config.windowName = windowElement->Attribute("Name");
	config.windowWidth = windowElement->IntAttribute("Width");
	config.windowHeight = windowElement->IntAttribute("Height");

	auto scriptAssembliesElement = rootElement->FirstChildElement("ScriptAssemblies");
	config.scriptsDirectory = scriptAssembliesElement->Attribute("Directory");
	for (auto assemblyElement = scriptAssembliesElement->FirstChildElement(); assemblyElement != nullptr; assemblyElement = assemblyElement->NextSiblingElement())
		config.scriptAssemblies.push_back(assemblyElement->Attribute("Name"));

	auto initializerElement = rootElement->FirstChildElement("Initializer");
	config.initializerAssembly = initializerElement->Attribute("Assembly");
	config.initializerNamespace = initializerElement->Attribute("Namespace");
	config.initializerClass = initializerElement->Attribute("Class");

	auto monoElement = rootElement->FirstChildElement("Mono");
	config.monoDirectory = monoElement->Attribute("Directory");

	auto postprocessingElement = rootElement->FirstChildElement("Postprocessing");
	config.postprocessingConfig = postprocessingElement->Attribute("Path");

	config.applicationPath = applicationPath;

	return config;
}

int main(int argc, char** argv)
{
	auto config = ParseConfig(argv[0], "./Config.xml");
	//auto config = ParseConfig(argv[0], "./postprocessing.conf");

	EngineQ::Engine::Initialize(config);
	EngineQ::Engine& engine = EngineQ::Engine::Get();

	engine.Run();

	EngineQ::Engine::Finalize();

	return 0;
}