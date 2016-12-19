#ifndef ENGINEQ_GRAPHICS_SHADER_EXCEPTIONS_HPP
#define ENGINEQ_GRAPHICS_SHADER_EXCEPTIONS_HPP

// Standard includes
#include <stdexcept>


namespace EngineQ
{
	namespace Graphics
	{
		class ShaderCompilationException : public std::runtime_error
		{
		public:
			using std::runtime_error::runtime_error;
		};

		class ShaderLinkException : public std::runtime_error
		{
		public:
			using std::runtime_error::runtime_error;
		};

		class ShaderArgumentException : public std::runtime_error
		{
		public:
			using std::runtime_error::runtime_error;
		};

		class InvalidUniformTypeException : public std::runtime_error
		{
		public:
			using std::runtime_error::runtime_error;
		};
	}
}

#endif // !ENGINEQ_GRAPHICS_SHADER_EXCEPTIONS_HPP
