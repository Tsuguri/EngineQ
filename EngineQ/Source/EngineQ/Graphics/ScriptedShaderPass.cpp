#include "ScriptedShaderPass.hpp"

// This project
#include "EngineQ/Scripting/ScriptEngine.hpp"
#include "EngineQ/Engine.hpp"


namespace EngineQ
{
	namespace Graphics
	{
		ScriptedShaderPass::ScriptedShaderPass(Scripting::ScriptEngine& scriptEngine, Scripting::ScriptClass effectClass, Resources::Resource<Shader> shader, const std::string& name) :
			Object(scriptEngine, effectClass), ShaderPass(std::make_unique<EngineShaderProperties>(scriptEngine, shader), name)
		{
			auto managedObject = this->GetManagedObject();

			this->createMethod = this->scriptEngine.GetEffectCreateMethod(effectClass, managedObject);
			this->updateMethod = this->scriptEngine.GetEffectUpdateMethod(effectClass, managedObject);
			this->beforeRenderMethod = this->scriptEngine.GetEffectBeforeRenderMethod(effectClass, managedObject);
			this->afterUpdateMethod = this->scriptEngine.GetEffectAfterRenderMethod(effectClass, managedObject);
			this->destroyMethod = this->scriptEngine.GetEffectDestroyMethod(effectClass, managedObject);

			this->scriptEngine.InvokeConstructor(managedObject);
		}

		ScriptedShaderPass::~ScriptedShaderPass()
		{
			if (this->destroyMethod != nullptr)
				this->scriptEngine.InvokeMethod(this->managedHandle, this->destroyMethod, nullptr);
		}

		EngineShaderProperties& ScriptedShaderPass::GetShaderProperties() const
		{
			return static_cast<EngineShaderProperties&>(this->ShaderPass::GetShaderProperties());
		}

		bool ScriptedShaderPass::IsUpdatable() const
		{
			return this->updateMethod != nullptr;
		}

		void ScriptedShaderPass::Update()
		{
			this->scriptEngine.InvokeMethod(this->managedHandle, this->updateMethod, nullptr);
		}

		void ScriptedShaderPass::BeforeRender()
		{
			Engine::Get().GetProfiler().StartGPU(this->GetName(), "Postprocessing");

			if (this->beforeRenderMethod != nullptr)
				this->scriptEngine.InvokeMethod(this->managedHandle, this->beforeRenderMethod, nullptr);
		}

		void ScriptedShaderPass::AfterRender()
		{
			if (this->afterUpdateMethod != nullptr)
				this->scriptEngine.InvokeMethod(this->managedHandle, this->afterUpdateMethod, nullptr);

			Engine::Get().GetProfiler().EndGPU(this->GetName(), "Postprocessing");
		}
		
		void ScriptedShaderPass::Created()
		{
			if (this->createMethod != nullptr)
				this->scriptEngine.InvokeMethod(this->managedHandle, this->createMethod, nullptr);
		}
	}
}

