#ifndef ENGINEQ_GRAPHICS_SCRIPTED_RENDERING_UNIT_HPP
#define ENGINEQ_GRAPHICS_SCRIPTED_RENDERING_UNIT_HPP

// Other projects
#include "EngineQRenderer/Graphics/RenderingUnit.hpp"

// This project
#include "ScriptedShaderPass.hpp"
#include "EngineQ/Scripting/Types.hpp"


namespace EngineQ
{
	namespace Graphics
	{
		class ScriptedRenderingUnit : public RenderingUnit
		{
		private:
			class ScriptedShaderPassFactory : public ShaderPassFactory
			{
			private:
				ScriptedRenderingUnit& parent;

			public:
				ScriptedShaderPassFactory(ScriptedRenderingUnit& parent);

				virtual std::unique_ptr<ShaderPass> CreateShaderPass(const Configuration::EffectConfiguration& config) override;
			};

			Scripting::ScriptEngine& scriptEngine;
			std::vector<ScriptedShaderPass*> updatable;

		public:
			ScriptedRenderingUnit(Scripting::ScriptEngine& scriptEngine, ScreenDataProvider* engine, const Configuration::RenderingUnitConfiguration& configuration);

			void Update();
		};
	}
}

#endif // !ENGINEQ_GRAPHICS_SCRIPTED_RENDERING_UNIT_HPP
