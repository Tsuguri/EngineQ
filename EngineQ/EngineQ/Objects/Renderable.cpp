#include "Renderable.hpp"

#include "../Scripting/ScriptEngine.hpp"
#include "../Graphics/ShaderProperties.hpp"
#include <Resources/Resource.hpp>

#include "Entity.hpp"
#include "Transform.hpp"

namespace EngineQ
{
	Renderable::Renderable(Scripting::ScriptEngine& scriptEngine, Entity& entity, bool enabled)
		: Component{ ComponentType::Renderable, scriptEngine, scriptEngine.GetClass(Scripting::ScriptEngine::Class::Renderable), entity, enabled }
	{
	}

	Renderable::~Renderable()
	{
	}

	void Renderable::SetForwardShader(Resources::Resource<Graphics::Shader> shader)
	{
		this->forwardShader = std::make_unique<EngineShaderProperties>(this->scriptEngine, shader);
	}

	Graphics::ShaderProperties* Renderable::GetForwardShader() const
	{
		return this->forwardShader.get();
	}

	EngineShaderProperties * Renderable::GetForwardShaderEngine() const
	{
		return forwardShader.get();
	}

	void Renderable::SetDeferredShader(Resources::Resource<Graphics::Shader> shader)
	{
		this->deferredShader = std::make_unique<EngineShaderProperties>(this->scriptEngine, shader);
	}

	Graphics::ShaderProperties* Renderable::GetDeferredShader() const
	{
		return this->deferredShader.get();
	}

	EngineShaderProperties * Renderable::GetDeferredShaderEngine() const
	{
		return deferredShader.get();
	}

	Resources::Resource<Graphics::Mesh> Renderable::GetMesh() const
	{
		return mesh;
	}

	void Renderable::SetMesh(Resources::Resource<Graphics::Mesh> mesh)
	{
		this->mesh = mesh;
	}
	Math::Vector3 Renderable::GetPosition()
	{
		return this->GetEntity().GetTransform().GetPosition();
	}
	Math::Matrix4 Renderable::GetGlobalMatrix()
	{
		return this->GetEntity().GetTransform().GetGlobalMatrix();
	}
}
