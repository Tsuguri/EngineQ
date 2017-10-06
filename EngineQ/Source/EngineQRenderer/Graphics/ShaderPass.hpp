#ifndef ENGINEQ_GRAPHICS_POSTPROCESSING_EFFECT_HPP
#define ENGINEQ_GRAPHICS_POSTPROCESSING_EFFECT_HPP

// Other projects
#include "EngineQCommon/Resources/Resource.hpp"

// This project
#include "Configuration/RendererConfiguration.hpp"
#include "ShaderProperties.hpp"


namespace EngineQ
{
	namespace Graphics
	{
		struct InputConfiguration
		{
			Resources::Resource<Texture> texture;
			std::string Name;

			InputConfiguration(Resources::Resource<Texture> texture, const std::string& name);
		};


		class ShaderPass
		{
		private:
			std::string name;
			std::unique_ptr<ShaderProperties> shaderProperties;
			bool applyShadowData = false;
			std::vector<InputConfiguration> inputTextures;
			std::unique_ptr<Framebuffer> framebuffer;

		protected:
			ShaderPass(std::unique_ptr<ShaderProperties> shaderProperties, const std::string& name);

		public:
			ShaderPass(Resources::Resource<Shader> shader, const std::string& name);
			virtual ~ShaderPass();

			ShaderProperties& GetShaderProperties() const;
			void BindTargetBuffer() const;
			void SetTargetBuffer(std::unique_ptr<Framebuffer>&& buffer);

			const std::string& GetName() const;
			bool GetApplyShadowData() const;
			void SetApplyShadowData(bool val);
			void AddInput(const InputConfiguration& input);

			virtual void BeforeRender();
			virtual void AfterRender();

			virtual void Created();

			// Obsolete
			void Activate(Camera* cam, float time);
		};


		class ShaderPassFactory
		{
		public:
			virtual ~ShaderPassFactory() = default;

			virtual std::unique_ptr<ShaderPass> CreateShaderPass(const Configuration::EffectConfiguration& config, const std::string& name);
		};
	}
}

#endif