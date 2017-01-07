#ifndef ENGINEQ_GLFWWINDOW_HPP
#define ENGINEQ_GLFWWINDOW_HPP

// Standard includes
#include <string>
#include <map>

// Other projects
#include "EngineQCommon/Math/Vector2.hpp"
#include "EngineQCommon/Utilities/Immovable.hpp"
#include "EngineQRenderer/Graphics/Utils/ScreenDataProvider.hpp"


struct GLFWwindow;

namespace EngineQ
{
	class Window : public Utilities::Immovable, public Graphics::ScreenDataProvider
	{
	public:
		class EngineCallbacks
		{
			friend class Engine;

		public:
			static void SwapBuffers(Window& window);
			static void PollEvents();
			static void Initialize();
			static void Finalize();
		};

	public:
		typedef void(*KeyEventHandler)(int, int, int, int);
		typedef void(*MouseButtonEventHandler)(int, int, int);
		typedef void(*MousePositionEventHandler)(double, double);
		typedef void(*ResizeEventHandler)(int, int);

	private:
		GLFWwindow* window;
		Math::Vector2i screenSize;

		KeyEventHandler KeyFunction = nullptr;
		MouseButtonEventHandler MouseButtonFunction = nullptr;
		MousePositionEventHandler MousePositionFunction = nullptr;
		ResizeEventHandler ResizeFunction = nullptr;

		static std::map<GLFWwindow*, Window*> windowsMap;

		static void KeyControl(GLFWwindow* glfwWindow, int key, int scancode, int action, int mode);
		static void MouseButtonControl(GLFWwindow* glfwWindow, int button, int action, int mods);
		static void MousePositionControl(GLFWwindow* glfwWindow, double xpos, double ypos);
		static void ResizeControl(GLFWwindow* glfwWindow, int width, int height);

		void Close();

	public:
		Window(const std::string& windowName, int width, int height);
		~Window();

		void MakeCurrent();
		bool ShouldClose();
		void RequestClose();
		virtual Math::Vector2i GetScreenSize() const override;

		void SetKeyFunction(KeyEventHandler function);
		void SetMouseButtonFunction(MouseButtonEventHandler function);
		void SetMousePositionFunction(MousePositionEventHandler function);
		void SetResizeFunction(ResizeEventHandler function);
	};
}
#endif