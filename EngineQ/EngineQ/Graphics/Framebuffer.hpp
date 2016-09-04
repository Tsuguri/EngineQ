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
			static GLuint locations[8];

			GLuint fbo = 0;
			GLuint depthRbo=0;

			std::vector<GLuint> textures;
			int size;

			bool ready = false;

			void CreateTexture(int location, TextureConfiguration configuration);

			void AddTexture(int location, GLuint texture);

			void CreateDepthTesting();

			void Init(bool depth, std::vector<GLuint> textures);


		public:
			Framebuffer(bool depth, std::vector<GLuint> textures);
			~Framebuffer();

			void Bind() const;
			//remeber that it will automatically bind this framebuffer
			bool Ready();
			static void BindDefault();
			void Resize(int width, int height);

		};

	}
}
#endif
