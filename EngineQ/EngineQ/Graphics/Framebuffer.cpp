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


		void Framebuffer::CreateTexture(int location, TextureConfiguration configuration)
		{
			glGenTextures(1, &textures[location]);
			glBindTexture(GL_TEXTURE_2D, textures[location]);
			auto size = Engine::Get()->GetScreenSize();
			glTexImage2D(GL_TEXTURE_2D, 0, configuration.Format, size.X, size.Y, 0, configuration.Format, configuration.DataType, nullptr);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glFramebufferTexture2D(GL_FRAMEBUFFER, locations[location], GL_TEXTURE_2D, textures[location], 0);
		}

		void Framebuffer::AddTexture(int location, GLuint texture)
		{
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);//locations[location]
		}

		void Framebuffer::CreateDepthTesting()
		{
			glGenRenderbuffers(1, &depthRbo);
			glBindRenderbuffer(GL_RENDERBUFFER, depthRbo);
			auto size = Engine::Get()->GetScreenSize();
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


		void Framebuffer::Init(bool depth, std::vector<GLuint> textures)
		{
			glGenBuffers(1, &fbo);
			Bind();
			int j = 0;
			for (auto i : textures)
				AddTexture(j++, i);

			if (depth)
				CreateDepthTesting();

			engine->resizeEvent += handler;
		}


		Framebuffer::Framebuffer(bool depth, std::vector<GLuint> textures, EngineQ::Engine* engine): handler(*this, &Framebuffer::Resize), engine(engine)
		{
			Init(depth, textures);
		}

		Framebuffer::~Framebuffer()
		{
			engine->resizeEvent -= handler;

			//delete depthRbo?
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
	}
}
