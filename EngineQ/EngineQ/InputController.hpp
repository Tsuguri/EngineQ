#ifndef ENGINEQ_INPUTCONTROLLER_HPP
#define ENGINEQ_INPUTCONTROLLER_HPP
#include "Math/Vector2.hpp"
#include "Scripting/ScriptEngine.hpp"

namespace EngineQ
{
	namespace Scripting
	{
		class ScriptEngine;
	}
	class InputController
	{
		friend class Engine;

		bool keys[512];
		bool mouseButtons[10];
		Scripting::ScriptEngine* se=nullptr;
		Scripting::ScriptMethod keyEventMethod=nullptr;
		Scripting::ScriptMethod mouseButtonEventMethod=nullptr;

		Math::Vector2 cursorPos;
		Math::Vector2 cursorDeltaPos;

		void KeyAction(int key, int scancode, int action, int mode);
		void MouseButtonAction(int button, int action, int mode);
		void MouseMoveAction(double xpos, double ypos);
	public:
		InputController();
		void InitMethods(Scripting::ScriptEngine* se);
		bool isButtonDown(int keyCode);
		bool isMouseButtonDown(int keyCode);
		Math::Vector2 GetMousePosition() const;
		Math::Vector2 GetMouseDeltaPosition() const;
		void ClearDelta();
	};
}

#endif