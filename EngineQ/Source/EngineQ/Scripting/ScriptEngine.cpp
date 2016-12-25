#include "ScriptEngine.hpp"

// Libraries
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/image.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/metadata.h>
#include <mono/metadata/class.h>
#include <mono/metadata/exception.h>
#include <mono/metadata/mono-debug.h>
#include <mono/metadata/attrdefs.h>
#include <mono/metadata/mono-gc.h>

// This project
#include "ScriptingExceptions.hpp"
#include "API_Component.hpp"
#include "API_Scene.hpp"
#include "API_Entity.hpp"
#include "API_Resource.hpp"
#include "API_ShaderProperties.hpp"
#include "API_Camera.hpp"
#include "API_Transform.hpp"
#include "API_Renderable.hpp"
#include "API_Matrix3.hpp"
#include "API_Matrix4.hpp"
#include "API_Quaternion.hpp"
#include "API_Input.hpp"
#include "API_TimeCounter.hpp"
#include "API_Application.hpp"
#include "API_ResourceManager.hpp"
#include "API_EffectController.hpp"
#include "API_PrefabGenerator.hpp"


namespace EngineQ
{
	namespace Scripting
	{
		constexpr const char* ScriptEngine::ScriptClassNames[ScriptClassCount][2];

		std::array<MonoClass*, ScriptEngine::ScriptClassCount> ScriptEngine::scriptClasses;


		MonoMethod* ScriptEngine::GetMethod(MonoClass* mclass, const char* name)
		{
			MonoMethodDesc* desc = mono_method_desc_new(name, true);
			if (desc == nullptr)
				return nullptr;
			MonoMethod* method = mono_method_desc_search_in_class(desc, mclass);
			mono_method_desc_free(desc);
			return method;
		}

		ScriptMethod ScriptEngine::GetInputMethod(const char* name) const
		{
			return GetMethod(this->GetClass(Class::Input), name);
		}

		MonoMethod* ScriptEngine::GetScriptMethod(MonoClass* mclass, MonoObject* object, const char* name, MonoClass* scriptClass) const
		{
			MonoClass* currClass = mclass;
			MonoMethod* foundMethod = nullptr;
			
			while (currClass != scriptClass)
			{
				if (currClass == nullptr)
					throw ScriptEngineException("Class is not derrived from Script class");

				MonoMethod* method = GetMethod(currClass, name);

				if (method != nullptr)
				{
					uint32_t flags = mono_method_get_flags(method, nullptr);

					if (flags & MONO_METHOD_ATTR_NEW_SLOT)
						foundMethod = nullptr;
					else if (flags & MONO_METHOD_ATTR_VIRTUAL)
						foundMethod = method;
				}

				currClass = mono_class_get_parent(currClass);
			}

			if (foundMethod == nullptr)
				return nullptr;

			return mono_object_get_virtual_method(object, foundMethod);
		}

		ScriptEngine::ScriptEngine(const char* name, const char* assemblyPath, const char* libPath, const char* configPath)
		{
			mono_set_dirs(libPath, configPath);


			
			
			


		//	const char* inputArgs[] = {
		//		"--debugger-agent=transport=dt_socket,address=0.0.0.0:56000,server=y",
		//	};
			
		//	mono_jit_parse_options(sizeof(inputArgs) / sizeof(const char*), const_cast<char**>(inputArgs));

		//	mono_debug_init(MONO_DEBUG_FORMAT_MONO);
			
			this->domain = mono_jit_init(name);
			
		//	mono_debug_domain_create(this->domain);
			



			this->assembly = mono_domain_assembly_open(this->domain, assemblyPath);
			if (this->assembly == nullptr)
				throw ScriptEngineException("Failed to open assembly");

			this->image = mono_assembly_get_image(assembly);

			this->scriptClasses[static_cast<std::size_t>(Class::Integer)] = mono_get_int32_class();
			this->scriptClasses[static_cast<std::size_t>(Class::Float)] = mono_get_single_class();


			for (std::size_t i = ScriptClassOffset; i < ScriptClassCount; ++i)
			{
				std::size_t nameIndex = i - ScriptClassOffset;
				auto scriptClass = mono_class_from_name(this->image, ScriptClassNames[nameIndex][0], ScriptClassNames[nameIndex][1]);
				scriptClasses[i] = scriptClass;
			}

			this->nativeHandleClassField = mono_class_get_field_from_name(this->GetClass(Class::Object), NativeHandleFieldName);

			this->entityConstructor = GetMethod(this->GetClass(Class::Entity), ConstructorName);
			this->entityUpdate = GetMethod(this->GetClass(Class::Entity), UpdateName);

			this->transformConstructor = GetMethod(this->GetClass(Class::Transform), ConstructorName);


			// API
			API_Matrix3::API_Register(*this);
			API_Matrix4::API_Register(*this);
			API_Quaternion::API_Register(*this);

			API_Scene::API_Register(*this);
			API_Camera::API_Register(*this);
			API_Entity::API_Register(*this);
			API_Component::API_Register(*this);
			API_Transform::API_Register(*this);
			API_Renderable::API_Register(*this);

			API_Input::API_Register(*this);
			API_TimeCounter::API_Register(*this);
			API_Application::API_Register(*this);
			API_Resource::API_Register(*this);
			API_ResourceManager::API_Register(*this);
			API_ShaderProperties::API_Register(*this);
			API_EffectController::API_Register(*this);
			API_PrefabGenerator::API_Register(*this);
		}

