#ifndef ENGINEQ_ENGINEQ_HPP
#define ENGINEQ_ENGINEQ_HPP

#include <string>
#include <memory>

#include "GLFWWindow.hpp"
#include "Scripting/ScriptEngine.hpp"
#include "Scene.hpp"
#include "InputController.hpp"
namespace EngineQ
{

class Engine
{
#pragma region Fields

private:
	static Engine* instance;
	GLFWWindow window;
	
public:
	InputController input;
#pragma endregion 

#pragma region Methods

private:
	std::unique_ptr<Scripting::ScriptEngine> se;

	Engine(std::string name, int width, int height);
	static void KeyControl(int key, int scancode, int action, int mode);
	static void MouseButtonControl(int button, int action, int mode);
	static void MouseControl(double xpos, double ypos);
public:
	static bool Initialize(std::string name, int width, int height, char* assemblyName);
	Scripting::ScriptClass GetClass(std::string assembly, std::string namespaceName, std::string className);
	Scene* CreateScene() const;
	static Engine* Get();

	void Run(Scene* scene);

#pragma endregion 


};

}

#endif