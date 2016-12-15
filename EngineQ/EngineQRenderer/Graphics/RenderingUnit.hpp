#ifndef ENGINEQ_GRAPHICS_RENDERING_UNIT_HPP
#define ENGINEQ_GRAPHICS_RENDERING_UNIT_HPP

#include <vector>

#include "Scene.hpp"
#include "ShaderPass.hpp"
#include "Framebuffer.hpp"
#include "Configuration/RendererConfiguration.hpp"
#include "Renderer.hpp"

#include "Utils\ScreenDataProvider.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		class RenderingUnit
		{
		private:
			ScreenDataProvider* screenDataProvider;
			Renderer renderer;
			GLuint quadVao = 0;

			std::vector<std::unique_ptr<ShaderPass>> effects;

			//std::vector<GLuint> textures;
			//std::vector<Configuration::TextureConfiguration> texturesConfigurations;
			std::vector<Resources::Resource<Texture>> texturesResources;

			Utilities::EventHandler<void(int, int)> handler;

			void CreateTexture(GLuint* texture, const Configuration::TextureConfiguration& configuration) const;

			Resources::Resource<Texture> CreateTexture(int width, int height, const Configuration::TextureConfiguration& configuration);

			void Resize(int width, int height);
			std::unique_ptr<Framebuffer> CreateFramebuffer(std::vector<GLuint>& textures, bool depthTesting);
			std::unique_ptr<Framebuffer> CreateFramebuffer(std::vector<Resources::Resource<Texture>>& textures, bool depthTesting);
			void Init(const Configuration::RenderingUnitConfiguration&configuration);

		public:
			RenderingUnit(ScreenDataProvider* engine, const Configuration::RenderingUnitConfiguration& configuration);
			~RenderingUnit();

			void Render(Scene& scene);

		};
	}
}

#endif