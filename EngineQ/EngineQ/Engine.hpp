#ifndef ENGINEQ_ENGINEQ_HPP
#define ENGINEQ_ENGINEQ_HPP

#include <string>
#include <memory>

#include "Graphics/Types.hpp"

#include "Window.hpp"
#include "Scripting/ScriptEngine.hpp"
#include "Objects/Scene.hpp"
#include "InputController.hpp"
#include "Resources/ResourceManager.hpp"
#include "Utilities/Event.hpp"

#include "Math/Vector2.hpp"

namespace EngineQ
{
	class Engine : private Utilities::Immovable
	{
#pragma region Fields

	private:
		static std::unique_ptr<Engine> instance;

		Window window;
		bool isRunning = true;
		Math::Vector2i screenSize;
		
	public:
		Utilities::Event<Engine, void(int, int)> resizeEvent;
		InputController input;

	private:
		std::unique_ptr<Scripting::ScriptEngine> scriptingEngine;
		std::unique_ptr<Resources::ResourceManager> resourceManager;
		std::shared_ptr<Graphics::RenderingUnit> renderingUnit;
		
		std::vector<std::unique_ptr<Scene>> scenes;
		Scene* currentScene = nullptr;

#pragma endregion 

#pragma region Methods

	private:

		Engine(std::string name, int width, int height, const char* assemblyName);

		void WindowResized(int width, int height);

		static void KeyControl(int key, int scancode, int action, int mode);
		static void MouseButtonControl(int button, int action, int mode);
		static void MouseControl(double xpos, double ypos);
		static void FramebufferResize(int width, int height);
	public:
		static bool Initialize(std::string name, int width, int height, char* assemblyName);

		static Engine& Get();
		Resources::ResourceManager& GetResourceManager() const;
		Scripting::ScriptEngine& GetScriptEngine() const;
		Scripting::ScriptClass GetClass(std::string assembly, std::string namespaceName, std::string className) const;
		Math::Vector2i GetScreenSize() const;

		void SetPostprocessingConfiguration(std::string filePath);

		Scene& CreateScene();
		void RemoveScene(Scene& scene);

		void SetCurrentScene(Scene& scene);
		Scene& GetCurrentScene() const;

		void Exit();
		void Run();


#pragma endregion 


	};

}

#endif