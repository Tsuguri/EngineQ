#include "Emiter.hpp"

// Standard includes
#include <iostream>


namespace Utilities
{
	Emiter::Emiter(const std::string& objectName) :
		objectName{ objectName }
	{
		std::cout << "Emiter: Constructed " << this->objectName << std::endl;
	}

	Emiter::~Emiter()
	{
		std::cout << "Emiter: Destructed " << this->objectName << std::endl;
	}
}