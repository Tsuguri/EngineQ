#include <EngineQ/Engine.hpp>
#include <EngineQ/Vertex.hpp>

#include <EngineQ/Utilities/ResourcesIDs.hpp>
#include <EngineQ/Resources/ModelLoader.hpp>

#include <EngineQ/Graphics/Mesh.hpp>

#include <EngineQ/Objects/Entity.hpp>
#include <EngineQ/Objects/Transform.hpp>
#include <EngineQ/Objects/Renderable.hpp>
#include <EngineQ/Objects/Camera.hpp>
#include <EngineQ/Objects/Light.hpp>

#include <EngineQ/Graphics/ShaderProperties.hpp>
#include <EngineQ/Graphics/Texture.hpp>

#include <EngineQ/Resources/Resource.hpp>
#include <EngineQ/Resources/ShaderFactory.hpp>

#include <EngineQ/Libraries/TinyXML/tinyxml2.h>

namespace Math = EngineQ::Math;

std::unique_ptr<EngineQ::Graphics::Mesh> GenerateCube(float side = 1.0f)
{
	side *= 0.5f;

	Math::Vector3 color{ 0.5f };

	std::vector<EngineQ::VertexPNC> vertices{
		{ Math::Vector3{ +side, -side, -side }, Math::Vector3{ 0.0f, 0.0f, -1.0f }, color },
		{ Math::Vector3{ -side, -side, -side }, Math::Vector3{ 0.0f, 0.0f, -1.0f }, color },
		{ Math::Vector3{ +side, +side, -side }, Math::Vector3{ 0.0f, 0.0f, -1.0f }, color },

		{ Math::Vector3{ -side, -side, -side }, Math::Vector3{ 0.0f, 0.0f, -1.0f }, color },
		{ Math::Vector3{ -side, +side, -side }, Math::Vector3{ 0.0f, 0.0f, -1.0f }, color },
		{ Math::Vector3{ +side, +side, -side }, Math::Vector3{ 0.0f, 0.0f, -1.0f }, color },

		{ Math::Vector3{ +side, -side, +side }, Math::Vector3{ 0.0f, 0.0f, 1.0f }, color },
		{ Math::Vector3{ +side, +side, +side }, Math::Vector3{ 0.0f, 0.0f, 1.0f }, color },
		{ Math::Vector3{ -side, -side, +side }, Math::Vector3{ 0.0f, 0.0f, 1.0f }, color },

		{ Math::Vector3{ -side, -side, +side }, Math::Vector3{ 0.0f, 0.0f, 1.0f }, color },
		{ Math::Vector3{ +side, +side, +side }, Math::Vector3{ 0.0f, 0.0f, 1.0f }, color },
		{ Math::Vector3{ -side, +side, +side }, Math::Vector3{ 0.0f, 0.0f, 1.0f }, color },

		{ Math::Vector3{ -side, -side, -side }, Math::Vector3{ -1.0f, 0.0f, 0.0f }, color },
		{ Math::Vector3{ -side, +side, +side }, Math::Vector3{ -1.0f, 0.0f, 0.0f }, color },
		{ Math::Vector3{ -side, +side, -side }, Math::Vector3{ -1.0f, 0.0f, 0.0f }, color },

		{ Math::Vector3{ -side, +side, +side }, Math::Vector3{ -1.0f, 0.0f, 0.0f }, color },
		{ Math::Vector3{ -side, -side, -side }, Math::Vector3{ -1.0f, 0.0f, 0.0f }, color },
		{ Math::Vector3{ -side, -side, +side }, Math::Vector3{ -1.0f, 0.0f, 0.0f }, color },

		{ Math::Vector3{ +side, -side, -side }, Math::Vector3{ 1.0f, 0.0f, 0.0f }, color },
		{ Math::Vector3{ +side, +side, -side }, Math::Vector3{ 1.0f, 0.0f, 0.0f }, color },
		{ Math::Vector3{ +side, +side, +side }, Math::Vector3{ 1.0f, 0.0f, 0.0f }, color },

		{ Math::Vector3{ +side, +side, +side }, Math::Vector3{ 1.0f, 0.0f, 0.0f }, color },
		{ Math::Vector3{ +side, -side, +side }, Math::Vector3{ 1.0f, 0.0f, 0.0f }, color },
		{ Math::Vector3{ +side, -side, -side }, Math::Vector3{ 1.0f, 0.0f, 0.0f }, color },

		{ Math::Vector3{ +side, -side, -side }, Math::Vector3{ 0.0f, -1.0f, 0.0f }, color },
		{ Math::Vector3{ +side, -side, +side }, Math::Vector3{ 0.0f, -1.0f, 0.0f }, color },
		{ Math::Vector3{ -side, -side, -side }, Math::Vector3{ 0.0f, -1.0f, 0.0f }, color },

		{ Math::Vector3{ -side, -side, +side }, Math::Vector3{ 0.0f, -1.0f, 0.0f }, color },
		{ Math::Vector3{ -side, -side, -side }, Math::Vector3{ 0.0f, -1.0f, 0.0f }, color },
		{ Math::Vector3{ +side, -side, +side }, Math::Vector3{ 0.0f, -1.0f, 0.0f }, color },

		{ Math::Vector3{ +side, +side, +side }, Math::Vector3{ 0.0f, 1.0f, 0.0f }, color },
		{ Math::Vector3{ +side, +side, -side }, Math::Vector3{ 0.0f, 1.0f, 0.0f }, color },
		{ Math::Vector3{ -side, +side, -side }, Math::Vector3{ 0.0f, 1.0f, 0.0f }, color },

		{ Math::Vector3{ -side, +side, -side }, Math::Vector3{ 0.0f, 1.0f, 0.0f }, color },
		{ Math::Vector3{ -side, +side, +side }, Math::Vector3{ 0.0f, 1.0f, 0.0f }, color },
		{ Math::Vector3{ +side, +side, +side }, Math::Vector3{ 0.0f, 1.0f, 0.0f }, color },
	};

	std::vector<unsigned int> indices{};
	indices.reserve(vertices.size());
	for (unsigned int i = 0; i < vertices.size(); ++i)
		indices.push_back(i);

	return std::make_unique<EngineQ::Graphics::Mesh>(vertices, indices);
}

