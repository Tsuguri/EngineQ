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
			std::cout << "framebuffer resized :)" << std::endl;
			Bind();
			if (depthRbo > 0)
			{
				glDeleteRenderbuffers(1, &depthRbo);
				CreateDepthTesting();
			}
			if (textureColor > 0)
			{
				glBindTexture(GL_TEXTURE_2D, textureColor);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
			}

		}

		void Framebuffer::Init(FramebufferConfiguration* configuration)
		{
			glGenFramebuffers(1, &fbo);
			Bind();
			int j = 0;
			for (auto i : configuration->Textures)
			{
				texturesConfiguration.push_back(i);
				CreateTexture(j, i);
				j++;
			}
			if (configuration->DepthTesting)
				CreateDepthTesting();

			Engine::Get()->resizeEvent += handler;
		}

		Framebuffer::Framebuffer() : handler(*this, &Framebuffer::Resize), textures(1, 0), size(1), texturesConfiguration(1)
		{
			FramebufferConfiguration conf;
			conf.DepthTesting = true;
			conf.Textures.push_back(TextureConfiguration());

			Init(&conf);
		}

		//TODO
		Framebuffer::Framebuffer(FramebufferConfiguration* configuration) : texturesConfiguration(configuration->Textures.size()), size(configuration->Textures.size()), textures(configuration->Textures.size(), 0), handler(*this, &Framebuffer::Resize)
		{
			Init(configuration);
		}

		Framebuffer::~Framebuffer()
		{
			Engine::Get()->resizeEvent -= handler;
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

		GLuint Framebuffer::GetColorTexture(int location)
		{
			if (textures.size()<location || textures[location] == 0)
				throw "Color texture does not exist!";
			return textures[location];
		}
	}
}
