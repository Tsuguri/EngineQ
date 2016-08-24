#ifndef ENGINEQ_GRAPHICS_RENDERING_UNIT_HPP
#define ENGINEQ_GRAPHICS_RENDERING_UNIT_HPP

#include <vector>

#include "PostprocessingEffect.hpp"
#include "Framebuffer.hpp"
#include "RendererConfiguration.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		class RenderingUnit
		{
		private:
			std::vector<PostprocessingEffect> effects;
			std::vector<Framebuffer> framebuffers;
			
			bool ValidateConfiguration(RendererConfiguration* configuration);
			void CreateFramebuffers(RendererConfiguration* configuration);
			void CreateEffects(RendererConfiguration* configuration);
			void BindFramebuffers(RendererConfiguration* configuration);

		public:
			RenderingUnit(RendererConfiguration* configuration);

		};
	}
}

#endif