#ifndef ENGINEQ_SCRIPTING_SCRIPT_ENGINE_H
#define ENGINEQ_SCRIPTING_SCRIPT_ENGINE_H

#include <iostream>
#include <map>
#include <string>

#include "ScriptEngineException.hpp"

typedef struct _MonoDomain MonoDomain;
typedef struct _MonoAssembly MonoAssembly;
typedef struct _MonoImage MonoImage;
typedef struct _MonoClass MonoClass;
typedef struct _MonoClassField MonoClassField;
typedef struct _MonoMethod MonoMethod;
typedef struct _MonoReflectionType MonoReflectionType;
typedef struct _MonoObject MonoObject;

namespace EngineQ
{
	class Object;
	class Entity;
	class Transform;

	namespace Scripting
	{
		using ScriptClass = MonoClass*;
		using ScriptMethod = MonoMethod*;
		using ScriptObject = MonoObject*;
		using ScriptHandle = std::uint32_t;
		using ScriptTypeClass = MonoReflectionType*;

		class ScriptEngine
		{
		private:
			static constexpr char* ConstructorName = ":.ctor";
			static constexpr char* UpdateName = ":Update";

			static constexpr char* NamespaceName = "EngineQ";
			static constexpr char* ObjectClassName = "Object";
			static constexpr char* EntityClassName = "Entity";
			static constexpr char* ScriptClassName = "Script";
			static constexpr char* TransformClassName = "Transform";
			static constexpr char* LightClassName = "Light";
			static constexpr char* CameraClassName = "Camera";

			static constexpr char* NativeHandleFieldName = "nativeHandle";

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

			MonoMethod* entityConstructor;
			MonoMethod* transformConstructor;

			MonoMethod* entityUpdate;

			std::map<std::string, std::pair<MonoAssembly*, MonoImage*>> assemblies;

			static MonoMethod* GetMethod(MonoClass* mclass, const char* name);
			MonoMethod* GetScriptMethod(MonoClass* mclass, MonoObject* object, const char* name) const;

		public:
			ScriptEngine(const char* name, const char* assemblyPath, const char* libPath, const char* configPath);
			~ScriptEngine();

			ScriptObject GetInstance(ScriptHandle handle) const;
			Object* GetNativeHandle(ScriptObject object) const;

			void Throw_ArgumentException(const char* argument, const char* message) const;
			void Throw_IndexOutOfRangeException() const;

			void InvokeMethod(ScriptHandle handle, ScriptMethod method, void** args) const;
			void InvokeConstructor(ScriptObject object) const;
			
			ScriptHandle CreateObject(ScriptClass sclass, Object* nativeHandle) const;
			void DestroyObject(ScriptHandle handle) const;

			void API_Register(const char* name, const void* method);
			void LoadAssembly(const char* path);

			ScriptMethod GetScriptUpdateMethod(ScriptClass sclass, ScriptObject object) const;

			ScriptClass GetScriptClass(const char* assembly, const char* classNamespace, const char* name) const;
			ScriptClass GetTransformClass() const;
			ScriptClass GetLightClass() const;
			ScriptClass GetCameraClass() const;
			ScriptClass GetEntityClass() const;

			ScriptClass GetObjectClass(ScriptObject object) const;
			ScriptClass GetTypeClass(ScriptTypeClass type) const;			
		};
	}
}

#endif // !ENGINEQ_SCRIPTING_SCRIPT_ENGINE_H
