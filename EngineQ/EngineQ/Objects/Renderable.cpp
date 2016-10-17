#include "Renderable.hpp"

#include "../Scripting/ScriptEngine.hpp"
#include "../Graphics/ShaderProperties.hpp"
#include "../Resources/Resource.hpp"

namespace EngineQ
{
	Renderable::Renderable(Scripting::ScriptEngine& scriptEngine, Entity& entity)
		: Component{ scriptEngine, scriptEngine.GetRenderableClass(), entity }
	{
	}

	ComponentType Renderable::GetType() const
	{
		return ComponentType::Renderable;
	}

	void Renderable::SetForwardShader(Resources::Resource<Graphics::Shader> shader)
	{
		this->forwardShader = std::make_unique<Graphics::ShaderProperties>(this->scriptEngine, shader);
	}

	Graphics::ShaderProperties* Renderable::GetForwardShader() const
	{
		return this->forwardShader.get();
	}

	void Renderable::SetDeferredShader(Resources::Resource<Graphics::Shader> shader)
	{
		this->deferredShader = std::make_unique<Graphics::ShaderProperties>(this->scriptEngine, shader);
	}

	Graphics::ShaderProperties* Renderable::GetDeferredShader() const
	{
		return this->deferredShader.get();
	}

	Graphics::Mesh* Renderable::GetMesh() const
	{
		return mesh;
	}

	void Renderable::SetMesh(Graphics::Mesh* mesh)
	{
		this->mesh = mesh;
	}
}
