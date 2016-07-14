#ifndef ENGINEQ_SCRIPTING_API_INPUT_HPP
#define ENGINEQ_SCRIPTING_API_INPUT_HPP

#include "ScriptEngine.hpp"
#include "../Engine.hpp"

namespace EngineQ
{
	namespace Scripting
	{
		class API_Input
		{
		public:
			static void API_KeyPresed(int keyCode,bool& result);

			static void API_MouseButtonDown(int buttonCode, bool& result);

			static void API_Register(ScriptEngine& scriptEngine);
		};
	}
}

#endif