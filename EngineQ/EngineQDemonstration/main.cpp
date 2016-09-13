#include "Engine.hpp"

#include "Utilities/ResourcesIDs.hpp"

namespace Math = EngineQ::Math;

EngineQ::Mesh* GenerateCube(float side = 1.0f)
{
	std::vector<EngineQ::VertexPNC> vertices{
		{Math::Vector3{ side, -side, -side }, Math::Vector3{ 0.0f,  0.0f, -1.0f } },
		{Math::Vector3{ side,  side, -side }, Math::Vector3{ 0.0f,  0.0f, -1.0f } },
		{Math::Vector3{ -side, -side, -side }, Math::Vector3{ 0.0f,  0.0f, -1.0f } },

		{Math::Vector3{ -side,  side, -side }, Math::Vector3{ 0.0f,  0.0f, -1.0f } },
		{ Math::Vector3{ -side, -side, -side }, Math::Vector3{ 0.0f,  0.0f, -1.0f } },
		{ Math::Vector3{ side,  side, -side }, Math::Vector3{ 0.0f,  0.0f, -1.0f } },

		{ Math::Vector3{ side,  side,  side }, Math::Vector3{ 0.0f,  0.0f,  1.0f } },
		{ Math::Vector3{ side, -side,  side }, Math::Vector3{ 0.0f,  0.0f,  1.0f } },
		{ Math::Vector3{ -side, -side,  side }, Math::Vector3{ 0.0f,  0.0f,  1.0f } },

		{ Math::Vector3{ side,  side,  side }, Math::Vector3{ 0.0f,  0.0f,  1.0f } },
		{ Math::Vector3{ -side, -side,  side }, Math::Vector3{ 0.0f,  0.0f,  1.0f } },
		{ Math::Vector3{ -side,  side,  side }, Math::Vector3{ 0.0f,  0.0f,  1.0f } },

		{ Math::Vector3{ -side,  side,  side }, Math::Vector3{ -1.0f,  0.0f,  0.0f } },
		{ Math::Vector3{ -side, -side, -side }, Math::Vector3{ -1.0f,  0.0f,  0.0f } },
		{ Math::Vector3{ -side,  side, -side }, Math::Vector3{ -1.0f,  0.0f,  0.0f } },

		{ Math::Vector3{ -side, -side, -side }, Math::Vector3{ -1.0f,  0.0f,  0.0f } },
		{ Math::Vector3{ -side,  side,  side }, Math::Vector3{ -1.0f,  0.0f,  0.0f } },
		{ Math::Vector3{ -side, -side,  side }, Math::Vector3{ -1.0f,  0.0f,  0.0f } },

		{ Math::Vector3{ side,  side, -side }, Math::Vector3{ 1.0f,  0.0f,  0.0f } },
		{ Math::Vector3{ side, -side, -side }, Math::Vector3{ 1.0f,  0.0f,  0.0f } },
		{ Math::Vector3{ side,  side,  side }, Math::Vector3{ 1.0f,  0.0f,  0.0f } },

		{ Math::Vector3{ side, -side,  side }, Math::Vector3{ 1.0f,  0.0f,  0.0f } },
		{ Math::Vector3{ side,  side,  side }, Math::Vector3{ 1.0f,  0.0f,  0.0f } },
		{ Math::Vector3{ side, -side, -side }, Math::Vector3{ 1.0f,  0.0f,  0.0f } },

		{ Math::Vector3{ side, -side,  side }, Math::Vector3{ 0.0f, -1.0f,  0.0f } },
		{ Math::Vector3{ side, -side, -side }, Math::Vector3{ 0.0f, -1.0f,  0.0f } },
		{ Math::Vector3{ -side, -side, -side }, Math::Vector3{ 0.0f, -1.0f,  0.0f } },

		{ Math::Vector3{ -side, -side, -side }, Math::Vector3{ 0.0f, -1.0f,  0.0f } },
		{ Math::Vector3{ -side, -side,  side }, Math::Vector3{ 0.0f, -1.0f,  0.0f } },
		{ Math::Vector3{ side, -side,  side }, Math::Vector3{ 0.0f, -1.0f,  0.0f } },

		{ Math::Vector3{ side,  side, -side }, Math::Vector3{ 0.0f,  1.0f,  0.0f } },
		{ Math::Vector3{ side,  side,  side }, Math::Vector3{ 0.0f,  1.0f,  0.0f } },
		{ Math::Vector3{ -side,  side, -side }, Math::Vector3{ 0.0f,  1.0f,  0.0f } },

		{ Math::Vector3{ -side,  side,  side }, Math::Vector3{ 0.0f,  1.0f,  0.0f } },
		{ Math::Vector3{ -side,  side, -side }, Math::Vector3{ 0.0f,  1.0f,  0.0f } },
		{ Math::Vector3{ side,  side,  side }, Math::Vector3{ 0.0f,  1.0f,  0.0f } },

	};
	std::vector<unsigned int> indices{};
	indices.reserve(vertices.size());
	for (unsigned int i = 0; i < vertices.size(); ++i)
		indices.push_back(i);

	return new EngineQ::Mesh{ vertices, indices };
}

