#ifndef ENGINEQ_SCRIPTING_API_EFFECT_CONTROLLER_HPP
#define ENGINEQ_SCRIPTING_API_EFFECT_CONTROLLER_HPP

// This project
#include "Types.hpp"
#include "EngineQ/Objects/Types.hpp"


namespace EngineQ
{
	namespace Scripting
	{
		class API_EffectController
		{
		public:
			static void API_GetShaderProperties(const Object& effectBase, MonoObject*& shaderProperties);
			static void API_GetScene(const Object& effectBase, MonoObject*& scene);

			static void API_Register(ScriptEngine& scriptEngine);
		};
	}
}

#endif // !ENGINEQ_SCRIPTING_API_EFFECT_CONTROLLER_HPP
