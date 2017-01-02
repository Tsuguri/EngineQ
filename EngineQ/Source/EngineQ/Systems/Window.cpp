#include "Window.hpp"

// Libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// This project
#include "Logger.hpp"


namespace EngineQ
{
	Window::keyfunc Window::KeyFunction=nullptr;
	Window::mousebuttonfunc Window::MouseButtonsFunction = nullptr;
	Window::mousecontrolfunc Window::MouseControlFunction = nullptr;
	Window::framebuffersizefunc Window::FramebufferResizeFunction = nullptr;

	void Window::KeyControl(GLFWwindow * window, int key, int scancode, int action, int mode)
	{
		if (KeyFunction != nullptr)
			KeyFunction(key, scancode, action, mode);
	}
	void Window::MouseButtonControl(GLFWwindow * window, int button, int action, int mods)
	{
		if (MouseButtonsFunction != nullptr)
			MouseButtonsFunction(button, action, mods);
	}
	void Window::MouseControl(GLFWwindow * window, double xpos, double ypos)
	{
		if (MouseControlFunction != nullptr)
			MouseControlFunction(xpos, ypos);
	}

	void Window::FramebufferResize(GLFWwindow* window, int width, int height)
	{
		if (FramebufferResizeFunction != nullptr)
			FramebufferResizeFunction(width, height);
	}

	bool Window::Initialize(const std::string& windowName, int width, int height)
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
			Logger::LogMessage("Failed to create GLFW window", "\n");
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
		glfwSetFramebufferSizeCallback(window, FramebufferResize);


		// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
		glewExperimental = GL_TRUE;

		// Initialize GLEW to setup the OpenGL Function pointers
		if (glewInit() != GLEW_OK)
		{
			Logger::LogMessage("Failed to initialize GLEW", "\n");
			glfwSetWindowShouldClose(window, GL_TRUE);
			window = nullptr;
			return false;
		}
		return true;
	}

	void Window::Close()
	{
		glfwTerminate();
	}

	void Window::SwapBuffers()
	{
		glfwSwapBuffers(window);
	}

	bool Window::ShouldClose()
	{
		return glfwWindowShouldClose(window) > 0 ? true : false;
	}

	void Window::PollEvents()
	{
		glfwPollEvents();
	}

	void Window::SetKeyFunction(keyfunc function)
	{
		KeyFunction = function;
	}

	void Window::SetMouseButtonFunction(mousebuttonfunc function)
	{
		MouseButtonsFunction = function;
	}

	void Window::SetMouseControlFunction(mousecontrolfunc function)
	{
		MouseControlFunction = function;
	}

	void Window::SetFramebufferResizeFunction(framebuffersizefunc function)
	{
		FramebufferResizeFunction = function;
	}

	double Window::GetTime()
	{
		return glfwGetTime();
	}

	Window::Window()
	{
	}


	Window::~Window()
	{
	}
}