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
			static GLenum locations[8];

			GLuint fbo;
			GLuint depthRbo;

			ScreenDataProvider* screenDataProvider;
			Utilities::EventHandler<void(int, int)> handler;
			void Resize(int width, int height);

			void CreateDepthTesting();
		public:
			void AddTexture(GLuint texture, GLenum location);
			Framebuffer(bool depthTesting, std::vector<Resources::Resource<Texture>>& textures, ScreenDataProvider* dataProvider);
			~Framebuffer();

			void Bind() const;

			void ResetDrawBuffer();
			void ResetReadBuffer();

			static void BindDefault();
		};

	}
}
#endif
