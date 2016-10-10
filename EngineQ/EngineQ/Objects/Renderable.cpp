#include "Renderable.hpp"

#include "../Scripting/ScriptEngine.hpp"

namespace EngineQ
{
	Renderable::Renderable(Scripting::ScriptEngine& scriptEngine, Entity& entity)
		: Component{ scriptEngine, scriptEngine.GetCameraClass(), entity }
	{
	}

	ComponentType Renderable::GetType() const
	{
		return ComponentType::Renderable;
	}

	Graphics::Shader* Renderable::GetForwardShader() const
	{
		return forwardShader.get();
	}

	Graphics::Shader* Renderable::GetDeferredShader() const
	{
		return deferredShader.get();
	}

	void Renderable::SetForwardShader(std::shared_ptr<Graphics::Shader> shader)
	{
		forwardShader = shader;
	}

	void Renderable::SetDeferredShader(std::shared_ptr<Graphics::Shader> shader)
	{
		deferredShader = shader;
	}

	Graphics::Mesh* Renderable::GetModel() const
	{
		return model;
	}

	void Renderable::SetModel(Graphics::Mesh* mesh)
	{
		model = mesh;
	}
}
