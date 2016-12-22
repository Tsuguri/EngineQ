#ifndef ENGINEQ_GRAPHICS_SCRIPTED_SHADER_PASS_HPP
#define ENGINEQ_GRAPHICS_SCRIPTED_SHADER_PASS_HPP

// Other projects
#include "EngineQRenderer/Graphics/ShaderPass.hpp"

// This project
#include "EngineQ/Objects/Object.hpp"
#include "EngineQ/EngineShaderProperties.hpp"


namespace EngineQ
{
	namespace Graphics
	{
		class ScriptedShaderPass : public Object, public ShaderPass
		{
		private:
			Scripting::ScriptMethod createMethod;
			Scripting::ScriptMethod updateMethod;
			Scripting::ScriptMethod beforeRenderMethod;
			Scripting::ScriptMethod afterUpdateMethod;
			Scripting::ScriptMethod destroyMethod;

		public:
			ScriptedShaderPass(Scripting::ScriptEngine& scriptEngine, Scripting::ScriptClass effectClass, Resources::Resource<Shader> shader);
			virtual ~ScriptedShaderPass();

			EngineShaderProperties& GetShaderProperties() const;

			bool IsUpdatable() const;
			void Update();

			virtual void BeforeRender() override;
			virtual void AfterRender() override;
			virtual void Created() override;
		};
	}
}

#endif // !ENGINEQ_GRAPHICS_SCRIPTED_SHADER_PASS_HPP
