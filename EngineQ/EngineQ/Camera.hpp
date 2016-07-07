#ifndef ENGINEQ_CAMERA_HPP
#define ENGINEQ_CAMERA_HPP

#include "Component.hpp" 

namespace EngineQ
{
	class Camera : public Component
	{
	public:
		Camera(Scripting::ScriptEngine& scriptEngine, Entity& entity);

		virtual ComponentType GetType() const override;
	};
}

#endif // !ENGINEQ_CAMERA_HPP
