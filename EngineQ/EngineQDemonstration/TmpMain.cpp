#include <EngineQ/Engine.hpp>
#include <Graphics/Vertex.hpp>

#include <Utilities/ResourcesIDs.hpp>
#include <EngineQ/Resources/ModelLoader.hpp>

#include <Graphics/Mesh.hpp>

#include <EngineQ/Objects/Entity.hpp>
#include <EngineQ/Objects/Transform.hpp>
#include <EngineQ/Objects/Renderable.hpp>
#include <EngineQ/Objects/Camera.hpp>
#include <EngineQ/Objects/Light.hpp>

#include <Graphics/ShaderProperties.hpp>
#include <Graphics/Texture.hpp>

#include <Resources/Resource.hpp>
#include <EngineQ/Resources/ShaderFactory.hpp>

#include <Libraries/TinyXML/tinyxml2.h>

namespace Math = EngineQ::Math;

std::unique_ptr<EngineQ::Graphics::Mesh> GenerateCube(float side = 1.0f)
{
	side *= 0.5f;

	Math::Vector3 color{ 0.5f };

	std::vector<EngineQ::VertexPNTC> vertices = {
		{ Math::Vector3{ +side, -side, -side }, Math::Vector3{ 0.0f, 0.0f, -1.0f }, Math::Vector2{ 1.0f, 0.0f }, color },
		{ Math::Vector3{ -side, -side, -side }, Math::Vector3{ 0.0f, 0.0f, -1.0f }, Math::Vector2{ 0.0f, 0.0f }, color },
		{ Math::Vector3{ +side, +side, -side }, Math::Vector3{ 0.0f, 0.0f, -1.0f }, Math::Vector2{ 1.0f, 1.0f }, color },
		{ Math::Vector3{ -side, +side, -side }, Math::Vector3{ 0.0f, 0.0f, -1.0f }, Math::Vector2{ 0.0f, 1.0f }, color },

		{ Math::Vector3{ +side, -side, +side }, Math::Vector3{ 0.0f, 0.0f, 1.0f }, Math::Vector2{ 0.0f, 0.0f }, color },
		{ Math::Vector3{ +side, +side, +side }, Math::Vector3{ 0.0f, 0.0f, 1.0f }, Math::Vector2{ 0.0f, 1.0f }, color },
		{ Math::Vector3{ -side, -side, +side }, Math::Vector3{ 0.0f, 0.0f, 1.0f }, Math::Vector2{ 1.0f, 0.0f }, color },
		{ Math::Vector3{ -side, +side, +side }, Math::Vector3{ 0.0f, 0.0f, 1.0f }, Math::Vector2{ 1.0f, 1.0f }, color },

		{ Math::Vector3{ -side, -side, -side }, Math::Vector3{ -1.0f, 0.0f, 0.0f }, Math::Vector2{ 1.0f, 0.0f }, color },
		{ Math::Vector3{ -side, +side, +side }, Math::Vector3{ -1.0f, 0.0f, 0.0f }, Math::Vector2{ 0.0f, 1.0f }, color },
		{ Math::Vector3{ -side, +side, -side }, Math::Vector3{ -1.0f, 0.0f, 0.0f }, Math::Vector2{ 1.0f, 1.0f }, color },
		{ Math::Vector3{ -side, -side, +side }, Math::Vector3{ -1.0f, 0.0f, 0.0f }, Math::Vector2{ 0.0f, 0.0f }, color },

		{ Math::Vector3{ +side, -side, -side }, Math::Vector3{ 1.0f, 0.0f, 0.0f }, Math::Vector2{ 0.0f, 0.0f }, color },
		{ Math::Vector3{ +side, +side, -side }, Math::Vector3{ 1.0f, 0.0f, 0.0f }, Math::Vector2{ 0.0f, 1.0f }, color },
		{ Math::Vector3{ +side, +side, +side }, Math::Vector3{ 1.0f, 0.0f, 0.0f }, Math::Vector2{ 1.0f, 1.0f }, color },
		{ Math::Vector3{ +side, -side, +side }, Math::Vector3{ 1.0f, 0.0f, 0.0f }, Math::Vector2{ 1.0f, 0.0f }, color },

		{ Math::Vector3{ +side, -side, -side }, Math::Vector3{ 0.0f, -1.0f, 0.0f }, Math::Vector2{ 1.0f, 1.0f }, color },
		{ Math::Vector3{ +side, -side, +side }, Math::Vector3{ 0.0f, -1.0f, 0.0f }, Math::Vector2{ 1.0f, 0.0f }, color },
		{ Math::Vector3{ -side, -side, -side }, Math::Vector3{ 0.0f, -1.0f, 0.0f }, Math::Vector2{ 0.0f, 1.0f }, color },
		{ Math::Vector3{ -side, -side, +side }, Math::Vector3{ 0.0f, -1.0f, 0.0f }, Math::Vector2{ 0.0f, 0.0f }, color },

		{ Math::Vector3{ +side, +side, +side }, Math::Vector3{ 0.0f, 1.0f, 0.0f }, Math::Vector2{ 1.0f, 1.0f }, color },
		{ Math::Vector3{ +side, +side, -side }, Math::Vector3{ 0.0f, 1.0f, 0.0f }, Math::Vector2{ 1.0f, 0.0f }, color },
		{ Math::Vector3{ -side, +side, -side }, Math::Vector3{ 0.0f, 1.0f, 0.0f }, Math::Vector2{ 0.0f, 0.0f }, color },
		{ Math::Vector3{ -side, +side, +side }, Math::Vector3{ 0.0f, 1.0f, 0.0f }, Math::Vector2{ 0.0f, 1.0f }, color },
	};

	std::vector<unsigned int> indices = {
		0, 1, 2,
		1, 3, 2,

		4, 5, 6,
		6, 5, 7,

		8, 9, 10,
		9, 8, 11,

		12, 13, 14,
		14, 15, 12,

		16, 17, 18,
		19, 18, 17,

		20, 21, 22,
		22, 23, 20
	};

	return std::make_unique<EngineQ::Graphics::Mesh>(vertices, indices);
}

