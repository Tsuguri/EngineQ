#ifndef ENGINEQ_ENGINEQ_HPP
#define ENGINEQ_ENGINEQ_HPP

// Standard includes
#include <string>
#include <memory>

// Other projects
#include "EngineQCommon/Math/Vector2.hpp"
#include "EngineQCommon/Utilities/Event.hpp"

// This project
#include "Systems/Window.hpp"
#include "Systems/Profiler.hpp"
#include "Systems/TimeCounter.hpp"
#include "Systems/InputController.hpp"
#include "Graphics/RendererIntermediateConfiguration.hpp"
#include "Objects/Scene.hpp"
#include "Resources/ResourceManager.hpp"
#include "Scripting/ScriptEngine.hpp"
#include "Graphics/ScriptedRenderingUnit.hpp"


namespace EngineQ
{
	class Engine : private Utilities::Immovable
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

		bool isRunning = true;

		Profiler profiler;
		IntermediateRenderingUnitConfiguration renderConfig;

		std::unique_ptr<Window> window;

		std::unique_ptr<Scripting::ScriptEngine> scriptingEngine;
		TimeCounter timeCounter;
		InputController input;
		std::unique_ptr<Resources::ResourceManager> resourceManager;
		std::unique_ptr<Graphics::ScriptedRenderingUnit> renderingUnit;

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
		static bool Finalize();
		static Engine& Get();

		~Engine();
	
		Resources::ResourceManager& GetResourceManager() const;
		Scripting::ScriptEngine& GetScriptEngine() const;
		Profiler& GetProfiler();
		TimeCounter& GetTimeCounter();
		InputController& GetInputController();
		Window& GetWindow();

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