		ScriptEngine::~ScriptEngine()
		{
			//	for (const auto& assembly : assemblies)
			//	{
			//		mono_image_close(assembly.second.second);
			//		mono_assembly_close(assembly.second.first);
			//	}


			auto maxGeneration = mono_gc_max_generation();
			mono_gc_collect(maxGeneration);
			//	mono_gc_invoke_finalizers();
			mono_domain_finalize(this->domain, -1);

			/*
			auto gcClass = mono_class_from_name(mono_get_corlib(), "System", "GC");

			auto collectMethod = GetMethod(gcClass, ":Collect");
			auto waitForPendingFinalizersMethod = GetMethod(gcClass, ":WaitForPendingFinalizers");

			MonoObject* exc = nullptr;
			mono_runtime_invoke(collectMethod, nullptr, nullptr, &exc);
			if (exc != nullptr)
			{
				std::printf("==== Unhandled exception ====\n");

				std::string excStr = this->GetScriptStringContent(mono_object_to_string(exc, nullptr));
				std::printf("%s\n", excStr.c_str());
			}

			exc = nullptr;
			mono_runtime_invoke(waitForPendingFinalizersMethod, nullptr, nullptr, &exc);
			if (exc != nullptr)
			{
				std::printf("==== Unhandled exception ====\n");

				std::string excStr = this->GetScriptStringContent(mono_object_to_string(exc, nullptr));
				std::printf("%s\n", excStr.c_str());
			}
			*/

			mono_jit_cleanup(this->domain);

			//	mono_domain_unload(this->domain);
			//	mono_domain_free(this->domain, false);
		}

		ScriptObject ScriptEngine::GetInstance(ScriptHandle handle) const
		{
			return mono_gchandle_get_target(handle);
		}

		Object* ScriptEngine::GetNativeHandle(ScriptObject object) const
		{
			if (object == nullptr)
				return nullptr;

			Object* data = nullptr;
			mono_field_get_value(object, this->nativeHandleClassField, &data);

			return data;
		}

		void ScriptEngine::Throw_ArgumentException(const char* argument, const char* message) const
		{
			mono_raise_exception(mono_get_exception_argument(argument, message));
		}

		void ScriptEngine::Throw_IndexOutOfRangeException() const
		{
			mono_raise_exception(mono_get_exception_index_out_of_range());
		}

		void ScriptEngine::InvokeMethod(ScriptHandle handle, ScriptMethod method, void** args) const
		{
			MonoObject* exc = nullptr;
			mono_runtime_invoke(method, mono_gchandle_get_target(handle), args, &exc);

			// TMP
			if (exc != nullptr)
			{
				std::printf("==== Unhandled exception ====\n");
				
				std::string excStr = this->GetScriptStringContent(mono_object_to_string(exc, nullptr));
				std::printf("%s\n", excStr.c_str());
			}
		}

		void ScriptEngine::InvokeStaticMethod(ScriptMethod method, void** args) const
		{
			MonoObject* exc = nullptr;
			mono_runtime_invoke(method, nullptr, args, &exc);

			// TMP
			if (exc != nullptr)
			{
				std::printf("==== Unhandled exception ====\n");

				std::string excStr = this->GetScriptStringContent(mono_object_to_string(exc, nullptr));
				std::printf("%s\n", excStr.c_str());
			}
		}

		void ScriptEngine::InvokeConstructor(ScriptObject object) const
		{
			mono_runtime_object_init(object);
		}

		ScriptObject ScriptEngine::CreateUnhandledObject(ScriptClass sclass, void* nativeHandle) const
		{
			// Create object
			MonoObject* instance = mono_object_new(this->domain, sclass);

			// Set pointer to native representation
			mono_field_set_value(instance, this->nativeHandleClassField, &nativeHandle);

			mono_runtime_object_init(instance);

			return instance;
		}

