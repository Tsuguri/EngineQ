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
		class Framebuffer : private EngineQ::Utilities::Immovable
		{
			static GLenum locations[8];

			GLuint fbo;
			GLuint depthRbo;

			Engine* engine;
			EventHandler<void(int, int)> handler;

			void CreateDepthTesting();
			void Resize(int width, int height);
			void AddTexture(GLuint texture, GLenum location);
		public:
			Framebuffer(bool depthTesting,std::vector<GLuint>& textures,Engine* engine);
			~Framebuffer();

			void Bind() const;

			static void BindDefault();
		};

	}
}
#endif
