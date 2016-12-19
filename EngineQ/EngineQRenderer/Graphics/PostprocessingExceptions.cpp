#include "PostprocessingExceptions.hpp"


namespace EngineQ
{
	namespace Graphics
	{
		RendererConfigurationValidationException::RendererConfigurationValidationException(const char* message) : std::runtime_error{message}
		{
		}

		RendererConfigurationValidationException::RendererConfigurationValidationException(const std::string& message) : std::runtime_error{message}
		{
		}

	}
}