		ScriptHandle ScriptEngine::CreateObject(ScriptClass sclass, Object* nativeHandle) const
		{
			// Create object
			MonoObject* instance = mono_object_new(this->domain, sclass);

			// Create reference and get handle
			uint32_t handle = mono_gchandle_new(instance, false);

			// Set pointer to native representation
			mono_field_set_value(instance, this->nativeHandleClassField, &nativeHandle);

			return handle;
		}

		void ScriptEngine::DestroyObject(ScriptHandle handle) const
		{
			// Get object reference
			MonoObject* instance = mono_gchandle_get_target(handle);

			// Clear pointer to native representation
			void* nativeHandle = nullptr;
			mono_field_set_value(instance, this->nativeHandleClassField, &nativeHandle);

			// Release reference
			mono_gchandle_free(handle);
		}

		void ScriptEngine::API_Register(const char* name, const void* function)
		{
			mono_add_internal_call(name, function);
		}

		void ScriptEngine::LoadAssembly(const char* path)
		{
			MonoAssembly* assembly = mono_domain_assembly_open(this->domain, path);
			MonoAssemblyName* assemblyName = mono_assembly_get_name(assembly);
			std::string name = std::string{ mono_assembly_name_get_name(assemblyName) };
			//	mono_assembly_name_free(assemblyName);

			MonoImage* image = mono_assembly_get_image(assembly);

			this->assemblies[name] = { assembly, image };
		}


		ScriptMethod ScriptEngine::GetScriptCreateMethod(ScriptClass sclass, ScriptObject object) const
		{
			return GetScriptMethod(sclass, object, OnCreateName, this->GetClass(Class::Script));
		}

		ScriptMethod ScriptEngine::GetScriptActivateMethod(ScriptClass sclass, ScriptObject object) const
		{
			return GetScriptMethod(sclass, object, OnActivateName, this->GetClass(Class::Script));
		}

		ScriptMethod ScriptEngine::GetScriptEnableMethod(ScriptClass sclass, ScriptObject object) const
		{
			return GetScriptMethod(sclass, object, OnEnableName, this->GetClass(Class::Script));
		}

		ScriptMethod ScriptEngine::GetScriptUpdateMethod(ScriptClass sclass, ScriptObject object) const
		{
			return GetScriptMethod(sclass, object, OnUpdateName, this->GetClass(Class::Script));
		}

		ScriptMethod ScriptEngine::GetScriptDisableMethod(ScriptClass sclass, ScriptObject object) const
		{
			return GetScriptMethod(sclass, object, OnDisableName, this->GetClass(Class::Script));
		}
		
		ScriptMethod ScriptEngine::GetScriptDeactivateMethod(ScriptClass sclass, ScriptObject object) const
		{
			return GetScriptMethod(sclass, object, OnDeactivateName, this->GetClass(Class::Script));
		}

		ScriptMethod ScriptEngine::GetScriptDestroyMethod(ScriptClass sclass, ScriptObject object) const
		{
			return GetScriptMethod(sclass, object, OnDestroyName, this->GetClass(Class::Script));
		}


		ScriptMethod ScriptEngine::GetEffectCreateMethod(ScriptClass sclass, ScriptObject object) const
		{
			return GetScriptMethod(sclass, object, OnCreateName, this->GetClass(Class::EffectController));
		}

		ScriptMethod ScriptEngine::GetEffectUpdateMethod(ScriptClass sclass, ScriptObject object) const
		{
			return GetScriptMethod(sclass, object, OnUpdateName, this->GetClass(Class::EffectController));
		}

		ScriptMethod ScriptEngine::GetEffectBeforeRenderMethod(ScriptClass sclass, ScriptObject object) const
		{
			return GetScriptMethod(sclass, object, OnBeforeRenderName, this->GetClass(Class::EffectController));
		}

		ScriptMethod ScriptEngine::GetEffectAfterRenderMethod(ScriptClass sclass, ScriptObject object) const
		{
			return GetScriptMethod(sclass, object, OnAfterRenderName, this->GetClass(Class::EffectController));
		}

		ScriptMethod ScriptEngine::GetEffectDestroyMethod(ScriptClass sclass, ScriptObject object) const
		{
			return GetScriptMethod(sclass, object, OnDestroyName, this->GetClass(Class::EffectController));
		}


