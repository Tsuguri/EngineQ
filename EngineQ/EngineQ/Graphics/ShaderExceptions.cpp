#include "ShaderExceptions.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		ShaderCompilationException::ShaderCompilationException(const char* message) :
			std::runtime_error{ message }
		{
		}

		ShaderCompilationException::ShaderCompilationException(const std::string& message) :
			std::runtime_error{ message }
		{
		}

		ShaderLinkException::ShaderLinkException(const char* message) :
			std::runtime_error{ message }
		{
		}

		ShaderLinkException::ShaderLinkException(const std::string& message) :
			std::runtime_error{ message }
		{
		}


		ShaderArgumentException::ShaderArgumentException(const char* message) :
			std::runtime_error{ message }
		{
		}

		ShaderArgumentException::ShaderArgumentException(const std::string& message) :
			std::runtime_error{ message }
		{
		}
	}
}