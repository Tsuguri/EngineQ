#ifndef ENGINEQ_GRAPHICS_SCRIPTED_RENDERING_UNIT_HPP
#define ENGINEQ_GRAPHICS_SCRIPTED_RENDERING_UNIT_HPP

// Other projects
#include "EngineQRenderer/Graphics/RenderingUnit.hpp"

// This project
#include "ScriptedShaderPass.hpp"
#include "EngineQ/Scripting/Types.hpp"


namespace EngineQ
{
	namespace Graphics
	{
		class DepthRenderer
		{
		private:
			GLuint depthMapFBO;
			Resources::Resource<Texture> depthTexture;
			ScreenDataProvider* screenDataProvider = nullptr;
			Math::Vector2i size;
			EngineShaderProperties shaderProperties;
			bool drawVolumetric = false;

			Utilities::EventHandler<void(int, int)> resizeHandler;
			void ResizeEventHandler(int sizeX, int sizeY);

		public:
			DepthRenderer(Scripting::ScriptEngine& scriptEngine, Resources::Resource<Shader> shader, ScreenDataProvider* dataProvider, bool drawVolumetric);
			~DepthRenderer();

			void RenderDepthMap(const std::vector<Renderable*>& renderables, Math::Matrix4 viewMatrix, Math::Matrix4 projectionMatrix);

			Resources::Resource<Texture> GetDepthTexture();
		};

		class ScriptedRenderingUnit : public RenderingUnit
		{
			class CustomProvider : public ScreenDataProvider
			{
			private:
				Math::Vector2i size;

			public:
				CustomProvider(Math::Vector2i size);

				virtual Math::Vector2i GetScreenSize() const override;
			};

		private:
			class ScriptedShaderPassFactory : public ShaderPassFactory
			{
			private:
				ScriptedRenderingUnit& parent;

			public:
				ScriptedShaderPassFactory(ScriptedRenderingUnit& parent);

				virtual std::unique_ptr<ShaderPass> CreateShaderPass(const Configuration::EffectConfiguration& config) override;
			};

			CustomProvider lightSizer;

			Scripting::ScriptEngine& scriptEngine;
			std::vector<ScriptedShaderPass*> updatable;

			std::unique_ptr<DepthRenderer> forwardDepthRenderer;
			std::unique_ptr<DepthRenderer> backDepthRenderer;
			std::unique_ptr<DepthRenderer> depthRenderer;

			std::unique_ptr<DepthRenderer> light0backDepth;
			std::unique_ptr<DepthRenderer> light0frontDepth;

		public:
			ScriptedRenderingUnit(Scripting::ScriptEngine& scriptEngine, ScreenDataProvider* engine, const Configuration::RenderingUnitConfiguration& configuration);

			void Update();
			virtual void Render(Scene& scene) override;
		};
	}
}

#endif // !ENGINEQ_GRAPHICS_SCRIPTED_RENDERING_UNIT_HPP
