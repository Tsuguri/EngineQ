#include "API_Application.hpp"

// Other projects
#include "EngineQCommon/Math/Vector2.hpp"

// This project
#include "ScriptEngine.hpp"
#include "EngineQ/Engine.hpp"


namespace EngineQ
{
	namespace Scripting
	{
		void API_Application::API_GetScreenSize(Math::Vector2i& screenSize)
		{
			screenSize = Engine::Get().GetScreenSize();
		}

		void API_Application::API_ApplicationExit()
		{
			Engine::Get().Exit();
		}

		void API_Application::API_Register(ScriptEngine& scriptEngine)
		{
			scriptEngine.API_Register("EngineQ.Application::API_GetScreenSize", API_GetScreenSize);
			scriptEngine.API_Register("EngineQ.Application::API_ApplicationExit", API_ApplicationExit);
		}
	}
}
