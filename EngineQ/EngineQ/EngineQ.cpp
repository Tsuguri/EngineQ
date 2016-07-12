#include "EngineQ.hpp"

#include <iostream>
#include <fstream>
#include <memory>


#include "Math/Vector3.hpp"

#include "Mesh.hpp"
#include "Scene.hpp"
#include "Graphics/Shader.hpp"
#include "ForwardRenderer.hpp"

namespace EngineQ
{

	EngineQ* EngineQ::instance = nullptr;

	EngineQ::EngineQ(std::string name, int width, int height)
	{

		std::cout << "Creating  EngineQ" << std::endl;
		if (!window.Initialize(name, width, height))
		{
			std::cout << "Unable to initialize glfw window" << std::endl;
			throw std::logic_error("Unable to start glfw window");
		}

		window.SetKeyFunction(KeyControl);
		window.SetMouseButtonFunction(MouseButtonControl);
		window.SetMouseControlFunction(MouseControl);

		// Define the viewport dimensions
		glViewport(0, 0, width, height);
	}

	void EngineQ::KeyControl(int key, int scancode, int action, int mode)
	{

	}

	void EngineQ::MouseButtonControl(int button, int action, int mods)
	{

	}

	void EngineQ::MouseControl(double xpos, double ypos)
	{

	}

	bool EngineQ::Initialize(std::string name, int width, int height)
	{
		if (instance != nullptr)
		{
			std::cout << "EngineQ is already initialized" << std::endl;
			return false;
		}
		std::cout << "Initializing EngineQ" << std::endl;

		instance = new EngineQ{ name, width, height };

		return true;
	}

	EngineQ* EngineQ::Get()
	{
		if (instance != nullptr)
			return instance;
		else
		{
			std::cout << "EngineQ is not initialized" << std::endl;
			return nullptr;
		}
	}

	std::unique_ptr<Mesh> GenerateCube(float side = 1.0f)
	{
		std::vector<VertexPNC> vertices{
			{ Math::Vector3{ side, -side, -side }, Math::Vector3{ 0.0f,  0.0f, -1.0f } },
			{ Math::Vector3{ side,  side, -side }, Math::Vector3{ 0.0f,  0.0f, -1.0f } },
			{ Math::Vector3{ -side, -side, -side }, Math::Vector3{ 0.0f,  0.0f, -1.0f } },

			{ Math::Vector3{ -side,  side, -side }, Math::Vector3{ 0.0f,  0.0f, -1.0f } },
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
		std::vector<GLuint> indices{};
		indices.reserve(vertices.size());
		for (GLuint i = 0; i < vertices.size(); ++i)
			indices.push_back(i);

		return std::make_unique<Mesh>(vertices, indices);
	}


	void EngineQ::Run(const char* name)
	{
		// main engine loop
		std::string monoPath = "./";
		std::string engineAssemblyPath = "./";
		std::string scriptsAssembliesPath = "./Scripts/";

		Scripting::ScriptEngine se{ name, (engineAssemblyPath + "EngineQ.dll").c_str(), (monoPath + "libraries").c_str(), (monoPath + "config").c_str() };
		Graphics::ForwardRenderer renderer;
		::EngineQ::Graphics::Shader tempShader{ "Shaders/BasicVertex.vsh","Shaders/BasicFragment.fsh" };

		Math::Vector3(0, 0, 0);
		auto mesh = GenerateCube(0.2f);

		Scene sc{ se };
		auto ent = sc.CreateEntity();
		auto ent2 = sc.CreateEntity();
		auto renderable = ent2->AddComponent<Graphics::Renderable>();

		auto cam = ent->AddComponent<Camera>();
		renderable->Model(mesh.get());
		renderable->ForwardShader(&tempShader);
		ent->GetTransform().SetPosition(Math::Vector3(0, 0, -2.0f));

		sc.ActiveCamera(cam);
		while (!window.ShouldClose())
		{
			//input
			window.PollEvents();

			//check input and stuff

			//scripts & logic
			auto p = ent2->GetTransform().GetPosition();
			p.X = 0.3f*std::sin(window.GetTime());
			ent2->GetTransform().SetPosition(p);
			renderer.Render(&sc);

			window.SwapBuffers();
		}
		window.Close();
	}
}
