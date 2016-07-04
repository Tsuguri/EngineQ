#include "Camera.hpp"

namespace EngineQ
{
	Camera::Camera(Scripting::ScriptEngine& scriptEngine, Entity& entity)
		: Component{ scriptEngine, scriptEngine.GetCameraClass(), entity }
	{
		// TMP
		scriptEngine.InvokeConstructor(GetManagedObject());
	}

	ComponentType Camera::GetType() const
	{
		return ComponentType::Camera;
	}
}