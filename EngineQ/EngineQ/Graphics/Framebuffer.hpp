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

			GLuint fbo = 0;
			GLuint depthRbo=0;

			bool ready = false;

			EventHandler<void(int, int)> handler;

			Engine* engine;

			void AddTexture(int location, GLuint texture);

			void CreateDepthTesting();

			void Init(bool depth, std::vector<GLuint> textures);

			void Resize(int width, int height);

		public:
			Framebuffer(bool depth, std::vector<GLuint> textures, EngineQ::Engine* engine);
			~Framebuffer();

			void Bind() const;
			//remeber that it will automatically bind this framebuffer
			bool Ready();
			static void BindDefault();

		};

	}
}
#endif
