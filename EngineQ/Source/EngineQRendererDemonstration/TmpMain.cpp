#include <random>

#include "EngineQCommon/Resources/Resource.hpp"
#include "EngineQCommon/Libraries/TinyXML/tinyxml2.h"

#include "EngineQRenderer/Graphics/RenderingUnit.hpp"
#include "EngineQRenderer/Graphics/Configuration/RendererConfiguration.hpp"
#include "EngineQRenderer/Graphics/Shadows/Light.hpp"

#include "EngineQRendererDefaultImplementation/Graphics/Implementation/ScreenDataProvider.hpp"
#include "EngineQRendererDefaultImplementation/Graphics/Implementation/Scene.hpp"
#include "EngineQRendererDefaultImplementation/Graphics/Implementation/Light.hpp"
#include "EngineQRendererDefaultImplementation/Graphics/Implementation/Renderable.hpp"

#include "EngineQRenderer/Graphics/Mesh.hpp"
#include "EngineQRenderer/Graphics/Vertex.hpp"
//#include "EngineQRenderer/Graphics/ShaderProperties.hpp"
//#include "EngineQRenderer/Graphics/Texture.hpp"


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
	throw std::runtime_error{ "Not implemented" };

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

std::unique_ptr<EngineQ::Graphics::Texture> GenerateNoiseTexture(int width, int height)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(-1.0f, 1.0f);


	int size = width * height;
	std::vector<EngineQ::Math::Vector3f> vectors(size);

	for (auto& vec : vectors)
		vec = EngineQ::Math::Vector3f(dist(mt), dist(mt), 0.0f).GetNormalized();

	return std::make_unique<EngineQ::Graphics::Texture>(width, height, &(vectors.data()->X));
}

EngineQ::Graphics::Configuration::RenderingUnitConfiguration CreateRenderingUnitConfiguration()
{
	return EngineQ::Graphics::Configuration::RenderingUnitConfiguration{};
}

EngineQ::Graphics::Implementation::Scene CreateScene(EngineQ::Graphics::Implementation::ScreenDataProvider* screenDataProvider)
{
	auto scene = EngineQ::Graphics::Implementation::Scene{};

	auto light = new EngineQ::Graphics::Implementation::Light();
	light->Init(screenDataProvider);
	light->SetPosition(Math::Vector3{ 5,5,5 });
	light->SetLightType(EngineQ::Graphics::Shadows::Light::Type::Directional);
	light->SetDirection(Math::Vector3{ -5,-4,-4 });
	scene.lights.push_back(light);

	auto meshResource = EngineQ::Resources::Resource<EngineQ::Graphics::Mesh>(GenerateCube());
	auto renderable = EngineQ::Graphics::Implementation::Renderable{};
	renderable.SetMesh(meshResource);

	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
		{
			renderable.SetPosition(EngineQ::Math::Vector3{ i,0,j });
		}

	return scene;
}

void FreeResources(EngineQ::Graphics::Implementation::Scene& scene)
{
	for (int i = 0; i < scene.lights.size(); i++)
	{
		delete scene.lights[i];
	}
	scene.lights.clear();
}

int main(int argc, char** argv)
{
	auto configuration = CreateRenderingUnitConfiguration();

	auto screenDataProvider = std::make_shared<EngineQ::Graphics::Implementation::ScreenDataProvider>();
	screenDataProvider->SetScreenSize(EngineQ::Math::Vector2i{ 1920,1080 });

	auto renderingUnit = std::make_unique<EngineQ::Graphics::RenderingUnit>(screenDataProvider.get(), configuration);

	auto scene = CreateScene(screenDataProvider.get());


	renderingUnit->Render(scene);

	return 0;
}