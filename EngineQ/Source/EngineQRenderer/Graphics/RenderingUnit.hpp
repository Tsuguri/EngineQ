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

			ScreenDataProvider* screenDataProvider;
			Renderer renderer;
			GLuint quadVao = 0;

			std::vector<std::unique_ptr<ShaderPass>> effects;

			//std::vector<GLuint> textures;
			//std::vector<Configuration::TextureConfiguration> texturesConfigurations;
			std::vector<Resources::Resource<Texture>> texturesResources;

			Utilities::EventHandler<void(int, int)> handler;

			Resources::Resource<Texture> CreateTexture(int width, int height, const Configuration::TextureConfiguration& configuration);

			void Resize(int width, int height);
			std::unique_ptr<Framebuffer> CreateFramebuffer(std::vector<GLuint>& textures, bool depthTesting);
			std::unique_ptr<Framebuffer> CreateFramebuffer(std::vector<Resources::Resource<Texture>>& textures, bool depthTesting);

			void AddEffects(const std::vector<Configuration::EffectConfiguration>& effects, const std::map<std::string, int>& texturesNames);

		protected:
			RenderingUnit(ScreenDataProvider * dataProvider, const Configuration::RenderingUnitConfiguration & configuration, std::unique_ptr<ShaderPassFactory> shaderPassFactory);
			void Initialize(const Configuration::RenderingUnitConfiguration& configuration);

		public:
			RenderingUnit(ScreenDataProvider* screenDataProvider, const Configuration::RenderingUnitConfiguration& configuration);
			~RenderingUnit();

			void Render(Scene& scene);
		};
	}
}

#endif