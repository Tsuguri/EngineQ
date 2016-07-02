#include <iostream>

#include "Math/Vector4.hpp"
#include "Math/Matrix4.hpp"

int main(int argc, char** argv)
{
	EngineQ::Math::Vector4 vec{ 1, 2, 3, 4 };
	EngineQ::Math::Matrix4 mat = EngineQ::Math::Matrix4::GetIdentity();

	std::cout << "Vector4: " << vec.ToString() << std::endl;
	std::cout << "Matrix4: " << mat.ToString() << std::endl;

	std::cout << "mat * vec = " << (mat * vec).ToString() << std::endl;

	return 0;
}
