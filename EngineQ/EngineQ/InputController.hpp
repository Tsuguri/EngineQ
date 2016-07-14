#ifndef ENGINEQ_INPUTCONTROLLER_HPP
#define ENGINEQ_INPUTCONTROLLER_HPP

namespace EngineQ
{
	class InputController
	{
		friend class Engine;

		bool keys[512];
		bool mouseButtons[10];

		void KeyAction(int key, int scancode, int action, int mode);
	public:
		InputController();
		bool isButtonDown(int keyCode);
		bool isMouseButtonDown(int keyCode);
	};
}

#endif