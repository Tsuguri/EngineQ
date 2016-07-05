#include "EngineQ.hpp"

int main()
{
	EngineQ::EngineQ::Initialize("Turbo giera", 800, 600);

	EngineQ::EngineQ::Get()->Run();
	
	return 0;
}