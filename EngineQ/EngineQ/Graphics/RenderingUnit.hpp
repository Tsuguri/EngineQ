#ifndef ENGINEQ_GRAPHICS_RENDERING_UNIT_HPP
#define ENGINEQ_GRAPHICS_RENDERING_UNIT_HPP

#include <vector>

#include "../Scene.hpp"
#include "PostprocessingEffect.hpp"
#include "Framebuffer.hpp"
#include "RendererConfiguration.hpp"
#include "ForwardRenderer.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		class RenderingUnit
		{
		private:
			Engine* engine;
			ForwardRenderer* renderer=nullptr;
			GLuint quadVao=0;

			std::vector<std::shared_ptr <PostprocessingEffect>> effects;
			std::vector<std::shared_ptr<Framebuffer>> framebuffers;

			std::vector<GLuint> textures;
			std::vector<TextureConfiguration> texturesConfigurations;
			
			EventHandler<void(int, int)> handler;

			void CreateTexture(GLuint* texture, TextureConfiguration configuration);

			void Resize(int width, int height);
			void ResizeTexture(GLuint texture, int width, int height);
			std::shared_ptr<Framebuffer> CreateFramebuffer(std::vector<GLuint>& textures, bool depthTesting);
			void Init(RenderingUnitConfiguration* configuration);
		public:

			RenderingUnit(Engine* engine, RenderingUnitConfiguration* configuration);
			~RenderingUnit();

			void Render(Scene* scene);

		};
	}
}

#endif