EngineQ::Mesh* GenerateSphere(float radius = 1.0f, float verticalStep = 10.0f, float horizontalStep = 10.0f)
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

	return new EngineQ::Mesh{ vertices,indices };
}
void PrepareScene(EngineQ::Scene* scene)
{
	auto& sc{ *scene };


	auto mesh = GenerateCube(0.3f);

	auto ent = sc.CreateEntity();
	auto ent2 = sc.CreateEntity();
	auto ent3 = sc.CreateEntity();

	auto renderable = ent2->AddComponent<EngineQ::Graphics::Renderable>();
	auto renderable2 = ent3->AddComponent<EngineQ::Graphics::Renderable>();

	auto cam = ent->AddComponent<EngineQ::Camera>();
	auto rm = EngineQ::Engine::Get()->GetResourceManager();
	auto shd = rm->GetResource<EngineQ::Graphics::Shader>(EngineQ::Utilities::ResourcesIDs::BasicShader);
	auto deffShd = rm->GetResource<EngineQ::Graphics::Shader>(EngineQ::Utilities::ResourcesIDs::DeferredGeometry);
	auto deffShdCustom = rm->GetResource<EngineQ::Graphics::Shader>(EngineQ::Utilities::ResourcesIDs::CustomDeferred);
	renderable->SetModel(mesh);
	renderable->SetForwardShader(shd);
	renderable->SetDeferredShader(deffShd);
	renderable2->SetModel(mesh);
	renderable2->SetForwardShader(shd);
	renderable2->SetDeferredShader(deffShdCustom);

	ent3->GetTransform().SetPosition(EngineQ::Math::Vector3(1.0f,0,0));
	ent->GetTransform().SetPosition(EngineQ::Math::Vector3(0, 0, -2.0f));

	EngineQ::Scripting::ScriptClass scriptClass = EngineQ::Engine::Get()->GetClass("QScripts", "QScripts", "CameraMoveClass");

	ent->AddScript(scriptClass);
	EngineQ::Scripting::ScriptClass scriptClass2 = EngineQ::Engine::Get()->GetClass("QScripts", "QScripts", "RotateTest");
	ent2->AddScript(scriptClass2);


	sc.ActiveCamera(cam);
}

void TemporaryResources(EngineQ::Engine* engine)
{
	auto rm = EngineQ::Engine::Get()->GetResourceManager();
	rm->AddResource<EngineQ::Graphics::Shader>(EngineQ::Utilities::ResourcesIDs::BasicShader, "./Shaders/Basic.shd");
	rm->AddResource<EngineQ::Graphics::Shader>(EngineQ::Utilities::ResourcesIDs::CustomShader, "./Shaders/Custom.shd");
	rm->AddResource<EngineQ::Graphics::Shader>(EngineQ::Utilities::ResourcesIDs::QuadShader, "./Shaders/Quad.shd");
	rm->AddResource<EngineQ::Graphics::Shader>(EngineQ::Utilities::ResourcesIDs::BlurShader, "./Shaders/Bloom/Blur.shd");
	rm->AddResource<EngineQ::Graphics::Shader>(EngineQ::Utilities::ResourcesIDs::BlurVShader, "./Shaders/Bloom/BlurV.shd");
	rm->AddResource<EngineQ::Graphics::Shader>(EngineQ::Utilities::ResourcesIDs::BrightExtract, "./Shaders/Bloom/BrightExtract.shd");
	rm->AddResource<EngineQ::Graphics::Shader>(EngineQ::Utilities::ResourcesIDs::CombineShader, "./Shaders/Bloom/Combine.shd");
	rm->AddResource<EngineQ::Graphics::Shader>(EngineQ::Utilities::ResourcesIDs::DeferredLightning, "./Shaders/Deferred/DeferredLightning.shd");
	rm->AddResource<EngineQ::Graphics::Shader>(EngineQ::Utilities::ResourcesIDs::DeferredGeometry, "./Shaders/Deferred/DeferredGeometry.shd");
	rm->AddResource<EngineQ::Graphics::Shader>(EngineQ::Utilities::ResourcesIDs::CustomDeferred, "./Shaders/Deferred/DeferredCustom.shd");
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