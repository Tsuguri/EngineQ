#include "API_Application.hpp"

// This project
#include "ScriptEngine.hpp"
#include "EngineQ/Engine.hpp"


namespace EngineQ
{
	namespace Scripting
	{
		void API_Application::API_ApplicationExit()
		{
			Engine::Get().Exit();
		}

		void API_Application::API_Register(ScriptEngine& scriptEngine)
		{
			scriptEngine.API_Register("EngineQ.Application::API_ApplicationExit", API_ApplicationExit);
		}
	}
}
