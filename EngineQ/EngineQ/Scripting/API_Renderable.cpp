#include "API_Renderable.hpp"

#include "../Objects/Renderable.hpp"
#include "../Graphics/ShaderProperties.hpp"
#include "ScriptEngine.hpp"

namespace EngineQ
{
	namespace Scripting
	{
		void API_Renderable::API_GetForwardShader(const Renderable& renderable, MonoObject*& forwardShader)
		{
			forwardShader = renderable.GetForwardShader()->GetManagedObject();
		}

		void API_Renderable::API_GetDeferredShader(const Renderable& renderable, MonoObject*& deferredShader)
		{
			deferredShader = renderable.GetDeferredShader()->GetManagedObject();
		}
		
		void API_Renderable::API_SetForwardShader(Renderable& renderable, Resources::Resource<Graphics::Shader>::Container& shader)
		{
			renderable.SetForwardShader(shader.ToResource());
		}
		
		void API_Renderable::API_SetDeferredShader(Renderable& renderable, Resources::Resource<Graphics::Shader>::Container& shader)
		{
			renderable.SetDeferredShader(shader.ToResource());
		}

		void API_Renderable::API_Register(ScriptEngine& scriptEngine)
		{
			scriptEngine.API_Register("API_GetForwardShader", API_GetForwardShader);
			scriptEngine.API_Register("API_GetDeferredShader", API_GetDeferredShader);
			scriptEngine.API_Register("API_SetForwardShader", API_SetForwardShader);
			scriptEngine.API_Register("API_SetDeferredShader", API_SetDeferredShader);
		}
	}
}