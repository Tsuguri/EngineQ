#ifndef ENGINEQ_ENGINEQ_HPP
#define ENGINEQ_ENGINEQ_HPP

#include <string>
#include <memory>

#include "GLFWWindow.hpp"
#include "Scripting/ScriptEngine.hpp"
#include "Scene.hpp"

namespace EngineQ
{

class Engine
{
#pragma region Fields

private:
	static Engine* instance;
	GLFWWindow window;

public:
#pragma endregion 

#pragma region Methods

private:
	std::unique_ptr<Scripting::ScriptEngine> se;


	Engine(std::string name, int width, int height);
	static void KeyControl(int key, int scancode, int action, int mode);
	static void MouseButtonControl(int button, int action, int mods);
	static void MouseControl(double xpos, double ypos);
public:
	static bool Initialize(std::string name, int width, int height, char* assemblyName);
	Scene* CreateScene() const;
	static Engine* Get();

	void Run(Scene* scene);

#pragma endregion 


};

}

#endif