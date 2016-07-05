#include "ScriptEngine.hpp"

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/image.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/metadata.h>
#include <mono/metadata/class.h>
#include <mono/metadata/exception.h>
#include <mono/metadata/mono-debug.h>
#include <mono/metadata/attrdefs.h>

#include "API_Component.hpp"
#include "API_Transform.hpp"
#include "API_Entity.hpp"
#include "API_Scene.hpp"
#include "API_Quaternion.hpp"
#include "API_Matrix3.hpp"
#include "API_Matrix4.hpp"

namespace EngineQ
{
	namespace Scripting
	{
		MonoMethod* ScriptEngine::GetMethod(MonoClass* mclass, const char* name)
		{
			MonoMethodDesc* desc = mono_method_desc_new(name, true);
			if (desc == nullptr)
				return nullptr;
			MonoMethod* method = mono_method_desc_search_in_class(desc, mclass);
			mono_method_desc_free(desc);
			return method;
		}

		MonoMethod* ScriptEngine::GetScriptMethod(MonoClass* mclass, MonoObject* object, const char* name) const
		{
			MonoClass* currClass = mclass;
			MonoMethod* foundMethod = nullptr;

			while (currClass != this->scriptClass)
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


			this->domain = mono_jit_init(name);

			this->assembly = mono_domain_assembly_open(domain, assemblyPath);
			if (this->assembly == nullptr)
				throw ScriptEngineException("Failed to open assembly");

			this->image = mono_assembly_get_image(assembly);

			this->qObjectClass = mono_class_from_name(this->image, NamespaceName, ObjectClassName);
			this->qObjectHandleField = mono_class_get_field_from_name(this->qObjectClass, NativeHandleFieldName);

			this->entityClass = mono_class_from_name(this->image, NamespaceName, EntityClassName);
			this->scriptClass = mono_class_from_name(this->image, NamespaceName, ScriptClassName);
			this->transformClass = mono_class_from_name(this->image, NamespaceName, TransformClassName);
			this->lightClass = mono_class_from_name(this->image, NamespaceName, LightClassName);
			this->cameraClass = mono_class_from_name(this->image, NamespaceName, CameraClassName);
			this->sceneClass = mono_class_from_name(this->image, NamespaceName, SceneClassName);

			this->entityConstructor = GetMethod(this->entityClass, ConstructorName);
			this->transformConstructor = GetMethod(this->transformClass, ConstructorName);

			this->entityUpdate = GetMethod(this->entityClass, UpdateName);

			// API
			API_Quaternion::API_Register(*this);
			API_Matrix3::API_Register(*this);
			API_Matrix4::API_Register(*this);

			API_Component::API_Register(*this);
			API_Transform::API_Register(*this);
			API_Entity::API_Register(*this);
			API_Scene::API_Register(*this);
		}

		ScriptEngine::~ScriptEngine()
		{
			//	for (const auto& assembly : assemblies)
			//	{
			//		mono_image_close(assembly.second.second);
			//		mono_assembly_close(assembly.second.first);
			//	}

			mono_jit_cleanup(this->domain);
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
			mono_field_get_value(object, this->qObjectHandleField, &data);

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
			mono_runtime_invoke(method, mono_gchandle_get_target(handle), args, nullptr);
		}

		void ScriptEngine::InvokeConstructor(ScriptObject object) const
		{
			mono_runtime_object_init(object);
		}

		ScriptHandle ScriptEngine::CreateObject(ScriptClass sclass, Object* nativeHandle) const
		{
			// Create object
			MonoObject* instance = mono_object_new(this->domain, sclass);

			// Create reference and get handle
			uint32_t handle = mono_gchandle_new(instance, false);

			// Set pointer to native representation
			mono_field_set_value(instance, this->qObjectHandleField, &nativeHandle);

			return handle;
		}

		void ScriptEngine::DestroyObject(ScriptHandle handle) const
		{
			// Get object reference
			MonoObject* instance = mono_gchandle_get_target(handle);

			// Clear pointer to native representation
			void* nativeHandle = nullptr;
			mono_field_set_value(instance, this->qObjectHandleField, &nativeHandle);

			// Release reference
			mono_gchandle_free(handle);
		}

		void ScriptEngine::API_Register(const char* name, const void* method)
		{
			mono_add_internal_call(name, method);
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

		ScriptMethod ScriptEngine::GetScriptUpdateMethod(ScriptClass sclass, ScriptObject object) const
		{
			return GetScriptMethod(sclass, object, UpdateName);
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
		
		ScriptClass ScriptEngine::GetTransformClass() const
		{
			return this->transformClass;
		}

		ScriptClass ScriptEngine::GetLightClass() const
		{
			return this->lightClass;
		}

		ScriptClass ScriptEngine::GetCameraClass() const
		{
			return this->cameraClass;
		}

		ScriptClass ScriptEngine::GetEntityClass() const
		{
			return this->entityClass;
		}

		ScriptClass ScriptEngine::GetSceneClass() const
		{
			return this->sceneClass;
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
			if (sclass == this->scriptClass)
				return false;

			return IsDerrived(sclass, this->scriptClass);
		}

		//int ScriptEngine::TMPRUN(int argc, char** argv)
		//{
		//	return mono_jit_exec(this->domain, this->assembly, argc, argv);
		//}

		//uint32_t ScriptEngine::CreateObject(void* nativeHandle) const
		//{
		//	return CreateObject(this->qObjectClass, nativeHandle);
		//}

		//void ScriptEngine::ExposeMethod(MonoClass* mclass, const char* assemblyName) const
		//{
		//	MonoClass* currClass = mclass;

		//	std::cout << "Searching for method " << assemblyName << " in class " << mono_class_get_name(mclass) << std::endl;
		//	while (currClass != nullptr)
		//	{
		//		MonoMethod* meth = GetMethod(currClass, assemblyName);
		//		if (meth != nullptr)
		//		{
		//			std::cout << "Found in class " << mono_class_get_name(currClass) << std::endl;

		//			uint32_t flags = mono_method_get_flags(meth, NULL);
		//			
		//			if (flags & MONO_METHOD_ATTR_NEW_SLOT)
		//				std::cout << "\tnew" << std::endl;

		//			if (flags & MONO_METHOD_ATTR_VIRTUAL)
		//				std::cout << "\tvirtual" << std::endl;


		//			return;
		//		}
		//		currClass = mono_class_get_parent(currClass);
		//	}
		//	std::cout << "Not found" << std::endl;
		//}
	}
}