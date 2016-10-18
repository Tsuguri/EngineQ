#ifndef ENGINEQ_SCRIPTING_TYPES_HPP
#define ENGINEQ_SCRIPTING_TYPES_HPP

#include <cstdint>

typedef struct _MonoDomain MonoDomain;
typedef struct _MonoAssembly MonoAssembly;
typedef struct _MonoImage MonoImage;
typedef struct _MonoClass MonoClass;
typedef struct _MonoClassField MonoClassField;
typedef struct _MonoMethod MonoMethod;
typedef struct _MonoReflectionType MonoReflectionType;
typedef struct _MonoObject MonoObject;
typedef struct _MonoString MonoString;

namespace EngineQ
{
	namespace Scripting
	{
		using ScriptClass = MonoClass*;
		using ScriptMethod = MonoMethod*;
		using ScriptObject = MonoObject*;
		using ScriptHandle = std::uint32_t;
		using ScriptTypeClass = MonoReflectionType*;
		using ScriptString = MonoString*;

		class ScriptEngine;
	}
}

#endif // !ENGINEQ_SCRIPTING_TYPES_HPP
