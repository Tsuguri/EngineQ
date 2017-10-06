#include "ScriptedRenderer.hpp"

// This project
#include "EngineQ/Engine.hpp"


namespace EngineQ
{
	namespace Graphics
	{
		void ScriptedRenderer::OnBeforeRender()
		{
			Engine::Get().GetProfiler().StartGPU("Scene render", "Renderer");
		}

		void ScriptedRenderer::OnAfterRender()
		{
			Engine::Get().GetProfiler().EndGPU("Scene render", "Renderer");
		}

		void ScriptedRenderer::OnBeforeLightRender(std::size_t index)
		{
			Engine::Get().GetProfiler().StartGPU("Light " + std::to_string(index) + " render", "Renderer");
		}

		void ScriptedRenderer::OnAfterLightRender(std::size_t index)
		{
			Engine::Get().GetProfiler().EndGPU("Light " + std::to_string(index) + " render", "Renderer");
		}
	}
}