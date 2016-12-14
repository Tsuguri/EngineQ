#include "Engine.hpp"

#include <iostream>
#include <fstream>
#include <memory>

#include "Objects/Scene.hpp"
#include <Graphics/Shader.hpp>
#include "TimeCounter.hpp"

#include "Resources/ResourceManager.hpp"
#include "Utilities/ResourcesIDs.hpp"
#include <Graphics/RenderingUnit.hpp>
#include "Objects/Camera.hpp"

#include "Math/Vector2.hpp"

namespace EngineQ
{
	std::unique_ptr<Engine> Engine::instance = nullptr;

	Engine::Engine(const Config& config)
	{
		std::cout << "Creating  EngineQ" << std::endl;
		if (!window.Initialize(config.windowName, config.windowWidth, config.windowHeight))
		{
			std::cout << "Unable to initialize window" << std::endl;
			throw std::runtime_error{ "Unable to start window" };
		}

		window.SetKeyFunction(KeyControl);
		window.SetMouseButtonFunction(MouseButtonControl);
		window.SetMouseControlFunction(MouseControl);
		window.SetFramebufferResizeFunction(FramebufferResize);

		screenSize = Math::Vector2i{ config.windowWidth, config.windowHeight };

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
		instance->input.KeyAction(key, scancode, action, mode);
	}

	void Engine::MouseButtonControl(int button, int action, int mods)
	{
		instance->input.MouseButtonAction(button, action, mods);
	}

	void Engine::MouseControl(double xpos, double ypos)
	{
		instance->input.MouseMoveAction(xpos, ypos);
	}

	void Engine::FramebufferResize(int width, int height)
	{
		instance->WindowResized(width, height);
	}

	bool Engine::Initialize(const Config& config)
	{
		if (instance != nullptr)
		{
			std::cout << "EngineQ is already initialized" << std::endl;
			return false;
		}
		std::cout << "Initializing EngineQ" << std::endl;

		instance = std::unique_ptr<Engine>{ new Engine{ config } };

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

	Resources::ResourceManager& Engine::GetResourceManager() const
	{
		return *resourceManager;
	}

	Scripting::ScriptEngine& Engine::GetScriptEngine() const
	{
		return *this->scriptingEngine;
	}

	IntermediateRenderingUnitConfiguration GenerateDefaultConfiguration()
	{
		std::string tex1Name = "tex1";
		std::string tex2Name = "tex2";
		std::string tex3Name = "tex3";
		IntermediateRenderingUnitConfiguration config{};
		config.Renderer.Output.push_back(Graphics::Configuration::OutputTexture{ tex1Name });

		config.Textures.push_back(Graphics::Configuration::TextureConfiguration{ tex1Name });
		config.Textures.push_back(Graphics::Configuration::TextureConfiguration{ tex2Name });
		config.Textures.push_back(Graphics::Configuration::TextureConfiguration{ tex3Name });

		auto extract = IntermediateEffectConfiguration{};
		extract.Input.push_back(Graphics::Configuration::InputPair{ 0,tex1Name });
		extract.Output.push_back(Graphics::Configuration::OutputTexture{ tex2Name });
		extract.Shader = Utilities::ResourcesIDs::BrightExtract;
		config.Effects.push_back(extract);

		auto blurVertical = IntermediateEffectConfiguration{};
		blurVertical.Input.push_back(Graphics::Configuration::InputPair{ 0,tex2Name });
		blurVertical.Output.push_back(Graphics::Configuration::OutputTexture{ tex3Name });
		blurVertical.Shader = Utilities::ResourcesIDs::BlurVShader;


		auto blur = IntermediateEffectConfiguration{};
		blur.Input.push_back(Graphics::Configuration::InputPair{ 0,tex3Name });
		blur.Output.push_back(Graphics::Configuration::OutputTexture{ tex2Name });
		blur.Shader = Utilities::ResourcesIDs::BlurShader;


		for (int i = 0; i < 5; i++)
		{
			config.Effects.push_back(blurVertical);
			config.Effects.push_back(blur);
		}

		auto quad = IntermediateEffectConfiguration{};
		quad.Input.push_back(Graphics::Configuration::InputPair{ 0, tex1Name, "scene" });
		quad.Input.push_back(Graphics::Configuration::InputPair{ 1,tex2Name, "bloomBlur" });
		quad.Output.push_back(Graphics::Configuration::OutputTexture{ "Screen" });
		quad.Shader = Utilities::ResourcesIDs::CombineShader;
		config.Effects.push_back(quad);

		return config;
	}

	void Engine::Run()
	{
		void* args[] =
		{
			static_cast<void*>(this->currentScene->GetManagedObject())
		};

		this->scriptingEngine->InvokeStaticMethod(this->initializerMethod, args);

		this->renderingUnit = std::make_shared<Graphics::RenderingUnit>(static_cast<Graphics::ScreenDataProvider*>(this), this->renderConfig.ToRenderingUnitConfiguration(resourceManager.get()));



		auto& timeCounter = TimeCounter::Get();
		timeCounter.Update(0.0f, 0.0f);

		float lastTime = 0.0f;
		while (!this->window.ShouldClose() && this->isRunning)
		{
			// Input
			this->window.PollEvents();

			// Update lastTime
			float currentTime = static_cast<float>(window.GetTime());
			timeCounter.Update(currentTime, currentTime - lastTime);
			lastTime = currentTime;

			// Update resource manager
			this->resourceManager->Update();

			// Update scene logic (scripts)
			this->currentScene->Update();

			// Render scene
			this->renderingUnit->Render(*this->currentScene);

			// Clear frame-characteristic data
			this->input.ClearDelta();

			// Show result on screen
			this->window.SwapBuffers();
		}
		this->window.Close();
	}
}