std::unique_ptr<EngineQ::Graphics::Mesh> GenerateQuad(float side = 1.0f)
{
	side *= 0.5f;

	Math::Vector3 color{ 0.5f };

	std::vector<EngineQ::VertexPNTC> vertices = {
		{ Math::Vector3{ +side, -side, 0.0f }, Math::Vector3{ 0.0f, 0.0f, -1.0f }, Math::Vector2{ 0.0f, 1.0f }, color },
		{ Math::Vector3{ -side, -side, 0.0f }, Math::Vector3{ 0.0f, 0.0f, -1.0f }, Math::Vector2{ 1.0f, 1.0f }, color },
		{ Math::Vector3{ +side, +side, 0.0f }, Math::Vector3{ 0.0f, 0.0f, -1.0f }, Math::Vector2{ 0.0f, 0.0f }, color },
		{ Math::Vector3{ -side, +side, 0.0f }, Math::Vector3{ 0.0f, 0.0f, -1.0f }, Math::Vector2{ 1.0f, 0.0f }, color },
	};

	std::vector<unsigned int> indices = {
		0, 1, 2,
		1, 3, 2,
	};

	return std::make_unique<EngineQ::Graphics::Mesh>(vertices, indices);
}

std::unique_ptr<EngineQ::Graphics::Mesh> GenerateSphere(float radius = 1.0f, float verticalStep = 10.0f, float horizontalStep = 10.0f)
{
	std::vector<EngineQ::VertexPNC> vertices{};


	for (float i = 0; i < 180; i += verticalStep)
	{
		for (float i = 0; i < 190; i += horizontalStep)
		{

		}
	}
	std::vector<unsigned int> indices{};
	indices.reserve(vertices.size());
	for (unsigned int i = 0; i < vertices.size(); ++i)
		indices.push_back(i);

	return std::make_unique<EngineQ::Graphics::Mesh>(vertices, indices);
}

void RegisterBuildInResources()
{
	auto& resourceManager = EngineQ::Engine::Get().GetResourceManager();


	resourceManager.RegisterResource<EngineQ::Graphics::Mesh>("EngineQ/Cube", [](EngineQ::Resources::ResourceManager&)
	{
		return GenerateCube();
	});

	resourceManager.RegisterResource<EngineQ::Graphics::Mesh>("EngineQ/Quad", [](EngineQ::Resources::ResourceManager&)
	{
		return GenerateQuad();
	});
}

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

	RegisterBuildInResources();

	engine.Run();

	return 0;
}