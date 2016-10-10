#ifndef ENGINEQ_ENGINEQ_HPP
#define ENGINEQ_ENGINEQ_HPP

#include <string>
#include <memory>

#include "Window.hpp"
#include "Scripting/ScriptEngine.hpp"
#include "Objects/Scene.hpp"
#include "InputController.hpp"
#include "ResourceManager.hpp"
#include "Utilities/Event.hpp"

#include "Math\Vector2.hpp"

namespace EngineQ
{

	namespace Graphics
	{
		class RenderingUnit;
	}
	class Engine
	{
#pragma region Fields

	private:
		std::unique_ptr<Scripting::ScriptEngine> scriptingEngine;
		std::unique_ptr<ResourceManager> resourceManager;
		std::shared_ptr<Graphics::RenderingUnit> renderingUnit;
		static Engine* instance;
		Window window;
		bool running = true;
		Math::Vector2i screenSize;
		
	public:
		Utilities::Event<Engine, void(int, int)> resizeEvent;
		InputController input;

#pragma endregion 

#pragma region Methods

	private:

		Engine(std::string name, int width, int height);

		void WindowResized(int width, int height);

		static void KeyControl(int key, int scancode, int action, int mode);
		static void MouseButtonControl(int button, int action, int mode);
		static void MouseControl(double xpos, double ypos);
		static void FramebufferResize(int width, int height);
	public:
		static bool Initialize(std::string name, int width, int height, char* assemblyName);

		static Engine* Get();
		ResourceManager* GetResourceManager() const;
		Scripting::ScriptClass GetClass(std::string assembly, std::string namespaceName, std::string className) const;
		Math::Vector2i GetScreenSize() const;

		void SetPostprocessingConfiguration(std::string filePath);

		Scene* CreateScene() const;
		void Exit();
		void Run(Scene* scene);


#pragma endregion 


	};

}

#endif