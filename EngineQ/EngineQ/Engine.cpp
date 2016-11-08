#include "Engine.hpp"

#include <iostream>
#include <fstream>
#include <memory>

#include "Objects/Scene.hpp"
#include "Graphics/Shader.hpp"

#include "TimeCounter.hpp"

#include "Resources/ResourceManager.hpp"
#include "Utilities/ResourcesIDs.hpp"
#include "Graphics/RenderingUnit.hpp"

#include "Math/Vector2.hpp"

namespace EngineQ
{
	std::unique_ptr<Engine> Engine::instance = nullptr;

	Engine::Engine(std::string name, int width, int height, const char* assemblyName)
	{

		std::cout << "Creating  EngineQ" << std::endl;
		if (!window.Initialize(name, width, height))
		{
			std::cout << "Unable to initialize glfw window" << std::endl;
			throw std::logic_error("Unable to start glfw window");
		}

		window.SetKeyFunction(KeyControl);
		window.SetMouseButtonFunction(MouseButtonControl);
		window.SetMouseControlFunction(MouseControl);
		window.SetFramebufferResizeFunction(FramebufferResize);

		// Define the viewport dimensions
		// TODO: This should be handled by renderer class
		glViewport(0, 0, width, height);
		screenSize = Math::Vector2i{ width,height };


		std::string monoPath = "./";
		std::string engineAssemblyPath = "./";
		std::string scriptsAssembliesPath = "./Scripts/";
		
		this->scriptingEngine = std::make_unique<Scripting::ScriptEngine>(assemblyName, (engineAssemblyPath + "EngineQ.dll").c_str(), (monoPath + "libraries").c_str(), (monoPath + "config").c_str());

		this->scriptingEngine->LoadAssembly((scriptsAssembliesPath + "QScripts.dll").c_str());
		this->input.InitMethods(this->scriptingEngine.get());

		this->resourceManager = std::make_unique<Resources::ResourceManager>(*this->scriptingEngine);

		this->currentScene = &this->CreateScene();
	}

	void Engine::WindowResized(int width, int height)
	{
		screenSize = Math::Vector2i{ width,height };
		glViewport(0, 0, width, height);
		if (!resizeEvent.IsEmpty())
			resizeEvent.Invoke(width, height);
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

	bool Engine::Initialize(std::string name, int width, int height, char* assemblyName)
	{
		if (instance != nullptr)
		{
			std::cout << "EngineQ is already initialized" << std::endl;
			return false;
		}
		std::cout << "Initializing EngineQ" << std::endl;

		instance = std::unique_ptr<Engine>(new Engine{ name, width, height, assemblyName });
				
		return true;
	}

	Scripting::ScriptClass Engine::GetClass(std::string assembly, std::string namespaceName, std::string className) const
	{
		return scriptingEngine->GetScriptClass(assembly.c_str(), namespaceName.c_str(), className.c_str());
	}

	Math::Vector2i Engine::GetScreenSize() const
	{
		return screenSize;
	}

	void Engine::SetPostprocessingConfiguration(std::string filePath)
	{
		renderingUnit = std::make_shared<Graphics::RenderingUnit>(this, Graphics::RenderingUnitConfiguration::Load(filePath));
	}

	Scene& Engine::CreateScene()
	{
		this->scenes.push_back(std::make_unique<Scene>(*this->scriptingEngine));
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

	Graphics::RenderingUnitConfiguration GenerateDefaultConfiguration()
	{
		std::string tex1Name = "tex1";
		std::string tex2Name = "tex2";
		std::string tex3Name = "tex3";
		Graphics::RenderingUnitConfiguration config{};
		config.Renderer.Output.push_back(Graphics::OutputTexture{ tex1Name });

		config.Textures.push_back(Graphics::TextureConfiguration{ tex1Name });
		config.Textures.push_back(Graphics::TextureConfiguration{ tex2Name });
		config.Textures.push_back(Graphics::TextureConfiguration{ tex3Name });

		auto extract = Graphics::EffectConfiguration{};
		extract.Input.push_back(Graphics::InputPair{ 0,tex1Name });
		extract.Output.push_back(Graphics::OutputTexture{ tex2Name });
		extract.Shader = Utilities::ResourcesIDs::BrightExtract;
		config.Effects.push_back(extract);

		auto blurVertical = Graphics::EffectConfiguration{};
		blurVertical.Input.push_back(Graphics::InputPair{ 0,tex2Name });
		blurVertical.Output.push_back(Graphics::OutputTexture{ tex3Name});
		blurVertical.Shader = Utilities::ResourcesIDs::BlurVShader;
		

		auto blur = Graphics::EffectConfiguration{};
		blur.Input.push_back(Graphics::InputPair{ 0,tex3Name });
		blur.Output.push_back(Graphics::OutputTexture{ tex2Name});
		blur.Shader = Utilities::ResourcesIDs::BlurShader;
		

		for (int i = 0; i < 5; i++)
		{
			config.Effects.push_back(blurVertical);
			config.Effects.push_back(blur);
		}

		auto quad = Graphics::EffectConfiguration{};
		quad.Input.push_back(Graphics::InputPair{ 0, tex1Name, "scene" });
		quad.Input.push_back(Graphics::InputPair{ 1,tex2Name, "bloomBlur" });
		quad.Output.push_back(Graphics::OutputTexture{ "Screen" });
		quad.Shader = Utilities::ResourcesIDs::CombineShader;
		config.Effects.push_back(quad);

		return config;
	}


	void Engine::Run()
	{
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
