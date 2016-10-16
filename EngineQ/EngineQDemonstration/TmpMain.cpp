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


namespace Math = EngineQ::Math;

EngineQ::Graphics::Mesh* GenerateCube(float side = 1.0f)
{
	Math::Vector3 color{ 0.5f };

	std::vector<EngineQ::VertexPNC> vertices{
		{ Math::Vector3{ +side, -side, -side }, Math::Vector3{ 0.0f, 0.0f, -1.0f }, color },
		{ Math::Vector3{ -side, -side, -side }, Math::Vector3{ 0.0f, 0.0f, -1.0f }, color },
		{ Math::Vector3{ +side, +side, -side }, Math::Vector3{ 0.0f, 0.0f, -1.0f }, color },

		{ Math::Vector3{ -side, +side, -side }, Math::Vector3{ 0.0f, 0.0f, -1.0f }, color },
		{ Math::Vector3{ +side, +side, -side }, Math::Vector3{ 0.0f, 0.0f, -1.0f }, color },
		{ Math::Vector3{ -side, -side, -side }, Math::Vector3{ 0.0f, 0.0f, -1.0f }, color },

		{ Math::Vector3{ +side, +side, +side }, Math::Vector3{ 0.0f, 0.0f, 1.0f }, color },
		{ Math::Vector3{ -side, -side, +side }, Math::Vector3{ 0.0f, 0.0f, 1.0f }, color },
		{ Math::Vector3{ +side, -side, +side }, Math::Vector3{ 0.0f, 0.0f, 1.0f }, color },

		{ Math::Vector3{ +side, +side, +side }, Math::Vector3{ 0.0f, 0.0f, 1.0f }, color },
		{ Math::Vector3{ -side, +side, +side }, Math::Vector3{ 0.0f, 0.0f, 1.0f }, color },
		{ Math::Vector3{ -side, -side, +side }, Math::Vector3{ 0.0f, 0.0f, 1.0f }, color },

		{ Math::Vector3{ -side, +side, +side }, Math::Vector3{ -1.0f, 0.0f, 0.0f }, color },
		{ Math::Vector3{ -side, +side, -side }, Math::Vector3{ -1.0f, 0.0f, 0.0f }, color },
		{ Math::Vector3{ -side, -side, -side }, Math::Vector3{ -1.0f, 0.0f, 0.0f }, color },

		{ Math::Vector3{ -side, -side, -side }, Math::Vector3{ -1.0f, 0.0f, 0.0f }, color },
		{ Math::Vector3{ -side, -side, +side }, Math::Vector3{ -1.0f, 0.0f, 0.0f }, color },
		{ Math::Vector3{ -side, +side, +side }, Math::Vector3{ -1.0f, 0.0f, 0.0f }, color },

		{ Math::Vector3{ +side, +side, -side }, Math::Vector3{ 1.0f, 0.0f, 0.0f }, color },
		{ Math::Vector3{ +side, +side, +side }, Math::Vector3{ 1.0f, 0.0f, 0.0f }, color },
		{ Math::Vector3{ +side, -side, -side }, Math::Vector3{ 1.0f, 0.0f, 0.0f }, color },

		{ Math::Vector3{ +side, -side, +side }, Math::Vector3{ 1.0f, 0.0f, 0.0f }, color },
		{ Math::Vector3{ +side, -side, -side }, Math::Vector3{ 1.0f, 0.0f, 0.0f }, color },
		{ Math::Vector3{ +side, +side, +side }, Math::Vector3{ 1.0f, 0.0f, 0.0f }, color },

		{ Math::Vector3{ +side, -side, +side }, Math::Vector3{ 0.0f, -1.0f, 0.0f }, color },
		{ Math::Vector3{ -side, -side, -side }, Math::Vector3{ 0.0f, -1.0f, 0.0f }, color },
		{ Math::Vector3{ +side, -side, -side }, Math::Vector3{ 0.0f, -1.0f, 0.0f }, color },

		{ Math::Vector3{ -side, -side, -side }, Math::Vector3{ 0.0f, -1.0f, 0.0f }, color },
		{ Math::Vector3{ +side, -side, +side }, Math::Vector3{ 0.0f, -1.0f, 0.0f }, color },
		{ Math::Vector3{ -side, -side, +side }, Math::Vector3{ 0.0f, -1.0f, 0.0f }, color },

		{ Math::Vector3{ +side, +side, -side }, Math::Vector3{ 0.0f, 1.0f, 0.0f }, color },
		{ Math::Vector3{ -side, +side, -side }, Math::Vector3{ 0.0f, 1.0f, 0.0f }, color },
		{ Math::Vector3{ +side, +side, +side }, Math::Vector3{ 0.0f, 1.0f, 0.0f }, color },

		{ Math::Vector3{ -side, +side, +side }, Math::Vector3{ 0.0f, 1.0f, 0.0f }, color },
		{ Math::Vector3{ +side, +side, +side }, Math::Vector3{ 0.0f, 1.0f, 0.0f }, color },
		{ Math::Vector3{ -side, +side, -side }, Math::Vector3{ 0.0f, 1.0f, 0.0f }, color },

	};
	std::vector<unsigned int> indices{};
	indices.reserve(vertices.size());
	for (unsigned int i = 0; i < vertices.size(); ++i)
		indices.push_back(i);

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

	EngineQ::Resources::ModelLoader loader;
	auto model = loader.LoadModel("./Models/skull.obj");

//	auto mesh = GenerateCube(0.3f);

	const auto& modelMesh = model->GetRootNode().GetChildren()[0]->GetMeshes()[0];

	auto mesh = new EngineQ::Graphics::Mesh{ modelMesh.GetVertices(), modelMesh.GetIndices() };
	auto cubeMesh = GenerateCube(0.3f);


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

	EngineQ::Graphics::ShaderProperties shaderProperties{ *shd };

	auto lightDirProp = shaderProperties.GetProperty<Math::Vector3f>("lightDir");
//	auto lightColorProp = shaderProperties.GetProperty<Math::Vector3f>("lightColor");
	auto ambientStrengthProp = shaderProperties.GetProperty<float>("ambientStrength");
	auto specularStrengthProp = shaderProperties.GetProperty<float>("specularStrength");
	auto materialShininessProp = shaderProperties.GetProperty<float>("materialShininess");

	lightDirProp = Math::Vector3f{ -1, -1, 0 };
//	lightColorProp = Math::Vector3f{ 1, 0.3f, 0.3f };
	ambientStrengthProp = 0.3f;
	specularStrengthProp = 0.4f;
	materialShininessProp = 32;

	shaderProperties.GetLights()[0].Diffuse = Math::Vector3f{ 1, 0.3f, 0.3f };
	shaderProperties.GetLights()[0].Ambient = Math::Vector3f{ 0.0f, 1.0f, 0.0f };

	shaderProperties.Apply();


	
	auto deffShdCustom = rm->GetResource<EngineQ::Graphics::Shader>(Utilities::ResourcesIDs::DeferredGeometry);
	renderable->SetModel(mesh);
	renderable->SetForwardShader(shd);
	renderable->SetDeferredShader(deffShd);
	renderable2->SetModel(mesh);
	renderable2->SetForwardShader(shd);
	renderable2->SetDeferredShader(deffShdCustom);
	renderable3->SetModel(cubeMesh);
	renderable3->SetForwardShader(shd);
	renderable3->SetDeferredShader(deffShd);

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