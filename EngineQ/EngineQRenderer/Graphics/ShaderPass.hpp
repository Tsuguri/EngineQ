#ifndef ENGINEQ_GRAPHICS_POSTPROCESSING_EFFECT_HPP
#define ENGINEQ_GRAPHICS_POSTPROCESSING_EFFECT_HPP

#include <Resources/Resource.hpp>

#include "Configuration/RendererConfiguration.hpp"
#include  "ShaderProperties.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		struct InputConfiguration
		{
			GLuint Texture;
			std::string Name;

			InputConfiguration(GLuint texture,std::string name);
		};


		class ShaderPass
		{
			//Resources::Resource<Shader> shader;
			ShaderProperties shader;
			bool ApplyShadowData = false;
			std::vector<InputConfiguration> inputTextures;
			std::unique_ptr<Framebuffer> framebuffer;
		public:
			static GLenum textureLocations[10];
			ShaderPass(Resources::Resource<Shader> shader);

			void BindTextures();
			void UnbindTextures();

			ShaderProperties& GetShaderproperties();
			void BindTargetBuffer() const;
			void SetTargetBuffer(std::unique_ptr<Framebuffer>&& buffer);

			bool GetApplyShadowData();
			void SetApplyShadowData(bool val);
			void AddInput(const InputConfiguration& input);

			void Activate(Camera* cam, float time);

		};
	}
}

#endif