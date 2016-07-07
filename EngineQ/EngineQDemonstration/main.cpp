#include "EngineQ.hpp"

int main(int argc, char** argv)
{
	EngineQ::EngineQ::Initialize("Turbo giera", 800, 600);

	EngineQ::EngineQ::Get()->Run(argv[0]);

	return 0;
}