﻿#include "Engine.hpp"

#include <iostream>
#include <fstream>
#include <memory>

#include "Scene.hpp"
#include "Graphics/Shader.hpp"
#include "Graphics/ForwardRenderer.hpp"
#include "TimeCounter.hpp"

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
	}

	void Engine::WindowResized(int width, int height)
	{

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
		return scriptingEngine->GetScriptClass(assembly.c_str(),namespaceName.c_str(), className.c_str());
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



	void Engine::Run(Scene* scene)
	{
		auto& tc{ *TimeCounter::Get()};
		tc.Update(0, 0);

		Graphics::ForwardRenderer renderer;

		float time=0,tmp;
		while (!window.ShouldClose() && running)
		{
			//input
			window.PollEvents();

			tmp = window.GetTime();
			tc.Update(tmp, tmp-time);
			time = tmp;
			//check input and stuff
			scene->Update();
			//scripts & logic

			renderer.Render(scene);

			input.ClearDelta();

			window.SwapBuffers();
		}
		window.Close();
	}
}
