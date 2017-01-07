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
		Logger::LogMessage("Creating  EngineQ", "\n");
		if (!window.Initialize(config.windowName, config.windowWidth, config.windowHeight))
		{
			Logger::LogMessage("Unable to initialize window", "\n");
			throw std::runtime_error{ "Unable to start window" };
		}

		window.SetKeyFunction(KeyControl);
		window.SetMouseButtonFunction(MouseButtonControl);
		window.SetMouseControlFunction(MouseControl);
		window.SetFramebufferResizeFunction(FramebufferResize);

		screenSize = Math::Vector2i{ static_cast<int>(config.windowWidth), static_cast<int>(config.windowHeight) };

		this->scriptingEngine = std::make_unique<Scripting::ScriptEngine>(config.applicationPath.c_str(), config.engineAssemblyPath.c_str(), (config.monoDirectory + "libraries").c_str(), (config.monoDirectory + "config").c_str());

		for (const auto& scriptAssembly : config.scriptAssemblies)
			this->scriptingEngine->LoadAssembly((config.scriptsDirectory + scriptAssembly).c_str());

		this->input.InitMethods(this->scriptingEngine.get());

		this->resourceManager = std::make_unique<Resources::ResourceManager>(*this->scriptingEngine);
		this->currentScene = &this->CreateScene();

		this->initializerMethod = this->scriptingEngine->GetInitializerMethod(config.initializerAssembly, config.initializerNamespace, config.initializerClass);


		this->renderConfig = IntermediateRenderingUnitConfiguration::Load(config.postprocessingConfig);
	}

	void Engine::WindowResized(int width, int height)
	{
		screenSize = Math::Vector2i{ width,height };
		
		if (!ResizeEventIsEmpty())
			ResizeEventInvoke(width, height);

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

	Math::Vector2i Engine::GetScreenSize() const
	{
		return screenSize;
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

		this->renderingUnit = std::make_unique<Graphics::ScriptedRenderingUnit>(*this->scriptingEngine.get(), static_cast<Graphics::ScreenDataProvider*>(this), this->renderConfig.ToRenderingUnitConfiguration(resourceManager.get()));
		

		auto& timeCounter = TimeCounter::Get();
		timeCounter.Update(0.0f, 0.0f);

		float lastTime = 0.0f;
		while (!this->window.ShouldClose() && this->isRunning)
		{
			this->profiler.Start("Main loop");

			// Input
			this->profiler.Start("Input");
			this->window.PollEvents();
			this->profiler.End("Input");

			// Update lastTime
			float currentTime = static_cast<float>(window.GetTime());
			timeCounter.Update(currentTime, currentTime - lastTime);
			lastTime = currentTime;

			// Update resource manager
			this->profiler.Start("Resource Manager");
			this->resourceManager->Update();
			this->profiler.End("Resource Manager");

			this->profiler.Start("Scripts");
			// Update scene logic (scripts)
			this->currentScene->Update();
			// Update renderer
			this->renderingUnit->Update();
			this->profiler.End("Scripts");

			// Render scene
			this->profiler.Start("Renderer");
			this->renderingUnit->Render(*this->currentScene);
			this->profiler.End("Renderer");

			// Clear frame-characteristic data
			this->input.ClearDelta();

			// Show result on screen
			this->window.SwapBuffers();

			// Update profiler
			this->profiler.End("Main loop");
			this->profiler.Update();
		}
		this->window.Close();
	}
}
