#include "API_EffectController.hpp"

// This project
#include "ScriptEngine.hpp"
#include "EngineQ/Engine.hpp"
#include "EngineQ/EngineShaderProperties.hpp"
#include "EngineQ/Graphics/ScriptedShaderPass.hpp"


namespace EngineQ
{
	namespace Scripting
	{
		void API_EffectController::API_GetShaderProperties(const Object& effectBase, MonoObject*& shaderProperties)
		{
			const auto& effect = static_cast<const Graphics::ScriptedShaderPass&>(effectBase);

			shaderProperties = effect.GetShaderProperties().GetManagedObject();
		}
		
		void API_EffectController::API_GetScene(const Object&, MonoObject*& scene)
		{
			scene = EngineQ::Engine::Get().GetCurrentScene().GetManagedObject();
		}
		
		void API_EffectController::API_Register(ScriptEngine& scriptEngine)
		{
			scriptEngine.API_Register("EngineQ.EffectController::API_GetShaderProperties", API_GetShaderProperties);
			scriptEngine.API_Register("EngineQ.EffectController::API_GetScene", API_GetScene);
		}
	}
}