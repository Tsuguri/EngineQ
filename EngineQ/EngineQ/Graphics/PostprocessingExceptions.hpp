#ifndef ENGINEQ_GRAPHICS_POSTPROCESSING_EXCEPTIONS_HPP
#define ENGINEQ_GRAPHICS_POSTPROCESSING_EXCEPTIONS_HPP
#include <stdexcept>

namespace EngineQ
{
	namespace Graphics
	{
		class RendererConfigurationValidationException : public std::runtime_error
		{
		public:
			RendererConfigurationValidationException(const char* message);
			RendererConfigurationValidationException(const std::string& message);
		};
	}
}
#endif