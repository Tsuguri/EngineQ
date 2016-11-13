#include "API_Renderable.hpp"

#include "../Objects/Renderable.hpp"
#include <Graphics/ShaderProperties.hpp>
#include <Graphics/Mesh.hpp>
#include "ScriptEngine.hpp"

namespace EngineQ
{
	namespace Scripting
	{
		void API_Renderable::API_GetForwardShader(const Object& renderableBase, MonoObject*& forwardShader)
		{
			const Renderable& renderable = static_cast<const Renderable&>(renderableBase);

			forwardShader = renderable.GetForwardShaderEngine()->GetManagedObject();
		}

		void API_Renderable::API_GetDeferredShader(const Object& renderableBase, MonoObject*& deferredShader)
		{
			const Renderable& renderable = static_cast<const Renderable&>(renderableBase);

			deferredShader = renderable.GetDeferredShaderEngine()->GetManagedObject();
		}
		
		void API_Renderable::API_GetMesh(const Object& renderableBase, MonoObject*& mesh)
		{
			const Renderable& renderable = static_cast<const Renderable&>(renderableBase);

			const auto& scriptEngine = renderable.GetScriptEngine();

			mesh = scriptEngine.CreateUnhandledObject(scriptEngine.GetClass(ScriptEngine::Class::Mesh), renderable.GetMesh().GetControlBlock());
		}

		void API_Renderable::API_SetMesh(Object& renderableBase, Resources::Resource<Graphics::Mesh>::ControlBlock& mesh)
		{
			Renderable& renderable = static_cast<Renderable&>(renderableBase);

			renderable.SetMesh(mesh.GetResource());
		}

		void API_Renderable::API_UseForwardShader(Object& renderableBase, Resources::Resource<Graphics::Shader>::ControlBlock& shader)
		{
			Renderable& renderable = static_cast<Renderable&>(renderableBase);
			
			renderable.SetForwardShader(shader.GetResource());
		}
		
		void API_Renderable::API_UseDeferredShader(Object& renderableBase, Resources::Resource<Graphics::Shader>::ControlBlock& shader)
		{
			Renderable& renderable = static_cast<Renderable&>(renderableBase);
		
			renderable.SetDeferredShader(shader.GetResource());
		}

		void API_Renderable::API_Register(ScriptEngine& scriptEngine)
		{
			scriptEngine.API_Register("EngineQ.Renderable::API_GetForwardShader", API_GetForwardShader);
			scriptEngine.API_Register("EngineQ.Renderable::API_GetDeferredShader", API_GetDeferredShader);
			scriptEngine.API_Register("EngineQ.Renderable::API_GetMesh", API_GetMesh);
			scriptEngine.API_Register("EngineQ.Renderable::API_SetMesh", API_SetMesh);
			scriptEngine.API_Register("EngineQ.Renderable::API_UseForwardShader", API_UseForwardShader);
			scriptEngine.API_Register("EngineQ.Renderable::API_UseDeferredShader", API_UseDeferredShader);
		}
	}
}