#ifndef ENGINEQ_GRAPHICS_FRAMEBUFFER_HPP
#define ENGINEQ_GRAPHICS_FRAMEBUFFER_HPP

#include "../Libraries/GL/glew.h"

#include "../Utilities/Immovable.hpp"
#include "RendererConfiguration.hpp"
#include "../Utilities/Event.hpp"
#include "../Engine.hpp"

namespace EngineQ
{
	namespace Graphics
	{

		// TODO
		class Framebuffer : public EngineQ::Utilities::Immovable
		{
			static GLuint locations[8];
			//GLuint textureColor;
			GLuint fbo;
			GLuint depthRbo;

			Engine* engine;
			EventHandler<void(int, int)> handler;

			void CreateDepthTesting();
			void Resize(int width, int height);
		public:
			Framebuffer(Engine* engine);
			~Framebuffer();

			void Bind();

			//GLuint GetTexture();

			void SetTexture(GLuint tex);


			static void BindDefault();

		};

	}
}
#endif
