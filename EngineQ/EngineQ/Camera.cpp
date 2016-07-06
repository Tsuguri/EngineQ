#include "Camera.hpp" 

namespace EngineQ
{
	Camera::Camera(Scripting::ScriptEngine& scriptEngine, Entity& entity)
		: Component{ scriptEngine, scriptEngine.GetCameraClass(), entity }
	{

	}

	ComponentType Camera::GetType() const
	{
		return ComponentType::Camera;
	}
}