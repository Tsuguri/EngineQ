#include "GLFWWindow.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace EngineQ
{
	GLFWWindow::keyfunc GLFWWindow::KeyFunction=nullptr;
	GLFWWindow::mousebuttonfunc GLFWWindow::MouseButtonsFunction = nullptr;
	GLFWWindow::mousecontrolfunc GLFWWindow::MouseControlFunction = nullptr;

	void GLFWWindow::KeyControl(GLFWwindow * window, int key, int scancode, int action, int mode)
	{
		if (KeyFunction != nullptr)
			KeyFunction(key, scancode, action, mode);
	}
	void GLFWWindow::MouseButtonControl(GLFWwindow * window, int button, int action, int mods)
	{
		if (MouseButtonsFunction != nullptr)
			MouseButtonsFunction(button, action, mods);
	}
	void GLFWWindow::MouseControl(GLFWwindow * window, double xpos, double ypos)
	{
		if (MouseControlFunction != nullptr)
			MouseControlFunction(xpos, ypos);
	}
	bool GLFWWindow::Initialize(std::string windowName, int width, int height)
	{


		glfwInit();

		// Set all the required options for GLFW
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

		// Creating glfw window.
		window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);//glfwGetPrimaryMonitor()

		if (window == nullptr)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return false;
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
			return false;
		}
		return true;
	}

	void GLFWWindow::Close()
	{

		glfwTerminate();
	}

	void GLFWWindow::SwapBuffers()
	{
		glfwSwapBuffers(window);
	}

	bool GLFWWindow::ShouldClose()
	{
		return glfwWindowShouldClose(window);
	}

	void GLFWWindow::PollEvents()
	{
		glfwPollEvents();
	}

	void GLFWWindow::SetKeyFunction(keyfunc function)
	{
		KeyFunction = function;
	}

	void GLFWWindow::SetMouseButtonFunction(mousebuttonfunc function)
	{
		MouseButtonsFunction = function;
	}

	void GLFWWindow::SetMouseControlFunction(mousecontrolfunc function)
	{
		MouseControlFunction = function;
	}

	double GLFWWindow::GetTime()
	{
		return glfwGetTime();
	}

	GLFWWindow::GLFWWindow()
	{
	}


	GLFWWindow::~GLFWWindow()
	{
	}
}