#ifndef ENGINEQHPP
#define ENGINEQHPP
#include <string>

namespace EngineQ
{

class EngineQ
{
#pragma region Fields

private:
	static EngineQ* instance;

public:
#pragma endregion 

#pragma region Methods

private:
	EngineQ(std::string name, int width, int height);
public:
	static void Initialize(std::string name, int width, int height);
	static EngineQ* Get();
#pragma endregion 


};

}

#endif