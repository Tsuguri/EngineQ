#include "Framebuffer.hpp"
#include "../Engine.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		void Framebuffer::CreateDepthTesting()
		{
			glGenRenderbuffers(1, &depthRbo);
			glBindRenderbuffer(GL_RENDERBUFFER, depthRbo);
			auto size = EngineQ::Engine::Get()->GetScreenSize();
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.X, size.Y);
			glBindRenderbuffer(GL_RENDERBUFFER, 0);

			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthRbo);
		}

		void Framebuffer::Resize(int width, int height)
		{
			std::cout << "framebuffer resized :)" << std::endl;
			Bind();
			if (depthRbo > 0)
			{
				glDeleteRenderbuffers(1, &depthRbo);
				CreateDepthTesting();
			}
			if(textureColor>0)
			{
				glBindTexture(GL_TEXTURE_2D, textureColor);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
			}

		}

		void Framebuffer::Init()
		{
			glGenFramebuffers(1, &fbo);
			EngineQ::Engine::Get()->resizeEvent += handler;
		}

		Framebuffer::Framebuffer() : handler(*this, &Framebuffer::Resize)//handler([&](int a, int b) {Resize(a, b); })
		{
			Init();
		}

		//TODO
		Framebuffer::Framebuffer(FramebufferConfiguration* configuration) : texturesConfiguration(configuration->Textures), size(configuration->Textures.size()), textures(configuration->Textures.size(), 0), handler(*this, &Framebuffer::Resize)
		{
			Init();
		}

		Framebuffer::~Framebuffer()
		{
			EngineQ::Engine::Get()->resizeEvent -= handler;
			if (textures.size() > 0)
				glDeleteTextures(textures.size(), &textures[0]);
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

		void Framebuffer::AddDepthTesting()
		{
			if (ready)
				throw "framebuffer is already ready";
			Bind();
			CreateDepthTesting();
		}

		void Framebuffer::AddColorAttachment( GLint format)
		{
			if (ready)
				throw "framebuffer is already ready";
			Bind();
			auto size =  EngineQ::Engine::Get()->GetScreenSize();

			glGenTextures(1, &textureColor);
			glBindTexture(GL_TEXTURE_2D, textureColor);

			glTexImage2D(GL_TEXTURE_2D, 0, format, size.X,size.Y, 0, format, GL_UNSIGNED_BYTE, nullptr);

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
