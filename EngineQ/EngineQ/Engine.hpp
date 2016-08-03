#ifndef ENGINEQ_ENGINEQ_HPP
#define ENGINEQ_ENGINEQ_HPP

#include <string>
#include <memory>

#include "Window.hpp"
#include "Scripting/ScriptEngine.hpp"
#include "Scene.hpp"
#include "InputController.hpp"


namespace EngineQ
{

	class Engine
	{
#pragma region Fields

	private:
		std::unique_ptr<Scripting::ScriptEngine> scriptingEngine;
		static Engine* instance;
		Window window;
		bool running = true;

	public:
		InputController input;

#pragma endregion 

#pragma region Methods

	private:

		Engine(std::string name, int width, int height);

		static void KeyControl(int key, int scancode, int action, int mode);
		static void MouseButtonControl(int button, int action, int mode);
		static void MouseControl(double xpos, double ypos);
	public:
		static bool Initialize(std::string name, int width, int height, char* assemblyName);
		static Engine* Get();

		Scripting::ScriptClass GetClass(std::string assembly, std::string namespaceName, std::string className) const;
		Scene* CreateScene() const;
		void Exit();
		void Run(Scene* scene);

#pragma endregion 


	};

}

#endif