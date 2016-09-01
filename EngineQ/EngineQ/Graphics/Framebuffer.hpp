#ifndef ENGINEQ_GRAPHICS_FRAMEBUFFER_HPP
#define ENGINEQ_GRAPHICS_FRAMEBUFFER_HPP

#include "../Libraries/GL/glew.h"

#include "../Utilities/Immovable.hpp"
#include "RendererConfiguration.hpp"
#include "../Utilities/Event.hpp"

namespace EngineQ
{
	namespace Graphics
	{

		// TODO
		class Framebuffer : public EngineQ::Utilities::Immovable
		{
			GLuint fbo = 0;
			GLuint textureColor = 0;
			GLuint depthRbo=0;

			std::vector<TextureConfiguration> texturesConfiguration;
			std::vector<GLuint> textures;
			int size;

			bool ready = false;

			EventHandler<void(int, int)> handler;


			void CreateTexture(int location, TextureConfiguration configuration);
			void DeleteTexture(int location);
			void ResetTextures();

			void CreateDepthTesting();

			void Init(FramebufferConfiguration* configuration);
		public:
			Framebuffer();
			Framebuffer(EngineQ::Graphics::FramebufferConfiguration* configuration);
			~Framebuffer();

			void Bind() const;
			//remeber that it will automatically bind this framebuffer
			bool Ready();
			static void BindDefault();

			//remeber that it will automatically bind this framebuffer
			void AddDepthTesting();
			void AddColorAttachment(GLint format = GL_RGB);
			void Resize(int width, int height);
			GLuint GetColorTexture(int location);
		};

	}
}
#endif
