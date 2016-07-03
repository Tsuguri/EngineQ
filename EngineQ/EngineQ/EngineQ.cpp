#include "EngineQ.hpp"
#define GLEW_STATIC // to jest ok? czy to musi być w headerze?
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

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
		if(instance->window==nullptr)
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
}