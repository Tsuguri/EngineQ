#include "Window.hpp"

// Libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// This project
#include "Logger.hpp"


namespace EngineQ
{
	std::map<GLFWwindow*, Window*> Window::windowsMap;

	void Window::KeyControl(GLFWwindow* glfwWindow, int key, int scancode, int action, int mode)
	{
		auto window = windowsMap.at(glfwWindow);

		if (window->KeyFunction != nullptr)
			window->KeyFunction(key, scancode, action, mode);
	}
	void Window::MouseButtonControl(GLFWwindow* glfwWindow, int button, int action, int mods)
	{
		auto window = windowsMap.at(glfwWindow);

		if (window->MouseButtonFunction != nullptr)
			window->MouseButtonFunction(button, action, mods);
	}
	void Window::MousePositionControl(GLFWwindow* glfwWindow, double xpos, double ypos)
	{
		auto window = windowsMap.at(glfwWindow);

		if (window->MousePositionFunction != nullptr)
			window->MousePositionFunction(xpos, ypos);
	}

	void Window::ResizeControl(GLFWwindow* glfwWindow, int width, int height)
	{
		auto window = windowsMap.at(glfwWindow);
		window->screenSize = Math::Vector2i(width, height);

		if (window->ResizeFunction != nullptr)
			window->ResizeFunction(width, height);

		if (!window->ResizeEventIsEmpty())
			window->ResizeEventInvoke(window->screenSize);
	}

	void Window::MakeCurrent()
	{
		glfwMakeContextCurrent(window);
	}

	void Window::Close()
	{
		glfwDestroyWindow(this->window);
	}
	
	bool Window::ShouldClose()
	{
		return glfwWindowShouldClose(window) > 0;
	}

	void Window::RequestClose()
	{
		glfwSetWindowShouldClose(this->window, GL_TRUE);
	}

	Math::Vector2i Window::GetScreenSize() const
	{
		return this->screenSize;
	}

	void Window::SetKeyFunction(KeyEventHandler function)
	{
		KeyFunction = function;
	}

	void Window::SetMouseButtonFunction(MouseButtonEventHandler function)
	{
		MouseButtonFunction = function;
	}

	void Window::SetMousePositionFunction(MousePositionEventHandler function)
	{
		MousePositionFunction = function;
	}

	void Window::SetResizeFunction(ResizeEventHandler function)
	{
		ResizeFunction = function;
	}

	Window::Window(const std::string& windowName, int width, int height)
	{
		// Set all the required options for GLFW
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

		// Creating glfw window.
		window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);//glfwGetPrimaryMonitor()
	
		this->screenSize = Math::Vector2i(width, height);

		if (window == nullptr)
			throw std::runtime_error{ "Failed to create window" };

		glfwMakeContextCurrent(window);

		//Change here to manipulate vsync
		//glfwSwapInterval(0);

		windowsMap.insert(std::make_pair(window, this));
	
		// Set the required callback functions
		glfwSetKeyCallback(window, KeyControl);
		glfwSetCursorPosCallback(window, MousePositionControl);
		glfwSetMouseButtonCallback(window, MouseButtonControl);
		//Uncomment below if want to register call on window resizing
		glfwSetFramebufferSizeCallback(window, ResizeControl);


		// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
		glewExperimental = GL_TRUE;

		// Initialize GLEW to setup the OpenGL Function pointers
		if (glewInit() != GLEW_OK)
			throw std::runtime_error{ "Failed to initialize GLEW" };
	}

	Window::~Window()
	{
		this->Close();
	}

	void Window::EngineCallbacks::SwapBuffers(Window& window)
	{
		glfwSwapBuffers(window.window);
	}

	void Window::EngineCallbacks::PollEvents()
	{
		glfwPollEvents();
	}

	void Window::EngineCallbacks::Initialize()
	{
		if (glfwInit() != GL_TRUE)
			throw std::runtime_error{ "Failed to initialize GLFW" };
	}

	void Window::EngineCallbacks::Finalize()
	{
		glfwTerminate();
	}
}