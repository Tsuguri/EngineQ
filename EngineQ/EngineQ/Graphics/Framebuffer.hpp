#ifndef ENGINEQ_GRAPHICS_FRAMEBUFFER_HPP
#define ENGINEQ_GRAPHICS_FRAMEBUFFER_HPP

#include "../Libraries/GL/glew.h"

#include "../Utilities/Uncopyable.hpp"
#include "RendererConfiguration.hpp"

namespace EngineQ
{
	namespace Graphics
	{

		// TODO
		class Framebuffer : public EngineQ::Utilities::Uncopyable
		{
			GLuint fbo = 0;
			GLuint textureColor = 0;
			GLuint depthRbo;


			bool ready = false;

		public:
			Framebuffer();
			Framebuffer(EngineQ::Graphics::FramebufferConfiguration* configuration);
			~Framebuffer();

			void Bind() const;
			//remeber that it will automatically bind this framebuffer
			bool Ready();
			static void BindDefault();

			//remeber that it will automatically bind this framebuffer
			void AddDepthTesting(int width, int height);
			void AddColorAttachment(int width, int height, GLint format = GL_RGB);

			GLuint GetColorTexture();
		};

	}
}
#endif
