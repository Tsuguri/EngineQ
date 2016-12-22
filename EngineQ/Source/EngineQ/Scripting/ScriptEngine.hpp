#ifndef ENGINEQ_SCRIPTING_SCRIPT_ENGINE_HPP
#define ENGINEQ_SCRIPTING_SCRIPT_ENGINE_HPP

// Standard includes
#include <map>
#include <string>
#include <array>

// Other projects
#include "EngineQCommon/Utilities/Immovable.hpp"

// This project
#include "Types.hpp"
#include "EngineQ/Objects/Types.hpp"


namespace EngineQ
{
	namespace Scripting
	{
		class ScriptEngine : private Utilities::Immovable
		{
		public:
			enum class Class
			{
				Integer,
				Float,

				Object,
				Entity,
				Script,
				Transform,
				Light,
				Camera,
				Renderable,
				Scene,
				ResourceManager,

				EffectController,
				ShaderProperties,

				Shader,
				Texture,
				Model,
				Mesh,
				
				Vector3f,

				Input,
			};
			
		private:
			static constexpr std::size_t ScriptClassOffset = static_cast<std::size_t>(Class::Object);
			static constexpr std::size_t ScriptClassCount = static_cast<std::size_t>(Class::Input) + 1;

			static constexpr const char* MathNamespaceName = "EngineQ.Math";
			static constexpr const char* NamespaceName = "EngineQ";
			static constexpr const char* ConstructorName = ":.ctor";
			
			static constexpr const char* UpdateName = ":Update";
			
			static constexpr const char* OnCreateName = ":OnCreate";
			static constexpr const char* OnActivateName = ":OnActivate";
			static constexpr const char* OnEnableName = ":OnEnable";
			static constexpr const char* OnUpdateName = ":OnUpdate";
			static constexpr const char* OnDisableName = ":OnDisable";
			static constexpr const char* OnDeactivateName = ":OnDeactivate";
			static constexpr const char* OnDestroyName = ":OnDestroy";
			static constexpr const char* OnBeforeRenderName = ":OnBeforeRender";
			static constexpr const char* OnAfterRenderName = ":OnAfterRender";

			static constexpr const char* InitializerName = ":OnInitialize";

			static constexpr const char* NativeHandleFieldName = "nativeHandle";

			static constexpr const char* ScriptClassNames[ScriptClassCount][2] = {
				{ NamespaceName, "Object" },
				{ NamespaceName, "Entity" },
				{ NamespaceName, "Script" },
				{ NamespaceName, "Transform" },
				{ NamespaceName, "Light" },
				{ NamespaceName, "Camera" },
				{ NamespaceName, "Renderable" },
				{ NamespaceName, "Scene" },
				{ NamespaceName, "ResourceManager" },

				{ NamespaceName, "EffectController" },
				{ NamespaceName, "ShaderProperties" },
				
				{ NamespaceName, "Shader" },
				{ NamespaceName, "Texture" },
				{ NamespaceName, "Model" },
				{ NamespaceName, "Mesh" },

				{ MathNamespaceName, "Vector3f" },

				{ NamespaceName, "Input" },
			};

			static std::array<MonoClass*, ScriptClassCount> scriptClasses;

			MonoDomain* domain;
			MonoAssembly* assembly;
			MonoImage* image;

			MonoClassField* nativeHandleClassField;

			MonoMethod* entityConstructor;	
			MonoMethod* transformConstructor;
			MonoMethod* entityUpdate;

			std::map<std::string, std::pair<MonoAssembly*, MonoImage*>> assemblies;

			static MonoMethod* GetMethod(MonoClass* mclass, const char* name);
			MonoMethod* GetScriptMethod(MonoClass* mclass, MonoObject* object, const char* name, MonoClass* scriptClass) const;

			void API_Register(const char* name, const void* function);

			void* Unbox(ScriptObject object) const;

		public:
			ScriptEngine(const char* name, const char* assemblyPath, const char* libPath, const char* configPath);
			~ScriptEngine();

			ScriptObject GetInstance(ScriptHandle handle) const;
			Object* GetNativeHandle(ScriptObject object) const;

			void Throw_ArgumentException(const char* argument, const char* message) const;
			void Throw_IndexOutOfRangeException() const;

			void InvokeMethod(ScriptHandle handle, ScriptMethod method, void** args) const;
			void InvokeStaticMethod(ScriptMethod method, void** args) const;
			void InvokeConstructor(ScriptObject object) const;

			ScriptObject CreateUnhandledObject(ScriptClass sclass, void* nativeHandle) const;
			ScriptHandle CreateObject(ScriptClass sclass, Object* nativeHandle) const;
			void DestroyObject(ScriptHandle handle) const;

			template<typename TReturn, typename... TArgs>
			void API_Register(const char* name, TReturn(*function)(TArgs...));
			void LoadAssembly(const char* path);

			ScriptMethod GetScriptCreateMethod(ScriptClass sclass, ScriptObject object) const;
			ScriptMethod GetScriptActivateMethod(ScriptClass sclass, ScriptObject object) const;
			ScriptMethod GetScriptEnableMethod(ScriptClass sclass, ScriptObject object) const;
			ScriptMethod GetScriptUpdateMethod(ScriptClass sclass, ScriptObject object) const;
			ScriptMethod GetScriptDisableMethod(ScriptClass sclass, ScriptObject object) const;
			ScriptMethod GetScriptDeactivateMethod(ScriptClass sclass, ScriptObject object) const;
			ScriptMethod GetScriptDestroyMethod(ScriptClass sclass, ScriptObject object) const;
			
			ScriptMethod GetEffectCreateMethod(ScriptClass sclass, ScriptObject object) const;
			ScriptMethod GetEffectUpdateMethod(ScriptClass sclass, ScriptObject object) const;
			ScriptMethod GetEffectBeforeRenderMethod(ScriptClass sclass, ScriptObject object) const;
			ScriptMethod GetEffectAfterRenderMethod(ScriptClass sclass, ScriptObject object) const;
			ScriptMethod GetEffectDestroyMethod(ScriptClass sclass, ScriptObject object) const;
			
			ScriptMethod GetInitializerMethod(const std::string& iassembly, const std::string& inamespace, const std::string& iclass) const;

			void GetClassDescription(ScriptClass sclass, std::string& cassembly, std::string& cnamespace, std::string& cname) const;
			ScriptClass GetClass(const std::string& cassembly, const std::string& cnamespace, const std::string& cname) const;

			ScriptClass GetScriptClass(const char* assembly, const char* classNamespace, const char* name) const;
			ScriptClass GetEffectControllerClass(const char * assembly, const char * classNamespace, const char * name) const;
			
			ScriptClass GetClass(Class scriptClass) const;
			
			ScriptMethod GetInputMethod(const char* name) const;

			ScriptClass GetObjectClass(ScriptObject object) const;
			ScriptClass GetTypeClass(ScriptTypeClass type) const;

			bool IsDerrived(ScriptClass derrived, ScriptClass base) const;
			bool IsScript(ScriptClass sclass) const;

			template<typename TType>
			TType& GetValue(ScriptObject object) const;
			std::string GetScriptStringContent(ScriptString string) const;
			ScriptString CreateScriptString(const std::string& content) const;
		};
	}
}

#include "ScriptEngine.inl"

#endif // !ENGINEQ_SCRIPTING_SCRIPT_ENGINE_HPP
