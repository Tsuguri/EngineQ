#ifndef ENGINEQ_INPUTCONTROLLER_HPP
#define ENGINEQ_INPUTCONTROLLER_HPP
#include "Math/Vector2.hpp"

namespace EngineQ
{
	class InputController
	{
		friend class Engine;

		bool keys[512];
		bool mouseButtons[10];

		Math::Vector2 cursorPos;
		Math::Vector2 cursorDeltaPos;

		void KeyAction(int key, int scancode, int action, int mode);
		void MouseButtonAction(int button, int action, int mode);
		void MouseMoveAction(double xpos, double ypos);
	public:
		InputController();
		bool isButtonDown(int keyCode);
		bool isMouseButtonDown(int keyCode);
		Math::Vector2 GetMousePosition() const;
	};
}

#endif