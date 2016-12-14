#ifndef ENGINEQ_ENGINEQ_HPP
#define ENGINEQ_ENGINEQ_HPP

#include <string>
#include <memory>

//#include <Graphics\Types.hpp>

#include "Window.hpp"
#include "Scripting/ScriptEngine.hpp"
#include "Objects/Scene.hpp"
#include "InputController.hpp"
#include "Resources/ResourceManager.hpp"
#include "Utilities/Event.hpp"

#include "RendererIntermediateConfiguration.hpp"
#include "Math/Vector2.hpp"

#include <Graphics\Utils\ScreenDataProvider.hpp>

namespace EngineQ
{
	class Engine : private Utilities::Immovable, public Graphics::ScreenDataProvider
	{
	#pragma region Types

	public:
		struct Config
		{
			std::string applicationPath;

			std::string monoDirectory = "./";

			std::string windowName = "EngineQ";
			unsigned int windowWidth = 800;
			unsigned int windowHeight = 600;

			std::string scriptsDirectory = "./Scripts/";
			std::string engineAssemblyPath = "./EngineQ.dll";

			std::vector<std::string> scriptAssemblies;

			std::string initializerAssembly;
			std::string initializerNamespace;
			std::string initializerClass;

			std::string postprocessingConfig;
		};

	#pragma endregion

	#pragma region Fields

	private:
		static std::unique_ptr<Engine> instance;

		IntermediateRenderingUnitConfiguration renderConfig;

		Window window;
		bool isRunning = true;
		Math::Vector2i screenSize;

	public:
		//Utilities::Event<Engine, void(int, int)> resizeEvent;
		InputController input;

	private:
		std::unique_ptr<Scripting::ScriptEngine> scriptingEngine;
		std::unique_ptr<Resources::ResourceManager> resourceManager;
		std::shared_ptr<Graphics::RenderingUnit> renderingUnit;

		std::vector<std::unique_ptr<Scene>> scenes;
		Scene* currentScene = nullptr;

		Scripting::ScriptMethod initializerMethod;

	#pragma endregion 

	#pragma region Methods

	private:
		Engine(const Config& config);

		void WindowResized(int width, int height);

		static void KeyControl(int key, int scancode, int action, int mode);
		static void MouseButtonControl(int button, int action, int mode);
		static void MouseControl(double xpos, double ypos);
		static void FramebufferResize(int width, int height);
	
	public:
		static bool Initialize(const Config& config);

		static Engine& Get();
		Resources::ResourceManager& GetResourceManager() const;
		Scripting::ScriptEngine& GetScriptEngine() const;
		Math::Vector2i GetScreenSize() const override;

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