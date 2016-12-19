#ifndef ENGINEQ_SHADERPROPERTIES_HPP
#define ENGINEQ_SHADERPROPERTIES_HPP

// Other projects
#include "EngineQRenderer/Graphics/ShaderProperties.hpp"

// This project
#include "Objects/Object.hpp"


namespace EngineQ
{
	class EngineShaderProperties : public Object, public Graphics::ShaderProperties
	{
	public:
		EngineShaderProperties(Scripting::ScriptEngine& scriptEngine, Resources::Resource<Graphics::Shader> shader);

	};
}

#endif // !ENGINEQ_SHADERPROPERTIES_HPP
