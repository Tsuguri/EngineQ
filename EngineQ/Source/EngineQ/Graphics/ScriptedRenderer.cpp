#include "ScriptedRenderer.hpp"

// This project
#include "EngineQ/Engine.hpp"


namespace EngineQ
{
	namespace Graphics
	{
		void ScriptedRenderer::OnBeforeRender()
		{
			Engine::Get().GetProfiler().Start("Scene render", "Renderer");
		}

		void ScriptedRenderer::OnAfterRender()
		{
			glFinish();
			Engine::Get().GetProfiler().End("Scene render", "Renderer");
		}

		void ScriptedRenderer::OnBeforeLightRender(std::size_t index)
		{
			Engine::Get().GetProfiler().Start("Light " + std::to_string(index) + " render", "Renderer");
		}

		void ScriptedRenderer::OnAfterLightRender(std::size_t index)
		{
			glFinish();
			Engine::Get().GetProfiler().End("Light " + std::to_string(index) + " render", "Renderer");
		}
	}
}