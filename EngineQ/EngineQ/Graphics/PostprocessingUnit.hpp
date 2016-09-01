#ifndef ENGINEQ_GRAPHICS_RENDERING_UNIT_HPP
#define ENGINEQ_GRAPHICS_RENDERING_UNIT_HPP

#include <vector>

#include "../Scene.hpp"
#include "PostprocessingEffect.hpp"
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
			ForwardRenderer* renderer;


			std::vector<PostprocessingEffect> effects;
			std::vector<Framebuffer*> framebuffers;
			
			bool ValidateConfiguration(RendererConfiguration* configuration);
			void CreateFramebuffers(RendererConfiguration* configuration);
			void CreateEffects(RendererConfiguration* configuration);
			void BindFramebuffers(RendererConfiguration* configuration);

		public:
			RenderingUnit(RendererConfiguration* configuration);

			void Render(Scene* scene);

		};
	}
}

#endif