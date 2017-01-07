#include "Engine.hpp"

// Standard includes
#include <fstream>
#include <memory>

// Other projects
#include "EngineQCommon/Math/Vector2.hpp"
#include "EngineQRenderer/Graphics/RenderingUnit.hpp"
#include "EngineQRenderer/Graphics/Shader.hpp"

// This project
#include "Systems/Logger.hpp"
#include "Systems/TimeCounter.hpp"
#include "Objects/Scene.hpp"
#include "Objects/Camera.hpp"
#include "Resources/ResourceManager.hpp"


namespace EngineQ
{
	std::unique_ptr<Engine> Engine::instance = nullptr;

	Engine::Engine(const Config& config)
	{
		Logger::LogMessage("Creating  EngineQ\n");

		Window::EngineCallbacks::Initialize();

		window = std::make_unique<Window>(config.windowName, config.windowWidth, config.windowHeight);

		window->SetKeyFunction(KeyControl);
		window->SetMouseButtonFunction(MouseButtonControl);
		window->SetMousePositionFunction(MouseControl);
		window->SetResizeFunction(FramebufferResize);

		this->scriptingEngine = std::make_unique<Scripting::ScriptEngine>(config.applicationPath.c_str(), config.engineAssemblyPath.c_str(), (config.monoDirectory + "libraries").c_str(), (config.monoDirectory + "config").c_str());

		for (const auto& scriptAssembly : config.scriptAssemblies)
			this->scriptingEngine->LoadAssembly((config.scriptsDirectory + scriptAssembly).c_str());

		this->input.InitMethods(this->scriptingEngine.get());

		this->resourceManager = std::make_unique<Resources::ResourceManager>(*this->scriptingEngine);
		this->currentScene = &this->CreateScene();

		this->initializerMethod = this->scriptingEngine->GetInitializerMethod(config.initializerAssembly, config.initializerNamespace, config.initializerClass);


		this->renderConfig = IntermediateRenderingUnitConfiguration::Load(config.postprocessingConfig);
	}

	Engine::~Engine()
	{
		Window::EngineCallbacks::Finalize();
	}

	void Engine::WindowResized(int width, int height)
	{
		if (this->currentScene != nullptr)
		{
			auto activeCamera = this->currentScene->GetActiveEngineCamera();
			if(activeCamera != nullptr)
				activeCamera->SetAspectRatio(static_cast<float>(width) / static_cast<float>(height));
		}
	}

	void Engine::KeyControl(int key, int scancode, int action, int mode)
	{
		instance->input.OnKeyAction(key, scancode, action, mode);
	}

	void Engine::MouseButtonControl(int button, int action, int mods)
	{
		instance->input.OnMouseButtonAction(button, action, mods);
	}

	void Engine::MouseControl(double xpos, double ypos)
	{
		instance->input.OnMouseMoveAction(xpos, ypos);
	}

	void Engine::FramebufferResize(int width, int height)
	{
		instance->WindowResized(width, height);
	}

	bool Engine::Initialize(const Config& config)
	{
		if (instance != nullptr)
		{
			Logger::LogMessage("EngineQ is already initialized", "\n");
			return false;
		}
		Logger::LogMessage("Initializing EngineQ", "\n");

		instance = std::unique_ptr<Engine>{ new Engine{ config } };

		return true;
	}

	bool Engine::Finalize()
	{
		if (instance == nullptr)
		{
			Logger::LogMessage("EngineQ is already finalized\n");
			return false;
		}
		Logger::LogMessage("Finalizing EngineQ\n");

		instance = nullptr;

		return true;
	}

	Scene& Engine::CreateScene()
	{
		this->scenes.push_back(std::make_unique<Scene>(*this->scriptingEngine,this));
		return *this->scenes.back();
	}

	void Engine::RemoveScene(Scene& scene)
	{
		if (this->currentScene == &scene)
			throw std::runtime_error{ "Cannot remove current scene" };

		auto it = this->scenes.begin();
		for (auto end = this->scenes.end(); it != end; ++it)
			if (it->get() == &scene)
				break;
		if (it == this->scenes.end())
			throw std::runtime_error{ "Scene not found" };

		this->scenes.erase(it);
	}

	void Engine::SetCurrentScene(Scene& scene)
	{
		auto it = this->scenes.begin();
		for (auto end = this->scenes.end(); it != end; ++it)
			if (it->get() == &scene)
				break;
		if (it == this->scenes.end())
			throw std::runtime_error{ "Scene not found" };

		this->currentScene = &scene;
	}

	Scene& Engine::GetCurrentScene() const
	{
		return *this->currentScene;
	}

	void Engine::Exit()
	{
		isRunning = false;
	}

	Engine& Engine::Get()
	{
		if (instance != nullptr)
			return *instance;

		throw std::runtime_error{ "Engine not initialized" };
	}

	Profiler& Engine::GetProfiler()
	{
		return this->profiler;
	}

	TimeCounter& Engine::GetTimeCounter()
	{
		return this->timeCounter;
	}

	InputController& Engine::GetInputController()
	{
		return this->input;
	}

	Window& Engine::GetWindow()
	{
		return *this->window;
	}

	Resources::ResourceManager& Engine::GetResourceManager() const
	{
		return *this->resourceManager;
	}

	Scripting::ScriptEngine& Engine::GetScriptEngine() const
	{
		return *this->scriptingEngine;
	}

	void Engine::Run()
	{
		void* args[] =
		{
			static_cast<void*>(this->currentScene->GetManagedObject())
		};

		this->scriptingEngine->InvokeStaticMethod(this->initializerMethod, args);

		this->renderingUnit = std::make_unique<Graphics::ScriptedRenderingUnit>(*this->scriptingEngine.get(), static_cast<Graphics::ScreenDataProvider*>(window.get()), this->renderConfig.ToRenderingUnitConfiguration(resourceManager.get()));

		this->timeCounter.Update();
		while (!this->window->ShouldClose() && this->isRunning)
		{
			this->profiler.Start("Main loop", "Main");

			// Update time counter
			this->timeCounter.Update();

			// Input
			this->profiler.Start("Input", "Main");
			this->input.Update();
			Window::EngineCallbacks::PollEvents();
			this->profiler.End("Input", "Main");

			// Update resource manager
			this->profiler.Start("Resource Manager", "Main");
			this->resourceManager->Update();
			this->profiler.End("Resource Manager", "Main");

			this->profiler.Start("Scripts", "Main");
			// Update scene logic (scripts)
			this->currentScene->Update();
			// Update renderer
			this->renderingUnit->Update();
			this->profiler.End("Scripts", "Main");

			// Render scene
			this->profiler.Start("Renderer", "Main");
			this->renderingUnit->Render(*this->currentScene);
			this->profiler.End("Renderer", "Main");
			
			// Show result on screen
			Window::EngineCallbacks::SwapBuffers(*this->window);

			// Update profiler
			this->profiler.End("Main loop", "Main");
			this->profiler.Update();
		}
		this->window->RequestClose();
	}
}
