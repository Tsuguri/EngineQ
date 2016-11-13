#ifndef ENGINEQ_SCRIPTING_API_RENDERABLE_HPP
#define ENGINEQ_SCRIPTING_API_RENDERABLE_HPP

#include "Types.hpp"
#include "../Objects/Types.hpp"
#include <Graphics/Types.hpp>

#include <Resources/Resource.hpp>

namespace EngineQ
{
	namespace Scripting
	{
		class API_Renderable
		{
		public:
			static void API_GetForwardShader(const Object& renderableBase, MonoObject*& forwardShader);
			static void API_GetDeferredShader(const Object& renderableBase, MonoObject*& deferredShader);
			static void API_GetMesh(const Object& renderableBase, MonoObject*& mesh);
			static void API_SetMesh(Object& renderableBase, Resources::Resource<Graphics::Mesh>::ControlBlock& mesh);
			static void API_UseForwardShader(Object& renderableBase, Resources::Resource<Graphics::Shader>::ControlBlock& shader);
			static void API_UseDeferredShader(Object& renderableBase, Resources::Resource<Graphics::Shader>::ControlBlock& shader);

			static void API_Register(ScriptEngine& scriptEngine);
		};
	}
}

#endif // !ENGINEQ_SCRIPTING_API_RENDERABLE_HPP
