#ifndef ENGINEQHPP
#define ENGINEQHPP
#include <string>

class GLFWwindow;

namespace EngineQ
{

class EngineQ
{
#pragma region Fields

private:
	static EngineQ* instance;
	GLFWwindow* window;

public:
#pragma endregion 

#pragma region Methods

private:
	EngineQ(std::string name, int width, int height);
	static void KeyControl(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void MouseButtonControl(GLFWwindow* window, int button, int action, int mods);
	static void MouseControl(GLFWwindow* window, double xpos, double ypos);
public:
	static bool Initialize(std::string name, int width, int height);
	static EngineQ* Get();
#pragma endregion 


};

}

#endif