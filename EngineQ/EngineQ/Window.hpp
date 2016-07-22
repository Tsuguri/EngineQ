#ifndef ENGINEQ_GLFWWINDOW_HPP
#define ENGINEQ_GLFWWINDOW_HPP
#include <string>

struct GLFWwindow;
namespace EngineQ
{
	class Window
	{
	public:
		typedef void(*keyfunc)(int, int, int, int);
		typedef void(*mousebuttonfunc)(int, int, int);
		typedef void(*mousecontrolfunc)(double, double);

	private:
		GLFWwindow* window;
		static keyfunc KeyFunction;
		static mousebuttonfunc MouseButtonsFunction;
		static mousecontrolfunc MouseControlFunction;

		static void KeyControl(GLFWwindow* window, int key, int scancode, int action, int mode);
		static void MouseButtonControl(GLFWwindow* window, int button, int action, int mods);
		static void MouseControl(GLFWwindow* window, double xpos, double ypos);
	public:
		Window();
		~Window();
		bool Initialize(std::string windowName, int width, int height);
		void Close();
		void SwapBuffers();
		bool ShouldClose();
		void PollEvents();
		void SetKeyFunction(keyfunc function);
		void SetMouseButtonFunction(mousebuttonfunc function);
		void SetMouseControlFunction(mousecontrolfunc function);
		double GetTime();

	};
}
#endif