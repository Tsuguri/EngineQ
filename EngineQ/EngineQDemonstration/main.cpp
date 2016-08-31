#include "Engine.hpp"
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


void PrepareScene(EngineQ::Scene* scene)
{
	auto& sc{ *scene };

	::EngineQ::Graphics::Shader* tempShader = new ::EngineQ::Graphics::Shader{ {"Shaders/BasicVertex.vsh"}, {"Shaders/BasicFragment.fsh"} };

	auto mesh = GenerateCube(0.2f);

	auto ent = sc.CreateEntity();
	auto ent2 = sc.CreateEntity();
	auto renderable = ent2->AddComponent<EngineQ::Graphics::Renderable>();

	auto cam = ent->AddComponent<EngineQ::Camera>();
	renderable->SetModel(mesh);
	renderable->SetForwardShader(tempShader);
	ent->GetTransform().SetPosition(EngineQ::Math::Vector3(0, 0, -2.0f));

	EngineQ::Scripting::ScriptClass scriptClass = EngineQ::Engine::Get()->GetClass("QScripts", "QScripts", "CameraMoveClass");

	ent->AddScript(scriptClass);
	EngineQ::Scripting::ScriptClass scriptClass2 = EngineQ::Engine::Get()->GetClass("QScripts", "QScripts", "RotateTest");
	ent2->AddScript(scriptClass2);


	sc.ActiveCamera(cam);
}

#include "Utilities\Property.hpp"
#include "ResourceManager.hpp"

class PropTest
{
	Math::Vector3 field{ 1, 2, 3 };

	Math::Vector3 GetField()
	{
		return this->field;
	}

	void SetField(const Math::Vector3& field)
	{
		this->field = field;
	}

	static Math::Vector3 GetField2()
	{
		return Math::Vector3{ 153, 226, 389 };
	}

public:
	PropTest()
	{

	}

	EngineQ::Property<Math::Vector3, decltype(&GetField), &GetField, decltype(&SetField), &SetField> Field = this;

	static EngineQ::Property<Math::Vector3, decltype(&GetField2), &GetField2> Field2;
};
EngineQ::Property<Math::Vector3, decltype(&PropTest::GetField2), &PropTest::GetField2> PropTest::Field2;

int main(int argc, char** argv)
{
	PropTest test;
	Math::Vector3 temporary = test.Field;
	//	int x = test.Field().X;
	//	int y = test.Field().Y;
	//	int z = test.Field().Z;
	//	std::cout << x << " " << y << " " << z << std::endl;
	//	std::cout << test.Field().ToString() << std::endl;


	Math::Vector2 testVal1{ 1.0f, 2.0f };
	Math::Vector2 testVal2;
	Math::Vector2 testVal3;

	std::stringstream sstream;
	sstream <<= testVal1;
	sstream >>= testVal2;
	sstream << testVal1;
	sstream >> testVal3;

	std::cout << testVal1 << std::endl;
	std::cout << testVal2 << std::endl;
	std::cout << testVal3 << std::endl;

	Math::Vector3 tmpVec = PropTest::Field2;
	std::cout << "Temp vec: " << tmpVec.ToString() << std::endl;

	EngineQ::Engine::Initialize("Turbo giera", 800, 600, argv[0]);


	// Resource manager test
	EngineQ::ResourceManager rm;
	rm.AddResource<EngineQ::Graphics::Shader>(0, "./TMP/Shader.shader");

	{
		auto res = rm.GetResource<EngineQ::Graphics::Shader>(0);
	}

	for (int i = 0; i < 5; ++i)
		rm.Update();

	{
		auto res = rm.GetResource<EngineQ::Graphics::Shader>(0);
	}

	for (int i = 0; i < 15; ++i)
		rm.Update();

	{
		auto res = rm.GetResource<EngineQ::Graphics::Shader>(0);
	}


	auto sc = EngineQ::Engine::Get()->CreateScene();
	PrepareScene(sc);

	EngineQ::Engine::Get()->Run(sc);

	return 0;
}