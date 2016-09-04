#ifndef ENGINEQ_GRAPHICS_POSTPROCESSING_EFFECT_HPP
#define ENGINEQ_GRAPHICS_POSTPROCESSING_EFFECT_HPP

#include "RendererConfiguration.hpp"
#include "Framebuffer.hpp"
#include "Shader.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		struct InputConfiguration
		{
			GLenum Position;
			GLuint Texture;

			InputConfiguration(GLuint position, GLuint texture);
		};


		class PostprocessingEffect
		{
			

			std::shared_ptr<Shader> shader;

			std::vector<InputConfiguration> inputTextures;
			Framebuffer* framebuffer=nullptr;
		public:
			static GLenum textureLocations[10];
			PostprocessingEffect(std::shared_ptr<Shader> shader);

			void BindTextures();
			void UnbindTextures();

			void BindTargetBuffer() const;
			void SetTargetBuffer(Framebuffer* buffer);

			void AddInput(InputConfiguration input);

			void Activate() const;

		};
	}
}

#endif