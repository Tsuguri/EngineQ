#ifndef ENGINEQ_GRAPHICS_FRAMEBUFFER_HPP
#define ENGINEQ_GRAPHICS_FRAMEBUFFER_HPP

// Libraries
#include <GL/glew.h>

// Other projects
#include "EngineQCommon/Utilities/Immovable.hpp"
#include "EngineQCommon/Utilities/Event.hpp"

// This project
#include "Configuration/RendererConfiguration.hpp"
#include "Utils/ScreenDataProvider.hpp"


namespace EngineQ
{
	namespace Graphics
	{

		// TODO
		class Framebuffer : private Utilities::Immovable
		{
		private:
			static GLenum locations[8];

			GLuint fbo;
			GLuint depthRbo;

			ScreenDataProvider* screenDataProvider;
			Utilities::EventHandler<void(Math::Vector2i)> handler;
			void Resize(Math::Vector2i size);

			void CreateDepthTesting();

		public:
			void AddTexture(GLuint texture, GLenum location, GLenum texType = GL_TEXTURE_2D);
			Framebuffer(bool depthTesting, std::vector<Resources::Resource<Texture>>& textures, ScreenDataProvider* dataProvider);
			void UnsubscribeFromResize();
			~Framebuffer();

			void Bind() const;

			void ResetDrawBuffer();
			void ResetReadBuffer();

			static void BindDefault();
		};

	}
}
#endif
