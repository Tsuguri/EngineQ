#include "Renderable.hpp"

namespace EngineQ
{
	namespace Graphics
	{

		Renderable::Renderable(Scripting::ScriptEngine& scriptEngine, Entity& entity)
			: Component{ scriptEngine, scriptEngine.GetCameraClass(), entity }
		{

		}

		ComponentType Renderable::GetType() const
		{
			return ComponentType::Renderable;
		}

		Shader* Renderable::GetForwardShader() const
		{
			return forwardShader;
		}

		void Renderable::SetForwardShader(Shader* shader)
		{
			forwardShader = shader;
		}

		Mesh* Renderable::GetModel() const
		{
			return model;
		}

		void Renderable::SetModel(EngineQ::Mesh* mesh)
		{
			model = mesh;
		}
	}
}
