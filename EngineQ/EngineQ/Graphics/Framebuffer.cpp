#include "Framebuffer.hpp"
#include "../Engine.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		GLuint Framebuffer::locations[8] = {
			GL_COLOR_ATTACHMENT0,
			GL_COLOR_ATTACHMENT1,
			GL_COLOR_ATTACHMENT2,
			GL_COLOR_ATTACHMENT3,
			GL_COLOR_ATTACHMENT4,
			GL_COLOR_ATTACHMENT5,
			GL_COLOR_ATTACHMENT6,
			GL_COLOR_ATTACHMENT7
		};


		void Framebuffer::CreateDepthTesting()
		{
			glGenRenderbuffers(1, &depthRbo);
			glBindRenderbuffer(GL_RENDERBUFFER, depthRbo);
			auto size = engine->GetScreenSize();
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.X, size.Y);
			glBindRenderbuffer(GL_RENDERBUFFER, 0);

			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthRbo);
		}

		void Framebuffer::Resize(int width, int height)
		{
			if(depthRbo>0)
			{
				glDeleteRenderbuffers(1, &depthRbo);
				CreateDepthTesting();
			}
		}

		Framebuffer::Framebuffer(Engine* engine) : engine(engine), handler(*this,&Framebuffer::Resize)
		{
			glGenFramebuffers(1, &fbo);
			glBindFramebuffer(GL_FRAMEBUFFER, fbo);

			CreateDepthTesting();

			engine->resizeEvent += handler;
			
		}

		Framebuffer::~Framebuffer()
		{
			if (depthRbo > 0)
				glDeleteRenderbuffers(1, &depthRbo);
			glDeleteFramebuffers(1, &fbo);

			engine->resizeEvent -= handler;
		}

		void Framebuffer::Bind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		}

		void Framebuffer::SetTexture(GLuint tex)
		{
			Bind();
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0);
		}

		void Framebuffer::BindDefault()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}
}
