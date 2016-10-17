#ifndef ENGINEQ_SCRIPTING_SCRIPT_ENGINE_HPP
#define ENGINEQ_SCRIPTING_SCRIPT_ENGINE_HPP

#include <map>
#include <string>

#include "Types.hpp"
#include "../Objects/Types.hpp"

#include "../Utilities/Immovable.hpp"

namespace EngineQ
{
	namespace Scripting
	{
		class ScriptEngine : private Utilities::Immovable
		{
		private:
			static constexpr const char* ConstructorName = ":.ctor";
			static constexpr const char* UpdateName = ":Update";

			static constexpr const char* NamespaceName = "EngineQ";
			static constexpr const char* ObjectClassName = "Object";
			static constexpr const char* EntityClassName = "Entity";
			static constexpr const char* ScriptClassName = "Script";
			static constexpr const char* TransformClassName = "Transform";
			static constexpr const char* LightClassName = "Light";
			static constexpr const char* CameraClassName = "Camera";
			static constexpr const char* RenderableClassName = "Renderable";
			static constexpr const char* SceneClassName = "Scene";
			static constexpr const char* InputClassName = "Input";

			static constexpr const char* ResourceShaderClass = "Shader";
			static constexpr const char* ResourceTextureClass = "Texture";

			static constexpr const char* NativeHandleFieldName = "nativeHandle";

			MonoDomain* domain;
			MonoAssembly* assembly;
			MonoImage* image;

			MonoClass* scriptClass;
			MonoClass* qObjectClass;
			MonoClassField* qObjectHandleField;

			MonoClass* entityClass;
			MonoClass* transformClass;
			MonoClass* lightClass;
			MonoClass* cameraClass;
			MonoClass* sceneClass;
			MonoClass* inputClass;
			MonoClass* renderableClass;

			MonoClass* resourceShaderClass;
			MonoClass* resourceTextureClass;

			MonoMethod* entityConstructor;
			MonoMethod* transformConstructor;

			MonoMethod* entityUpdate;

			std::map<std::string, std::pair<MonoAssembly*, MonoImage*>> assemblies;

			static MonoMethod* GetMethod(MonoClass* mclass, const char* name);
			MonoMethod* GetScriptMethod(MonoClass* mclass, MonoObject* object, const char* name) const;

			void API_Register(const char* name, const void* function);

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
			
			ScriptHandle CreateObject(ScriptClass sclass, Object* nativeHandle) const;
			void DestroyObject(ScriptHandle handle) const;

			template<typename TReturn, typename... TArgs>
			void API_Register(const char* name, TReturn(*function)(TArgs...));
			void LoadAssembly(const char* path);

			ScriptMethod GetScriptUpdateMethod(ScriptClass sclass, ScriptObject object) const;

			void GetClassDescription(ScriptClass sclass, std::string& cassembly, std::string& cnamespace, std::string& cname) const;
			ScriptClass GetClass(const std::string& cassembly, const std::string& cnamespace, const std::string& cname) const;

			ScriptClass GetScriptClass(const char* assembly, const char* classNamespace, const char* name) const;
			ScriptClass GetTransformClass() const;
			ScriptClass GetLightClass() const;
			ScriptClass GetCameraClass() const;
			ScriptClass GetEntityClass() const;
			ScriptClass GetSceneClass() const;
			ScriptClass GetRenderableClass() const;

			ScriptClass GetResourceShaderClass() const;
			ScriptClass GetResourceTextureClass() const;

			ScriptMethod GetInputMethod(const char* name) const;

			ScriptClass GetObjectClass(ScriptObject object) const;
			ScriptClass GetTypeClass(ScriptTypeClass type) const;

			bool IsDerrived(ScriptClass derrived, ScriptClass base) const;
			bool IsScript(ScriptClass sclass) const;
		};
	}
}

#include "ScriptEngine.inl"

#endif // !ENGINEQ_SCRIPTING_SCRIPT_ENGINE_HPP
