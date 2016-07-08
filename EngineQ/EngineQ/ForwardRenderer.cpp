#include "ForwardRenderer.hpp"
#include <GL/glew.h>

namespace EngineQ
{
	namespace Graphics
	{
		ForwardRenderer::ForwardRenderer()
		{
			glEnable(GL_DEPTH_TEST);
			glFrontFace(GL_CCW);
			glPolygonMode(GL_FRONT, GL_FILL);
			glPolygonMode(GL_BACK, GL_FILL);
			glCullFace(GL_BACK);
			glEnable(GL_CULL_FACE);
		}
	}
}
