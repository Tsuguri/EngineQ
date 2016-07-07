#ifndef ENGINEQ_GRAPHICS_SHADER_EXCEPTIONS_HPP
#define ENGINEQ_GRAPHICS_SHADER_EXCEPTIONS_HPP

#include <stdexcept>

namespace EngineQ
{
	namespace Graphics
	{
		class ShaderCompilationException : public std::runtime_error
		{
		public:
			ShaderCompilationException(const char* message);
			ShaderCompilationException(const std::string& message);
		};

		class ShaderLinkException : public std::runtime_error
		{
		public:
			ShaderLinkException(const char* message);
			ShaderLinkException(const std::string& message);
		};

		class ShaderArgumentException : public std::runtime_error
		{
		public:
			ShaderArgumentException(const char* message);
			ShaderArgumentException(const std::string& message);
		};
	}
}

#endif // !ENGINEQ_GRAPHICS_SHADER_EXCEPTIONS_HPP
