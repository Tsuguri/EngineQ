#ifndef ENGINEQ_GRAPHICS_SCRIPTED_RENDERER_HPP
#define ENGINEQ_GRAPHICS_SCRIPTED_RENDERER_HPP

// Other projects
#include "EngineQRenderer/Graphics/Renderer.hpp"


namespace EngineQ
{
	namespace Graphics
	{
		class ScriptedRenderer : public Renderer
		{
		public:
			virtual void OnBeforeRender() override;
			virtual void OnAfterRender() override;

			virtual void OnBeforeLightRender(std::size_t index) override;
			virtual void OnAfterLightRender(std::size_t index) override;
		};
	}
}

#endif // !ENGINEQ_GRAPHICS_SCRIPTED_RENDERER_HPP
