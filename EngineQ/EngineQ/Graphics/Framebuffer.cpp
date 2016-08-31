#include "Framebuffer.hpp"
namespace EngineQ
{
	namespace Graphics
	{
		Framebuffer::Framebuffer()
		{
			glGenFramebuffers(1, &fbo);

		}

		//TODO
		Framebuffer::Framebuffer(FramebufferConfiguration* configuration)
		{
			glGenFramebuffers(1, &fbo);
		}

		Framebuffer::~Framebuffer()
		{
			glDeleteFramebuffers(1, &fbo);
		}

		void Framebuffer::Bind() const
		{
			glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		}

		bool Framebuffer::Ready()
		{
			if (!ready)
			{
				ready = glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
				if (!ready)
					throw "Framebuffer is not complete!";
			}
			return ready;
		}

		void Framebuffer::BindDefault()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		void Framebuffer::AddDepthTesting(int width, int height)
		{
			if (ready)
				throw "framebuffer is already ready";
			Bind();
			glGenRenderbuffers(1, &depthRbo);
			glBindRenderbuffer(GL_RENDERBUFFER, depthRbo);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
			glBindRenderbuffer(GL_RENDERBUFFER, 0);

			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthRbo);
		}

		void Framebuffer::AddColorAttachment(int width, int height, GLint format)
		{
			if (ready)
				throw "framebuffer is already ready";
			Bind();
			glGenTextures(1, &textureColor);
			glBindTexture(GL_TEXTURE_2D, textureColor);

			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColor, 0);
		}

		GLuint Framebuffer::GetColorTexture()
		{
			if (textureColor == 0)
				throw "Color texture does not exist!";
			return textureColor;
		}
	}
}