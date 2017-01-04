#ifndef ENGINEQ_SCRIPTING_API_PREFAB_GENERATOR_HPP
#define ENGINEQ_SCRIPTING_API_PREFAB_GENERATOR_HPP

// Other projects
#include "EngineQCommon/Math/Types.hpp"

// This project
#include "Types.hpp"


namespace EngineQ
{
	namespace Scripting
	{
		class ScriptEngine;

		class API_PrefabGenerator
		{
		public:
			static void API_GenerateCapsule(Math::Real height, Math::Real radius, MonoObject*& mesh);
			static void API_GenerateCube(Math::Real side, MonoObject*& mesh);
			static void API_GenerateQuad(Math::Real side, MonoObject*& mesh);
			static void API_GenerateNoiseTexture(int width, int height, MonoObject*& texture);

			static void API_Register(ScriptEngine& scriptEngine);
		};
	}
}
#endif // !ENGINEQ_SCRIPTING_API_PREFAB_GENERATOR_HPP