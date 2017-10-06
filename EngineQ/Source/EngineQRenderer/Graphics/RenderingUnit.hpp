#ifndef ENGINEQ_GRAPHICS_RENDERING_UNIT_HPP
#define ENGINEQ_GRAPHICS_RENDERING_UNIT_HPP

// Standard includes
#include <vector>

// This project
#include "Scene.hpp"
#include "ShaderPass.hpp"
#include "Framebuffer.hpp"
#include "Renderer.hpp"
#include "Utils/ScreenDataProvider.hpp"
#include "Configuration/RendererConfiguration.hpp"


namespace EngineQ
{
	namespace Graphics
	{
		class RenderingUnit
		{
		private:
			std::unique_ptr<ShaderPassFactory> shaderPassFactory;
			std::unique_ptr<RendererFactory> rendererFactory;

			ScreenDataProvider* screenDataProvider;
			std::unique_ptr<Renderer> renderer;
			GLuint quadVao = 0;

			std::vector<std::unique_ptr<ShaderPass>> effects;

			std::vector<Resources::Resource<Texture>> texturesResources;

			Utilities::EventHandler<void(Math::Vector2i)> handler;

			Resources::Resource<Texture> CreateTexture(int width, int height, const Configuration::TextureConfiguration& configuration);

			void Resize(Math::Vector2i size);
			std::unique_ptr<Framebuffer> CreateFramebuffer(std::vector<Resources::Resource<Texture>>& textures, bool depthTesting);

			void AddEffects(const std::vector<Configuration::EffectConfiguration>& effects, const std::string& nameBase, const std::map<std::string, int>& texturesNames);

		protected:
			RenderingUnit(ScreenDataProvider * dataProvider, const Configuration::RenderingUnitConfiguration & configuration, std::unique_ptr<ShaderPassFactory> shaderPassFactory, std::unique_ptr<RendererFactory> rendererFactory);
			void Initialize(const Configuration::RenderingUnitConfiguration& configuration);

		public:
			RenderingUnit(ScreenDataProvider* screenDataProvider, const Configuration::RenderingUnitConfiguration& configuration);
			virtual ~RenderingUnit();

			void Render(Scene& scene);
		};
	}
}

#endif