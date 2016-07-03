#include "EngineQ.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

namespace EngineQ
{

	EngineQ* EngineQ::instance = nullptr;

	EngineQ::EngineQ(std::string name, int width, int height)
	{

		std::cout << "Creating  EngineQ" << std::endl;
	}

	void EngineQ::Initialize(std::string name, int width, int height)
	{
		if (instance != nullptr)
		{
			std::cout << "EngineQ is already initialized" << std::endl;
			return;
		}
		std::cout << "Initializing EngineQ" << std::endl;

		instance = new EngineQ(name, width, height);

	}

	EngineQ* EngineQ::Get()
	{
		if (instance != nullptr)
			return instance;
		else
		{
			std::cout << "EngineQ is not initialized" << std::endl;
			return nullptr;
		}
	}
}