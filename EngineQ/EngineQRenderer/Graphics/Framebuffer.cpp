#include "Framebuffer.hpp"

// This project
#include "Texture.hpp"


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
			auto size = screenDataProvider->GetScreenSize();
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

		Framebuffer::Framebuffer(bool depthTesting, std::vector<GLuint>& textures, ScreenDataProvider* dataProvider) :
			screenDataProvider(dataProvider), handler(*this, &Framebuffer::Resize)
		{
			glGenFramebuffers(1, &fbo);
			Bind();

			if (depthTesting)
				CreateDepthTesting();

			std::vector<GLenum> attachmentOrder;
			attachmentOrder.reserve(textures.size());
			for (std::size_t i = 0; i < textures.size(); ++i)
			{
				AddTexture(textures[i], locations[i]);
				attachmentOrder.push_back(GL_COLOR_ATTACHMENT0 + static_cast<GLuint>(i));
			}
			if (attachmentOrder.size() > 1)
				glDrawBuffers(static_cast<GLsizei>(attachmentOrder.size()), &attachmentOrder[0]);
			screenDataProvider->resizeEvent += handler;
		}

		Framebuffer::Framebuffer(bool depthTesting, std::vector<Resources::Resource<Texture>>& textures, ScreenDataProvider* dataProvider) :
			screenDataProvider(dataProvider), handler(*this, &Framebuffer::Resize)
		{
			glGenFramebuffers(1, &fbo);
			Bind();

			if (depthTesting)
				CreateDepthTesting();

			std::vector<GLenum> attachmentOrder;
			attachmentOrder.reserve(textures.size());
			for (std::size_t i = 0; i < textures.size(); ++i)
			{
				AddTexture(textures[i]->GetTextureID(), locations[i]);
				attachmentOrder.push_back(GL_COLOR_ATTACHMENT0 + static_cast<GLuint>(i));
			}
			if (attachmentOrder.size() > 1)
				glDrawBuffers(static_cast<GLsizei>(attachmentOrder.size()), &attachmentOrder[0]);
			screenDataProvider->resizeEvent += handler;
		}

		Framebuffer::Framebuffer(GLuint texture, ScreenDataProvider * dataProvider) : screenDataProvider(dataProvider),handler(*this,&Framebuffer::Resize)
		{
			glGenFramebuffers(1, &fbo);
			Bind();

			std::vector<GLenum> attachmentOrder;

			AddTexture(texture, locations[0]);

			//should not be needed as only one texture is used
			//attachmentOrder.push_back(GL_COLOR_ATTACHMENT0);

			//glDrawBuffers(GL_COLOR_ATTACHMENT0, &attachmentOrder[0]);



			screenDataProvider->resizeEvent += handler;
		}

		Framebuffer::~Framebuffer()
		{
			if (depthRbo > 0)
				glDeleteRenderbuffers(1, &depthRbo);
			glDeleteFramebuffers(1, &fbo);

			screenDataProvider->resizeEvent -= handler;
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
