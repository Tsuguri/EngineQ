#include "Framebuffer.hpp"
#include "../Engine.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		GLenum Framebuffer::locations[8] = {
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
			if (depthRbo > 0)
			{
				Bind();
				glDeleteRenderbuffers(1, &depthRbo);
				CreateDepthTesting();
			}
		}

		void Framebuffer::AddTexture(GLuint texture, GLenum location)
		{
			glFramebufferTexture2D(GL_FRAMEBUFFER, location, GL_TEXTURE_2D, texture, 0);
		}

		Framebuffer::Framebuffer(bool depthTesting, std::vector<GLuint>& textures, Engine* engine) : 
			engine(engine), handler(*this, &Framebuffer::Resize)
		{
			glGenFramebuffers(1, &fbo);
			Bind();

			if (depthTesting)
				CreateDepthTesting();

			std::vector<GLenum> attachmentOrder;
			attachmentOrder.reserve(textures.size());
			for (int i = 0; i < textures.size(); ++i)
			{
				AddTexture(textures[i], locations[i]);
				attachmentOrder.push_back(GL_COLOR_ATTACHMENT0 + i);
			}
			if (attachmentOrder.size() > 1)
				glDrawBuffers(attachmentOrder.size(), &attachmentOrder[0]);



			engine->resizeEvent += handler;
		}

		Framebuffer::~Framebuffer()
		{
			if (depthRbo > 0)
				glDeleteRenderbuffers(1, &depthRbo);
			glDeleteFramebuffers(1, &fbo);

			engine->resizeEvent -= handler;
		}

		void Framebuffer::Bind() const
		{
			glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		}

		void Framebuffer::BindDefault()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}
}
