#include "Model.hpp"

namespace EngineQ
{
	Camera::Camera(Scripting::ScriptEngine& scriptEngine, Entity& entity)
		: Component{ scriptEngine, scriptEngine.GetCameraClass(), entity }, fov(45.0f), aspectRatio(4 / 3.0f)
	{

	}

	ComponentType Model::GetType() const
	{
		return ComponentType::Camera;
	}
}