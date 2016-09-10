#ifndef ENGINEQ_GRAPHICS_RENDERING_UNIT_HPP
#define ENGINEQ_GRAPHICS_RENDERING_UNIT_HPP

#include <vector>

#include "../Scene.hpp"
#include "ShaderPass.hpp"
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

			std::vector<std::unique_ptr<ShaderPass>> effects;

			std::vector<GLuint> textures;
			std::vector<TextureConfiguration> texturesConfigurations;
			
			EventHandler<void(int, int)> handler;

			void CreateTexture(GLuint* texture, const TextureConfiguration& configuration) const;

			void Resize(int width, int height);
			std::unique_ptr<Framebuffer> CreateFramebuffer(std::vector<GLuint>& textures, bool depthTesting);
			void Init(const RenderingUnitConfiguration&configuration);
		public:

			RenderingUnit(Engine* engine,const RenderingUnitConfiguration& configuration);
			~RenderingUnit();

			void Render(Scene* scene);

		};
	}
}

#endif