#ifndef UTILITIES_EMITER_HPP
#define UTILITIES_EMITER_HPP

#include <string>

namespace Utilities
{
	class Emiter
	{
	private:
		std::string objectName;

	public:
		Emiter(const std::string& objectName);
		~Emiter();
	};
}

#endif // !UTILITIES_EMITER_HPP
