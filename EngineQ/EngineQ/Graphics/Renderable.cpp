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

		Shader* Renderable::ForwardShader() const
		{
			return forwardShader;
		}

		void Renderable::ForwardShader(Shader* shader)
		{
			forwardShader = shader;
		}

		Mesh* Renderable::Model() const
		{
			return model;
		}

		void Renderable::Model(EngineQ::Mesh* mesh)
		{
			model = mesh;
		}
	}
}
