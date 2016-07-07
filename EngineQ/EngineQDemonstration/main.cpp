#include "EngineQ.hpp"

int main(int argc, char** argv)
{
	EngineQ::EngineQ::Initialize("Turbo giera", 800, 600);
	try
	{
		EngineQ::EngineQ::Get()->Run(argv[0]);
	}
	catch (...)
	{
		getchar();
	}
	return 0;
}