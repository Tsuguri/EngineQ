#ifndef ENGINEQ_SHADER_PROPERTIES_HPP
#define ENGINEQ_SHADER_PROPERTIES_HPP

// Other projects
#include "EngineQRenderer/Graphics/ShaderProperties.hpp"

// This project
#include "EngineQ/Objects/Object.hpp"


namespace EngineQ
{
	class EngineShaderProperties : public Object, public Graphics::ShaderProperties
	{
	public:
		EngineShaderProperties(Scripting::ScriptEngine& scriptEngine, Resources::Resource<Graphics::Shader> shader);

	};
}

#endif // !ENGINEQ_SHADER_PROPERTIES_HPP
