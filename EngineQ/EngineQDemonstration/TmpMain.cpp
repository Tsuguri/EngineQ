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


namespace Math = EngineQ::Math;

EngineQ::Graphics::Mesh* GenerateCube(float side = 1.0f)
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

	return new EngineQ::Graphics::Mesh{ vertices, indices };
}

EngineQ::Graphics::Mesh* GenerateCube2(float side = 1.0f)
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

	return new EngineQ::Graphics::Mesh{ vertices, indices };
}

EngineQ::Graphics::Mesh* GenerateSphere(float radius = 1.0f, float verticalStep = 10.0f, float horizontalStep = 10.0f)
{
	std::vector<EngineQ::VertexPNC> vertices{};


	for (int i = 0; i < 180; i += verticalStep)
	{
		for (int i = 0; i < 190; i += horizontalStep);
	}
	std::vector<unsigned int> indices{};
	indices.reserve(vertices.size());
	for (unsigned int i = 0; i < vertices.size(); ++i)
		indices.push_back(i);

	return new EngineQ::Graphics::Mesh{ vertices,indices };
}

void PrepareScene(EngineQ::Scene* scene)
{
	auto& sc{ *scene };

	EngineQ::Resources::ModelLoader2 loader;
	auto model = loader.LoadModel("Models/skull2.obj");

	const auto& modelMesh = model->GetRootNode().GetChildren()[0]->GetMeshes()[0];
	auto mesh = new EngineQ::Graphics::Mesh{ modelMesh.GetVertices(), modelMesh.GetIndices() };

	auto cubeMesh = GenerateCube2(0.6f);

	auto ent = sc.CreateEntity();
	auto ent2 = sc.CreateEntity();
	auto ent3 = sc.CreateEntity();
	auto ent4 = sc.CreateEntity();

	auto renderable = ent2->AddComponent<EngineQ::Renderable>();
	auto renderable2 = ent3->AddComponent<EngineQ::Renderable>();
	auto renderable3 = ent4->AddComponent<EngineQ::Renderable>();
	auto rm = EngineQ::Engine::Get()->GetResourceManager();

	auto shd = rm->GetResource<EngineQ::Graphics::Shader>(Utilities::ResourcesIDs::BasicShader);
	auto deffShd = rm->GetResource<EngineQ::Graphics::Shader>(Utilities::ResourcesIDs::DeferredGeometry);

	auto cam = ent->AddComponent<EngineQ::Camera>();


	auto texture = std::make_shared<EngineQ::Graphics::Texture>("Textures/Numbers.png", true);

		
	auto deffShdCustom = rm->GetResource<EngineQ::Graphics::Shader>(Utilities::ResourcesIDs::DeferredGeometry);
	renderable->SetMesh(mesh);
	renderable->SetForwardShader(*shd);
	renderable->SetDeferredShader(*deffShd);
	renderable2->SetMesh(mesh);
	renderable2->SetForwardShader(*shd);
	renderable2->SetDeferredShader(*deffShdCustom);
	renderable3->SetMesh(cubeMesh);
	renderable3->SetForwardShader(*shd);
	renderable3->SetDeferredShader(*deffShd);

	auto textureProp1 = renderable->GetDeferredShader()->GetProperty<std::shared_ptr<EngineQ::Graphics::Texture>>("diffuseTexture");
	textureProp1 = texture;

	auto textureProp3 = renderable3->GetDeferredShader()->GetProperty<std::shared_ptr<EngineQ::Graphics::Texture>>("diffuseTexture");
	textureProp3 = texture;


	ent3->GetTransform().SetPosition(EngineQ::Math::Vector3(1.0f,0,0));
	ent->GetTransform().SetPosition(EngineQ::Math::Vector3(0, 0, -2.0f));
	ent4->GetTransform().SetPosition(EngineQ::Math::Vector3(2.0f, 0, 0));

	EngineQ::Scripting::ScriptClass scriptClass = EngineQ::Engine::Get()->GetClass("QScripts", "QScripts", "CameraMoveClass");

	ent->AddScript(scriptClass);
	EngineQ::Scripting::ScriptClass scriptClass2 = EngineQ::Engine::Get()->GetClass("QScripts", "QScripts", "RotateTest");
	ent2->AddScript(scriptClass2);


	sc.ActiveCamera(cam);

	auto lightEntity = sc.CreateEntity();
	auto light = lightEntity->AddComponent<EngineQ::Light>();
}

void TemporaryResources(EngineQ::Engine* engine)
{
	auto rm = EngineQ::Engine::Get()->GetResourceManager();
	rm->AddResource<EngineQ::Graphics::Shader>(Utilities::ResourcesIDs::BasicShader, "./Shaders/Basic.shd");
	rm->AddResource<EngineQ::Graphics::Shader>(Utilities::ResourcesIDs::CustomShader, "./Shaders/Custom.shd");
	rm->AddResource<EngineQ::Graphics::Shader>(Utilities::ResourcesIDs::QuadShader, "./Shaders/Quad.shd");
	rm->AddResource<EngineQ::Graphics::Shader>(Utilities::ResourcesIDs::BlurShader, "./Shaders/Bloom/Blur.shd");
	rm->AddResource<EngineQ::Graphics::Shader>(Utilities::ResourcesIDs::BlurVShader, "./Shaders/Bloom/BlurV.shd");
	rm->AddResource<EngineQ::Graphics::Shader>(Utilities::ResourcesIDs::BrightExtract, "./Shaders/Bloom/BrightExtract.shd");
	rm->AddResource<EngineQ::Graphics::Shader>(Utilities::ResourcesIDs::CombineShader, "./Shaders/Bloom/Combine.shd");
	rm->AddResource<EngineQ::Graphics::Shader>(Utilities::ResourcesIDs::DeferredLightning, "./Shaders/Deferred/DeferredLightning.shd");
	rm->AddResource<EngineQ::Graphics::Shader>(Utilities::ResourcesIDs::DeferredGeometry, "./Shaders/Deferred/DeferredGeometry.shd");
	rm->AddResource<EngineQ::Graphics::Shader>(Utilities::ResourcesIDs::CustomDeferred, "./Shaders/Deferred/DeferredCustom.shd");
}


int main(int argc, char** argv)
{
	
	EngineQ::Engine::Initialize("Turbo giera", 800, 600, argv[0]);
	TemporaryResources(EngineQ::Engine::Get());
	EngineQ::Engine::Get()->SetPostprocessingConfiguration("./postprocessing.conf");

	auto sc = EngineQ::Engine::Get()->CreateScene();
	PrepareScene(sc);

	EngineQ::Engine::Get()->Run(sc);

	return 0;
}