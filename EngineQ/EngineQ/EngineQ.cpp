#include "EngineQ.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include "Shader.hpp"
#include "Math/Vector3.hpp"
#include "Mesh.hpp"
#include <memory>
#include <Windows.h>
namespace EngineQ
{

	EngineQ* EngineQ::instance = nullptr;

	EngineQ::EngineQ(std::string name, int width, int height)
	{

		std::cout << "Creating  EngineQ" << std::endl;


		glfwInit();

		// Set all the required options for GLFW
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

		// Creating glfw window.
		window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);//glfwGetPrimaryMonitor()

		if (window == nullptr)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(window);

		//Change here to manipulate vsync
		//glfwSwapInterval(0);

		// Set the required callback functions
		glfwSetKeyCallback(window, KeyControl);
		glfwSetCursorPosCallback(window, MouseControl);
		glfwSetMouseButtonCallback(window, MouseButtonControl);

		//Uncomment below if want to register call on window resizing
		//glfwSetFramebufferSizeCallback(window, WindowResized);


		// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
		glewExperimental = GL_TRUE;

		// Initialize GLEW to setup the OpenGL Function pointers
		if (glewInit() != GLEW_OK)
		{
			std::cout << "Failed to initialize GLEW" << std::endl;
			glfwSetWindowShouldClose(window, GL_TRUE);
			window = nullptr;
			return;
		}

		// Define the viewport dimensions
		glViewport(0, 0, width, height);
	}

	void EngineQ::KeyControl(GLFWwindow* window, int key, int scancode, int action, int mode)
	{

	}

	void EngineQ::MouseButtonControl(GLFWwindow* window, int button, int action, int mods)
	{

	}

	void EngineQ::MouseControl(GLFWwindow* window, double xpos, double ypos)
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
		if (instance->window == nullptr)
		{
			std::cout << "Initializing failed" << std::endl;
			return false;
		}
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
			{ Math::Vector3{ -side, -side, -side }, Math::Vector3{ 0.0f,  0.0f, -1.0f } },
			{ Math::Vector3{ side,  side, -side }, Math::Vector3{ 0.0f,  0.0f, -1.0f } },
			{ Math::Vector3{ side, -side, -side }, Math::Vector3{ 0.0f,  0.0f, -1.0f } },
			{ Math::Vector3{ side,  side, -side }, Math::Vector3{ 0.0f,  0.0f, -1.0f } },
			{ Math::Vector3{ -side, -side, -side }, Math::Vector3{ 0.0f,  0.0f, -1.0f } },
			{ Math::Vector3{ -side,  side, -side }, Math::Vector3{ 0.0f,  0.0f, -1.0f } },
			{ Math::Vector3{ -side, -side,  side }, Math::Vector3{ 0.0f,  0.0f,  1.0f } },
			{ Math::Vector3{ side, -side,  side }, Math::Vector3{ 0.0f,  0.0f,  1.0f } },
			{ Math::Vector3{ side,  side,  side }, Math::Vector3{ 0.0f,  0.0f,  1.0f } },
			{ Math::Vector3{ -side,  side,  side }, Math::Vector3{ 0.0f,  0.0f,  1.0f } },
			{ Math::Vector3{ -side, -side,  side }, Math::Vector3{ 0.0f,  0.0f,  1.0f } },
			{ Math::Vector3{ side,  side,  side }, Math::Vector3{ 0.0f,  0.0f,  1.0f } },
			{ Math::Vector3{ -side,  side, -side }, Math::Vector3{ -1.0f,  0.0f,  0.0f } },
			{ Math::Vector3{ -side, -side, -side }, Math::Vector3{ -1.0f,  0.0f,  0.0f } },
			{ Math::Vector3{ -side,  side,  side }, Math::Vector3{ -1.0f,  0.0f,  0.0f } },
			{ Math::Vector3{ -side, -side,  side }, Math::Vector3{ -1.0f,  0.0f,  0.0f } },
			{ Math::Vector3{ -side,  side,  side }, Math::Vector3{ -1.0f,  0.0f,  0.0f } },
			{ Math::Vector3{ -side, -side, -side }, Math::Vector3{ -1.0f,  0.0f,  0.0f } },
			{ Math::Vector3{ side,  side,  side }, Math::Vector3{ 1.0f,  0.0f,  0.0f } },
			{ Math::Vector3{ side, -side, -side }, Math::Vector3{ 1.0f,  0.0f,  0.0f } },
			{ Math::Vector3{ side,  side, -side }, Math::Vector3{ 1.0f,  0.0f,  0.0f } },
			{ Math::Vector3{ side, -side, -side }, Math::Vector3{ 1.0f,  0.0f,  0.0f } },
			{ Math::Vector3{ side,  side,  side }, Math::Vector3{ 1.0f,  0.0f,  0.0f } },
			{ Math::Vector3{ side, -side,  side }, Math::Vector3{ 1.0f,  0.0f,  0.0f } },
			{ Math::Vector3{ -side, -side, -side }, Math::Vector3{ 0.0f, -1.0f,  0.0f } },
			{ Math::Vector3{ side, -side, -side }, Math::Vector3{ 0.0f, -1.0f,  0.0f } },
			{ Math::Vector3{ side, -side,  side }, Math::Vector3{ 0.0f, -1.0f,  0.0f } },
			{ Math::Vector3{ side, -side,  side }, Math::Vector3{ 0.0f, -1.0f,  0.0f } },
			{ Math::Vector3{ -side, -side,  side }, Math::Vector3{ 0.0f, -1.0f,  0.0f } },
			{ Math::Vector3{ -side, -side, -side }, Math::Vector3{ 0.0f, -1.0f,  0.0f } },
			{ Math::Vector3{ -side,  side, -side }, Math::Vector3{ 0.0f,  1.0f,  0.0f } },
			{ Math::Vector3{ side,  side,  side }, Math::Vector3{ 0.0f,  1.0f,  0.0f } },
			{ Math::Vector3{ side,  side, -side }, Math::Vector3{ 0.0f,  1.0f,  0.0f } },
			{ Math::Vector3{ side,  side,  side }, Math::Vector3{ 0.0f,  1.0f,  0.0f } },
			{ Math::Vector3{ -side,  side, -side }, Math::Vector3{ 0.0f,  1.0f,  0.0f } },
			{ Math::Vector3{ -side,  side,  side }, Math::Vector3{ 0.0f,  1.0f,  0.0f } },

		};
		std::vector<GLuint> indices{};
		for (GLuint i = 0; i < vertices.size(); i++)
			indices.push_back(i);

		return std::make_unique<Mesh>(vertices, indices);
	}


	void EngineQ::Run() const
	{
		// main engine loop

		Shader tempShader{ "Shaders/BasicVertex.vsh","Shaders/BasicFragment.fsh" };

		Math::Vector3(0, 0, 0);
		auto mesh = GenerateCube(0.2f);

		//glEnable(GL_DEPTH_TEST);
		glFrontFace(GL_CCW);
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_FILL);
		//glCullFace(GL_BACK);
		//glEnable(GL_CULL_FACE);



		while (!glfwWindowShouldClose(window))
		{
			//input
			glfwPollEvents();



			//check input and stuff


			//scripts & logic




			//render
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			tempShader.SetAsActive();




			glBindVertexArray(mesh->vao);
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->vbo[2]);
			glDrawElements(GL_TRIANGLES, mesh->Count(), GL_UNSIGNED_INT, NULL);

			//swapiping buffers
			glfwSwapBuffers(window);
		}

		glfwTerminate();
	}
}
