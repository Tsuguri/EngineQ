#ifndef ENGINEQ_SCRIPTING_API_APPLICATION_HPP
#define ENGINEQ_SCRIPTING_API_APPLICATION_HPP

// Other projects
#include "EngineQCommon/Math/Types.hpp"


namespace EngineQ
{
	namespace Scripting
	{
		class ScriptEngine;

		class API_Application
		{
		public:
			static void API_GetScreenSize(Math::Vector2i& screenSize);
			static void API_ApplicationExit();

			static void API_Register(ScriptEngine& scriptEngine);
		};
	}
}

#endif // ENGINEQ_SCRIPTING_API_APPLICATION_HPP