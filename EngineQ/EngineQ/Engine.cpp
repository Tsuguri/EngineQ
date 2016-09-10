﻿#include "Engine.hpp"

#include <iostream>
#include <fstream>
#include <memory>

#include "Scene.hpp"
#include "Graphics/Shader.hpp"

#include "TimeCounter.hpp"

#include "Utilities/ResourcesIDs.hpp"
#include "Graphics/RenderingUnit.hpp"

namespace EngineQ
{

	Engine* Engine::instance = nullptr;

	Engine::Engine(std::string name, int width, int height)
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
		glViewport(0, 0, width, height);
		screenSize = Vector2i{ width,height };
		resourceManager = std::make_unique<ResourceManager>();
	}

	void Engine::WindowResized(int width, int height)
	{
		screenSize = Vector2i{ width,height };
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



		instance = new Engine{ name, width, height };

		std::string monoPath = "./";
		std::string engineAssemblyPath = "./";
		std::string scriptsAssembliesPath = "./Scripts/";
		auto sem = new Scripting::ScriptEngine{ assemblyName, (engineAssemblyPath + "EngineQ.dll").c_str(), (monoPath + "libraries").c_str(), (monoPath + "config").c_str() };
		instance->scriptingEngine = std::unique_ptr<Scripting::ScriptEngine>(sem);

		instance->scriptingEngine->LoadAssembly((scriptsAssembliesPath + "QScripts.dll").c_str());
		instance->input.InitMethods(instance->scriptingEngine.get());
		return true;
	}

	Scripting::ScriptClass Engine::GetClass(std::string assembly, std::string namespaceName, std::string className) const
	{
		return scriptingEngine->GetScriptClass(assembly.c_str(), namespaceName.c_str(), className.c_str());
	}

	Vector2i Engine::GetScreenSize() const
	{
		return screenSize;
	}

	void Engine::SetPostprocessingConfiguration(std::string filePath)
	{
		renderingUnit = std::make_shared<Graphics::RenderingUnit>(this, Graphics::RenderingUnitConfiguration::Load(filePath));
	}

	Scene* Engine::CreateScene() const
	{
		return new Scene(*scriptingEngine.get());
	}

	void Engine::Exit()
	{
		running = false;
	}

	Engine* Engine::Get()
	{
		if (instance != nullptr)
			return instance;
		else
		{
			std::cout << "EngineQ is not initialized" << std::endl;
			return nullptr;
		}
	}

	ResourceManager* Engine::GetResourceManager() const
	{
		return resourceManager.get();
	}

	Graphics::RenderingUnitConfiguration GenerateDefaultConfiguration()
	{
		std::string tex1Name = "tex1";
		std::string tex2Name = "tex2";
		std::string tex3Name = "tex3";
		Graphics::RenderingUnitConfiguration p{};
		p.Renderer.Output.push_back(Graphics::OutputTexture{ tex1Name });

		p.Textures.push_back(Graphics::TextureConfiguration{ tex1Name });
		p.Textures.push_back(Graphics::TextureConfiguration{ tex2Name });
		p.Textures.push_back(Graphics::TextureConfiguration{ tex3Name });

		auto extract = Graphics::EffectConfiguration{};
		extract.Input.push_back(Graphics::InputPair{ 0,tex1Name });
		extract.Output.push_back(Graphics::OutputTexture{ tex2Name });
		extract.Shader = Utilities::ResourcesIDs::BrightExtract;
		p.Effects.push_back(extract);

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
			p.Effects.push_back(blurVertical);
			p.Effects.push_back(blur);
		}

		auto quad = Graphics::EffectConfiguration{};
		quad.Input.push_back(Graphics::InputPair{ 0, tex1Name, "scene" });
		quad.Input.push_back(Graphics::InputPair{ 1,tex2Name, "bloomBlur" });
		quad.Output.push_back(Graphics::OutputTexture{ "Screen" });
		quad.Shader = Utilities::ResourcesIDs::CombineShader;
		p.Effects.push_back(quad);

		return p;
	}


	void Engine::Run(Scene* scene)
	{
		auto& tc{ *TimeCounter::Get() };
		tc.Update(0, 0);

		float time = 0, tmp;
		while (!window.ShouldClose() && running)
		{
			//input
			window.PollEvents();

			//update time
			tmp = window.GetTime();
			tc.Update(tmp, tmp - time);
			time = tmp;

			//update scene logic (scripts)
			scene->Update();

			// render scene
			renderingUnit->Render(scene);

			// clear frame-characteristic data
			input.ClearDelta();

			//show result on screen
			window.SwapBuffers();
		}
		window.Close();
	}
}