std::unique_ptr<EngineQ::Graphics::Mesh> GenerateCube2(float side = 1.0f)
{
	side *= 0.5f;

	Math::Vector3 color{ 0.5f };

	std::vector<EngineQ::VertexPNTC> vertices = {
		{ Math::Vector3{ +side, -side, -side }, Math::Vector3{ 0.0f, 0.0f, -1.0f }, Math::Vector2{ 1.0f, 0.0f }, color }, // 0
		{ Math::Vector3{ -side, -side, -side }, Math::Vector3{ 0.0f, 0.0f, -1.0f }, Math::Vector2{ 0.0f, 0.0f }, color }, // 1
		{ Math::Vector3{ +side, +side, -side }, Math::Vector3{ 0.0f, 0.0f, -1.0f }, Math::Vector2{ 1.0f, 1.0f }, color }, // 2

	//	{ Math::Vector3{ -side, -side, -side }, Math::Vector3{ 0.0f, 0.0f, -1.0f }, Math::Vector2{ 0.0f, 0.0f }, color }, // 1
		{ Math::Vector3{ -side, +side, -side }, Math::Vector3{ 0.0f, 0.0f, -1.0f }, Math::Vector2{ 0.0f, 1.0f }, color }, // 3
	//	{ Math::Vector3{ +side, +side, -side }, Math::Vector3{ 0.0f, 0.0f, -1.0f }, Math::Vector2{ 1.0f, 1.0f }, color }, // 2


		{ Math::Vector3{ +side, -side, +side }, Math::Vector3{ 0.0f, 0.0f, 1.0f }, Math::Vector2{ 0.0f, 0.0f }, color }, // 4
		{ Math::Vector3{ +side, +side, +side }, Math::Vector3{ 0.0f, 0.0f, 1.0f }, Math::Vector2{ 0.0f, 1.0f }, color }, // 5
		{ Math::Vector3{ -side, -side, +side }, Math::Vector3{ 0.0f, 0.0f, 1.0f }, Math::Vector2{ 1.0f, 0.0f }, color }, // 6

	//	{ Math::Vector3{ -side, -side, +side }, Math::Vector3{ 0.0f, 0.0f, 1.0f }, Math::Vector2{ 0.0f, 0.0f }, color }, // 6
	//	{ Math::Vector3{ +side, +side, +side }, Math::Vector3{ 0.0f, 0.0f, 1.0f }, Math::Vector2{ 0.0f, 0.0f }, color }, // 5
		{ Math::Vector3{ -side, +side, +side }, Math::Vector3{ 0.0f, 0.0f, 1.0f }, Math::Vector2{ 1.0f, 1.0f }, color }, // 7


		{ Math::Vector3{ -side, -side, -side }, Math::Vector3{ -1.0f, 0.0f, 0.0f }, Math::Vector2{ 1.0f, 0.0f }, color }, // 8
		{ Math::Vector3{ -side, +side, +side }, Math::Vector3{ -1.0f, 0.0f, 0.0f }, Math::Vector2{ 0.0f, 1.0f }, color }, // 9
		{ Math::Vector3{ -side, +side, -side }, Math::Vector3{ -1.0f, 0.0f, 0.0f }, Math::Vector2{ 1.0f, 1.0f }, color }, // 10

	//	{ Math::Vector3{ -side, +side, +side }, Math::Vector3{ -1.0f, 0.0f, 0.0f }, Math::Vector2{ 0.0f, 0.0f }, color }, // 9
	//	{ Math::Vector3{ -side, -side, -side }, Math::Vector3{ -1.0f, 0.0f, 0.0f }, Math::Vector2{ 0.0f, 0.0f }, color }, // 8
		{ Math::Vector3{ -side, -side, +side }, Math::Vector3{ -1.0f, 0.0f, 0.0f }, Math::Vector2{ 0.0f, 0.0f }, color }, // 11


		{ Math::Vector3{ +side, -side, -side }, Math::Vector3{ 1.0f, 0.0f, 0.0f }, Math::Vector2{ 0.0f, 0.0f }, color }, // 12
		{ Math::Vector3{ +side, +side, -side }, Math::Vector3{ 1.0f, 0.0f, 0.0f }, Math::Vector2{ 0.0f, 1.0f }, color }, // 13
		{ Math::Vector3{ +side, +side, +side }, Math::Vector3{ 1.0f, 0.0f, 0.0f }, Math::Vector2{ 1.0f, 1.0f }, color }, // 14

	//	{ Math::Vector3{ +side, +side, +side }, Math::Vector3{ 1.0f, 0.0f, 0.0f }, Math::Vector2{ 0.0f, 0.0f }, color }, // 14
		{ Math::Vector3{ +side, -side, +side }, Math::Vector3{ 1.0f, 0.0f, 0.0f }, Math::Vector2{ 1.0f, 0.0f }, color }, // 15
	//	{ Math::Vector3{ +side, -side, -side }, Math::Vector3{ 1.0f, 0.0f, 0.0f }, Math::Vector2{ 0.0f, 0.0f }, color }, // 12


		{ Math::Vector3{ +side, -side, -side }, Math::Vector3{ 0.0f, -1.0f, 0.0f }, Math::Vector2{ 1.0f, 1.0f }, color }, // 16
		{ Math::Vector3{ +side, -side, +side }, Math::Vector3{ 0.0f, -1.0f, 0.0f }, Math::Vector2{ 1.0f, 0.0f }, color }, // 17
		{ Math::Vector3{ -side, -side, -side }, Math::Vector3{ 0.0f, -1.0f, 0.0f }, Math::Vector2{ 0.0f, 1.0f }, color }, // 18

		{ Math::Vector3{ -side, -side, +side }, Math::Vector3{ 0.0f, -1.0f, 0.0f }, Math::Vector2{ 0.0f, 0.0f }, color }, // 19
	//	{ Math::Vector3{ -side, -side, -side }, Math::Vector3{ 0.0f, -1.0f, 0.0f }, Math::Vector2{ 0.0f, 0.0f }, color }, // 18
	//	{ Math::Vector3{ +side, -side, +side }, Math::Vector3{ 0.0f, -1.0f, 0.0f }, Math::Vector2{ 0.0f, 0.0f }, color }, // 17


		{ Math::Vector3{ +side, +side, +side }, Math::Vector3{ 0.0f, 1.0f, 0.0f }, Math::Vector2{ 1.0f, 1.0f }, color }, // 20
		{ Math::Vector3{ +side, +side, -side }, Math::Vector3{ 0.0f, 1.0f, 0.0f }, Math::Vector2{ 1.0f, 0.0f }, color }, // 21
		{ Math::Vector3{ -side, +side, -side }, Math::Vector3{ 0.0f, 1.0f, 0.0f }, Math::Vector2{ 0.0f, 0.0f }, color }, // 22

	//	{ Math::Vector3{ -side, +side, -side }, Math::Vector3{ 0.0f, 1.0f, 0.0f }, Math::Vector2{ 0.0f, 0.0f }, color }, // 22
		{ Math::Vector3{ -side, +side, +side }, Math::Vector3{ 0.0f, 1.0f, 0.0f }, Math::Vector2{ 0.0f, 1.0f }, color }, // 23
	//	{ Math::Vector3{ +side, +side, +side }, Math::Vector3{ 0.0f, 1.0f, 0.0f }, Math::Vector2{ 0.0f, 0.0f }, color }, // 20
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

/*
void PrepareScene(EngineQ::Scene& scene)
{
	//	EngineQ::Resources::ModelLoader loader;
	//	auto model = loader.LoadModel("Models/skull2.obj", EngineQ::Resources::VertexComponent::Position | EngineQ::Resources::VertexComponent::Normal | EngineQ::Resources::VertexComponent::TextureCoordinates, EngineQ::Resources::ModelLoader::Config{});

	//	const auto& modelMesh = model->GetRootNode().GetChildren()[0]->GetMeshes()[0];
	//	auto mesh = new EngineQ::Graphics::Mesh{ modelMesh };




	auto& ent1 = scene.CreateEntity(true, "Camera");
	auto& ent2 = scene.CreateEntity(true, "Skull1");
	auto& ent3 = scene.CreateEntity(true, "Skull2");
	auto& ent4 = scene.CreateEntity();

	auto& renderable1 = ent2.AddComponent<EngineQ::Renderable>();
	auto& renderable2 = ent3.AddComponent<EngineQ::Renderable>();
	auto& renderable3 = ent4.AddComponent<EngineQ::Renderable>();
	auto& resourceManager = EngineQ::Engine::Get().GetResourceManager();

	auto& scriptEngine = EngineQ::Engine::Get().GetScriptEngine();


	//	auto model = resourceManager.GetResource<EngineQ::Resources::Model>("Skull");
	//	auto modelMesh = model->GetRootNode().GetChildren()[0]->GetMeshes()[0];
	auto cubeMesh = resourceManager.GetResource<EngineQ::Graphics::Mesh>("Cube");
	auto mesh = resourceManager.GetResource<EngineQ::Graphics::Mesh>("Skull");


	auto shd = resourceManager.GetResource<EngineQ::Graphics::Shader>(Utilities::ResourcesIDs::BasicShader);
	auto deffShd = resourceManager.GetResource<EngineQ::Graphics::Shader>(Utilities::ResourcesIDs::DeferredGeometry);

	auto& cam = ent1.AddComponent<EngineQ::Camera>();


	//	auto texture = std::make_shared<EngineQ::Graphics::Texture>("Textures/Numbers.png", true);
	auto texture = resourceManager.GetResource<EngineQ::Graphics::Texture>("Numbers");

	auto deffShdCustom = resourceManager.GetResource<EngineQ::Graphics::Shader>(Utilities::ResourcesIDs::DeferredGeometry);
	renderable1.SetMesh(mesh);
	renderable1.GetEntity().GetTransform().SetScale(Math::Vector3f{ 0.1f });
	renderable1.SetForwardShader(shd);
	renderable1.SetDeferredShader(deffShd);
	renderable2.SetMesh(mesh);
	renderable2.GetEntity().GetTransform().SetScale(Math::Vector3f{ 0.1f });
	renderable2.SetForwardShader(shd);
	renderable2.SetDeferredShader(deffShdCustom);
	renderable3.SetMesh(cubeMesh);
	renderable3.SetForwardShader(shd);
	renderable3.SetDeferredShader(deffShd);

	renderable1.GetDeferredShader()->GetMaterial().DiffuseTexture = texture;
	renderable2.GetDeferredShader()->GetMaterial().DiffuseTexture = texture;
	renderable3.GetDeferredShader()->GetMaterial().DiffuseTexture = texture;

	ent3.GetTransform().SetPosition(EngineQ::Math::Vector3(1.0f, 0, 0));
	ent1.GetTransform().SetPosition(EngineQ::Math::Vector3(0, 0, -2.0f));
	ent4.GetTransform().SetPosition(EngineQ::Math::Vector3(2.0f, 0, 0));

	EngineQ::Scripting::ScriptClass scriptClass = scriptEngine.GetScriptClass("QScripts", "QScripts", "CameraMoveClass");

	ent1.AddScript(scriptClass);
	EngineQ::Scripting::ScriptClass scriptClass2 = scriptEngine.GetScriptClass("QScripts", "QScripts", "RotateTest");
	ent2.AddScript(scriptClass2, false);


	scene.SetActiveCamera(&cam);

	auto& lightEntity = scene.CreateEntity();
	auto& light = lightEntity.AddComponent<EngineQ::Light>();
}
*/

/*
void TemporaryResources()
{
	auto& resourceManager = EngineQ::Engine::Get().GetResourceManager();

	resourceManager.RegisterResource<EngineQ::Graphics::Shader>(Utilities::ResourcesIDs::BasicShader, "./Shaders/Basic.shd");
	resourceManager.RegisterResource<EngineQ::Graphics::Shader>(Utilities::ResourcesIDs::CustomShader, "./Shaders/Custom.shd");
	resourceManager.RegisterResource<EngineQ::Graphics::Shader>(Utilities::ResourcesIDs::QuadShader, "./Shaders/Quad.shd");
	resourceManager.RegisterResource<EngineQ::Graphics::Shader>(Utilities::ResourcesIDs::BlurShader, "./Shaders/Bloom/Blur.shd");
	resourceManager.RegisterResource<EngineQ::Graphics::Shader>(Utilities::ResourcesIDs::BlurVShader, "./Shaders/Bloom/BlurV.shd");
	resourceManager.RegisterResource<EngineQ::Graphics::Shader>(Utilities::ResourcesIDs::BrightExtract, "./Shaders/Bloom/BrightExtract.shd");
	resourceManager.RegisterResource<EngineQ::Graphics::Shader>(Utilities::ResourcesIDs::CombineShader, "./Shaders/Bloom/Combine.shd");
	resourceManager.RegisterResource<EngineQ::Graphics::Shader>(Utilities::ResourcesIDs::DeferredLightning, "./Shaders/Deferred/DeferredLightning.shd");
	resourceManager.RegisterResource<EngineQ::Graphics::Shader>(Utilities::ResourcesIDs::DeferredGeometry, "./Shaders/Deferred/DeferredGeometry.shd");
	resourceManager.RegisterResource<EngineQ::Graphics::Shader>("TestDeferred1", "./Shaders/Deferred/DeferredGeometry2.shd");
	resourceManager.RegisterResource<EngineQ::Graphics::Shader>("TestDeferred2", "./Shaders/Deferred/DeferredGeometry3.shd");
	resourceManager.RegisterResource<EngineQ::Graphics::Shader>(Utilities::ResourcesIDs::CustomDeferred, "./Shaders/Deferred/DeferredCustom.shd");

	resourceManager.RegisterResource<EngineQ::Graphics::Texture>("Numbers", "./Textures/Numbers.qres");


	//	resourceManager.RegisterResource<EngineQ::Resources::Model>("Skull", "./Models/Skull.qres");

	//	resourceManager.RegisterResource<EngineQ::Graphics::Mesh>("Skull", [](EngineQ::Resources::ResourceManager& resourceManager)
	//	{	
	//		auto model = resourceManager.GetResource<EngineQ::Resources::Model>("Skull");
	//		auto modelMesh = model->GetRootNode().GetChildren()[0]->GetMeshes()[0];

	//		return std::make_unique<EngineQ::Graphics::Mesh>(modelMesh);
	//	});

	resourceManager.RegisterResource<EngineQ::Graphics::Mesh>("Skull", "./Meshes/Skull.qres");

	resourceManager.RegisterResource<EngineQ::Graphics::Mesh>("Cube", [](EngineQ::Resources::ResourceManager&)
	{
		return GenerateCube2(0.6f);
	});
}
*/

void RegisterBuildInResources()
{
	auto& resourceManager = EngineQ::Engine::Get().GetResourceManager();


	resourceManager.RegisterResource<EngineQ::Graphics::Mesh>("EngineQ/Cube", [](EngineQ::Resources::ResourceManager&)
	{
		return GenerateCube2(0.6f);
	});
}

void ParseConfig(const char* applicationPath, const char* path)
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


	EngineQ::Engine::Initialize(config);

	RegisterBuildInResources();
}

int main(int argc, char** argv)
{
	ParseConfig(argv[0], "./Config.xml");

	EngineQ::Engine& engine = EngineQ::Engine::Get();

	//	TemporaryResources();
	//	auto& scene = engine.GetCurrentScene();
	//	PrepareScene(scene);

	engine.Run();

	return 0;
}