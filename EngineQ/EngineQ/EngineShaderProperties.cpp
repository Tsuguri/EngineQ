#include "EngineShaderProperties.hpp"

// This project
#include "Scripting/ScriptEngine.hpp"


namespace EngineQ
{
	EngineShaderProperties::EngineShaderProperties(Scripting::ScriptEngine& scriptEngine, Resources::Resource<Graphics::Shader> shader):
		Object{ scriptEngine, scriptEngine.GetClass(Scripting::ScriptEngine::Class::ShaderProperties) },
		Graphics::ShaderProperties{ shader }
	{
		// Call constructor
		this->scriptEngine.InvokeConstructor(this->GetManagedObject());
	}
}