#ifndef ENGINEQ_SCRIPTING_API_APPLICATION_HPP
#define ENGINEQ_SCRIPTING_API_APPLICATION_HPP


namespace EngineQ
{
	namespace Scripting
	{
		class ScriptEngine;

		class API_Application
		{
		public:
			static void API_ApplicationExit();

			static void API_Register(ScriptEngine& scriptEngine);
		};
	}
}
#endif