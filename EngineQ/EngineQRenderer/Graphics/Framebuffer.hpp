#ifndef ENGINEQ_GRAPHICS_FRAMEBUFFER_HPP
#define ENGINEQ_GRAPHICS_FRAMEBUFFER_HPP

#include <Libraries/GL/glew.h>

#include <Utilities/Immovable.hpp>
#include <Utilities/Event.hpp>
#include "Configuration/RendererConfiguration.hpp"


#include "Utils\ScreenDataProvider.hpp"

namespace EngineQ
{
	namespace Graphics
	{

		// TODO
		class Framebuffer : private Utilities::Immovable
		{
			static GLenum locations[8];

			GLuint fbo;
			GLuint depthRbo;

			ScreenDataProvider* screenDataProvider;
			Utilities::EventHandler<void(int, int)> handler;

			void CreateDepthTesting();
			void Resize(int width, int height);
			void AddTexture(GLuint texture, GLenum location);
		public:
			Framebuffer(bool depthTesting, std::vector<GLuint>& textures, ScreenDataProvider* dataProvider);
			Framebuffer(bool depthTesting, std::vector<Resources::Resource<Texture>>& textures, ScreenDataProvider* dataProvider);
			Framebuffer(GLuint texture, ScreenDataProvider* dataProvider);
			~Framebuffer();

			void Bind() const;

			static void BindDefault();
		};

	}
}
#endif
