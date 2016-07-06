#ifndef GLFWWINDOWHPP
#define GLFWWINDOWHPP
#include <string>

struct GLFWwindow;
namespace EngineQ
{
	class GLFWWindow
	{
	private:
		GLFWwindow* window;

		static void KeyControl(GLFWwindow* window, int key, int scancode, int action, int mode);
		static void MouseButtonControl(GLFWwindow* window, int button, int action, int mods);
		static void MouseControl(GLFWwindow* window, double xpos, double ypos);
	public:
		GLFWWindow();
		~GLFWWindow();
		bool Initialize(std::string windowName, int width, int height);
		void Close();
		void SwapBuffers();
		bool ShouldClose();
		void PollEvents();

	};
}
#endif