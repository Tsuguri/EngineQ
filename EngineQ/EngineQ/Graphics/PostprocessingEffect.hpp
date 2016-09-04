#ifndef ENGINEQ_GRAPHICS_POSTPROCESSING_EFFECT_HPP
#define ENGINEQ_GRAPHICS_POSTPROCESSING_EFFECT_HPP

#include "RendererConfiguration.hpp"
#include "Framebuffer.hpp"
#include "Shader.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		class PostprocessingEffect
		{
			std::shared_ptr<Shader> shader;
		public:
			PostprocessingEffect(int shaderId);
			PostprocessingEffect(std::shared_ptr<Shader> shader);
			PostprocessingEffect(EffectConfiguration* conf);

			void BindTextures();
			void BindTargetBuffer();
			void SetTargetBuffer(Framebuffer* buffer);

			void Activate();

		};
	}
}

#endif