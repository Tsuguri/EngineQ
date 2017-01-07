#include "ScriptedRenderingUnit.hpp"

// This project
#include "EngineQ/Scripting/ScriptEngine.hpp"
#include "ScriptedRenderer.hpp"


namespace EngineQ
{
	namespace Graphics
	{
		ScriptedRenderingUnit::ScriptedRenderingUnit(Scripting::ScriptEngine& scriptEngine, ScreenDataProvider* screenDataProvider, const Configuration::RenderingUnitConfiguration& configuration) :
			RenderingUnit(screenDataProvider, configuration, std::make_unique<ScriptedShaderPassFactory>(*this), std::make_unique<ScriptedRendererFactory>()), scriptEngine(scriptEngine)
		{
			Initialize(configuration);
		}
		
		void ScriptedRenderingUnit::Update()
		{
			for (auto effect : this->updatable)
				effect->Update();
		}

		ScriptedRenderingUnit::ScriptedShaderPassFactory::ScriptedShaderPassFactory(ScriptedRenderingUnit& parent) :
			parent(parent)
		{
		}
		
		std::unique_ptr<ShaderPass> ScriptedRenderingUnit::ScriptedShaderPassFactory::CreateShaderPass(const Configuration::EffectConfiguration& config, const std::string& name)
		{
			Scripting::ScriptClass effectController;
			if (config.ClassName.empty())
			{
				effectController = parent.scriptEngine.GetClass(Scripting::ScriptEngine::Class::EffectController);
			}
			else
			{
				effectController = parent.scriptEngine.GetEffectControllerClass(config.ClassAssembly.c_str(), config.ClassNamespace.c_str(), config.ClassName.c_str());
			}

			auto shaderPass = std::make_unique<ScriptedShaderPass>(parent.scriptEngine, effectController, config.EffectShader, name);

			if (shaderPass->IsUpdatable())
				parent.updatable.push_back(shaderPass.get());

			return std::move(shaderPass);
		}
		
		std::unique_ptr<Renderer> ScriptedRenderingUnit::ScriptedRendererFactory::CreateRenderer()
		{
			return std::make_unique<ScriptedRenderer>();
		}
	}
}