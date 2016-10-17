#ifndef ENGINEQ_SCRIPTING_API_RENDERABLE_HPP
#define ENGINEQ_SCRIPTING_API_RENDERABLE_HPP

#include "Types.hpp"
#include "../Objects/Types.hpp"
#include "../Graphics/Types.hpp"

#include "../Resources/Resource.hpp"

namespace EngineQ
{
	namespace Scripting
	{
		class API_Renderable
		{
		public:
			static void API_GetForwardShader(const Renderable& renderable, MonoObject*& forwardShader);
			static void API_GetDeferredShader(const Renderable& renderable, MonoObject*& deferredShader);
			static void API_SetForwardShader(Renderable& renderable, Resources::Resource<Graphics::Shader>::Container& shader);
			static void API_SetDeferredShader(Renderable& renderable, Resources::Resource<Graphics::Shader>::Container& shader);

			static void API_Register(ScriptEngine& scriptEngine);
		};
	}
}

#endif // !ENGINEQ_SCRIPTING_API_RENDERABLE_HPP
