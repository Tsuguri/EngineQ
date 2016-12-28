#include "Renderable.hpp"

// Other projects
#include "EngineQCommon/Resources/Resource.hpp"
#include "EngineQRenderer/Graphics/ShaderProperties.hpp"
#include "EngineQRenderer/Graphics/Renderable.hpp"

// This project
#include "Entity.hpp"
#include "Transform.hpp"
#include "EngineQ/Logger.hpp"
#include "EngineQ/Scripting/ScriptEngine.hpp"


namespace EngineQ
{
	Renderable::Renderable(Scripting::ScriptEngine& scriptEngine, Entity& entity, bool enabled)
		: Component{ ComponentType::Renderable, scriptEngine, scriptEngine.GetClass(Scripting::ScriptEngine::Class::Renderable), entity, enabled }
	{
	}

	Renderable::~Renderable()
	{
		Logger::LogMessage("  Destroying Renderable\n");
		Logger::LogMessage("    DeferredShader ", this->deferredShader.get(), "\n");
		Logger::LogMessage("    ForwardShader ", this->forwardShader.get(), "\n");
		Logger::LogMessage("    Mesh ", &(*this->mesh), "\n");
	}

	void Renderable::SetForwardShader(Resources::Resource<Graphics::Shader> shader)
	{
		this->forwardShader = std::make_unique<EngineShaderProperties>(this->scriptEngine, shader);
	}

	EngineShaderProperties* Renderable::GetForwardShader() const
	{
		return forwardShader.get();
	}

	void Renderable::SetDeferredShader(Resources::Resource<Graphics::Shader> shader)
	{
		this->deferredShader = std::make_unique<EngineShaderProperties>(this->scriptEngine, shader);
	}

	EngineShaderProperties* Renderable::GetDeferredShader() const
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

	void Graphics::Renderable::SetCastShadows(bool val)
	{
		castShadows = val;
	}

	bool Graphics::Renderable::GetCastShadows() const
	{
		return castShadows;
	}

	void Graphics::Renderable::SetReceiveShadows(bool val)
	{
		receiveShadows = val;
	}

	bool Graphics::Renderable::GetReceiveShadows() const
	{
		return receiveShadows;
	}
}