		ScriptMethod ScriptEngine::GetInitializerMethod(const std::string& iassembly, const std::string& inamespace, const std::string& iclass) const
		{
			auto scriptClass = this->GetClass(iassembly, inamespace, iclass);

			auto method = this->GetMethod(scriptClass, InitializerName);
			if (method == nullptr)
				throw std::runtime_error{ std::string{ InitializerName } + " method not found" };

			auto signature = mono_method_signature(method);
		
			if (mono_signature_is_instance(signature))
				throw std::runtime_error{ std::string{ InitializerName } + " method must be static" };

			if (mono_signature_get_param_count(signature) != 1)
				throw std::runtime_error{ std::string{ InitializerName } +" method must accept only one argument of type Scene" };

			void* paramsIter = nullptr;
			auto arg0Type = mono_signature_get_params(signature, &paramsIter);
			
			auto arg0Class = mono_type_get_class(arg0Type);
			if (arg0Class != this->GetClass(Class::Scene))
				throw std::runtime_error{ std::string{ InitializerName } +" method must accept only one argument of type Scene" };

			return method;
		}

		void ScriptEngine::GetClassDescription(ScriptClass sclass, std::string& cassembly, std::string& cnamespace, std::string& cname) const
		{
			cname = mono_class_get_name(sclass);
			cnamespace = mono_class_get_namespace(sclass);

			MonoImage* image = mono_class_get_image(sclass);

			if (image != this->image)
			{
				for (auto& assembly : this->assemblies)
				{
					if (assembly.second.second == image)
					{
						cassembly = assembly.first;
						break;
					}
				}
			}
			else
			{
				cassembly = "";
			}
		}

		ScriptClass ScriptEngine::GetClass(const std::string& cassembly, const std::string& cnamespace, const std::string& cname) const
		{
			MonoImage* image = this->image;

			if (cassembly != "")
			{
				auto it = this->assemblies.find(cassembly);
				if (it == this->assemblies.end())
					throw ScriptEngineException{ "Assembly " + cassembly + " not found" };

				image = it->second.second;
			}

			MonoClass* mclass = mono_class_from_name(image, cnamespace.c_str(), cname.c_str());
			if (mclass == nullptr)
				throw ScriptEngineException{ "Class " + cnamespace + "." + cname + (cassembly == "" ? "" : " from assembly " + cassembly) + " not found" };

			return mclass;
		}

		ScriptClass ScriptEngine::GetScriptClass(const char* assembly, const char* classNamespace, const char* name) const
		{
			std::string assemblyName = std::string{ assembly };

			auto it = assemblies.find(assemblyName);
			if (it == assemblies.end())
				return nullptr;

			MonoImage* image = it->second.second;

			return mono_class_from_name(image, classNamespace, name);
		}

		ScriptClass ScriptEngine::GetEffectControllerClass(const char* assembly, const char* classNamespace, const char* name) const
		{
			std::string assemblyName = std::string{ assembly };

			auto it = assemblies.find(assemblyName);
			if (it == assemblies.end())
				return nullptr;

			MonoImage* image = it->second.second;

			auto effectClass = mono_class_from_name(image, classNamespace, name);

			if(effectClass == nullptr)
				throw ScriptEngineException{ "Class " + std::string{ classNamespace } +"." + name + (assemblyName.empty() ? "" : " from assembly " + assemblyName) + " not found" };
			
			if (!this->IsDerrived(effectClass, this->GetClass(Class::EffectController)))
				throw ScriptEngineException{ "Class " + std::string{ classNamespace } +"." + name + (assemblyName.empty() ? "" : " from assembly " + assemblyName) + " is not derrived from EffectController" };

			return effectClass;
		}

		ScriptClass ScriptEngine::GetClass(ScriptEngine::Class scriptClass) const
		{
			std::size_t index = static_cast<std::size_t>(scriptClass);
			return this->scriptClasses[index];
		}

		ScriptClass ScriptEngine::GetObjectClass(ScriptObject object) const
		{
			return mono_object_get_class(object);
		}

		ScriptClass ScriptEngine::GetTypeClass(ScriptTypeClass type) const
		{
			return mono_type_get_class(mono_reflection_type_get_type(type));
		}

		bool ScriptEngine::IsDerrived(ScriptClass derrived, ScriptClass base) const
		{
			MonoClass* currClass = derrived;
			while (currClass != base)
			{
				if (currClass == nullptr)
					return false;

				currClass = mono_class_get_parent(currClass);
			}

			return true;
		}

		bool ScriptEngine::IsScript(ScriptClass sclass) const
		{
			if (sclass == this->GetClass(Class::Script))
				return false;

			return IsDerrived(sclass, this->GetClass(Class::Script));
		}

		void* ScriptEngine::Unbox(ScriptObject object) const
		{
			return mono_object_unbox(object);
		}

		std::string ScriptEngine::GetScriptStringContent(ScriptString string) const
		{
			char* cstring = mono_string_to_utf8(string);
			std::string cppstring = cstring;
			mono_free(cstring);

			return cppstring;
		}

		ScriptString ScriptEngine::CreateScriptString(const std::string& content) const
		{
			return mono_string_new(this->domain, content.c_str());
		}
	}
}
