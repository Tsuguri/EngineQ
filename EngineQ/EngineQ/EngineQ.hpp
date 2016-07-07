#ifndef ENGINEQHPP
#define ENGINEQHPP
#include <string>

#include "GLFWWindow.hpp"
namespace EngineQ
{

class EngineQ
{
#pragma region Fields

private:
	static EngineQ* instance;
	GLFWWindow window;

public:
#pragma endregion 

#pragma region Methods

private:
	EngineQ(std::string name, int width, int height);
	static void KeyControl(int key, int scancode, int action, int mode);
	static void MouseButtonControl(int button, int action, int mods);
	static void MouseControl(double xpos, double ypos);
public:
	static bool Initialize(std::string name, int width, int height);
	static EngineQ* Get();

	void Run(const char* name);

#pragma endregion 


};

}

#endif