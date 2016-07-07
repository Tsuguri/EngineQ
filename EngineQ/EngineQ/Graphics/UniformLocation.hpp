#ifndef ENGINEQ_GRAPHICS_UNIFORM_LOCATION_HPP
#define ENGINEQ_GRAPHICS_UNIFORM_LOCATION_HPP

#include "GL/glew.h"

namespace EngineQ
{
	namespace Graphics
	{
		class Shader;

		class UniformLocation
		{
			friend class Shader;

		private:
			GLint location;

			UniformLocation(GLint location);
		};
	}
}

#endif // !ENGINEQ_GRAPHICS_UNIFORM_LOCATION_HPP
