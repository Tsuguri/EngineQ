#ifndef ENGINEQ_RENDERABLE_HPP
#define ENGINEQ_RENDERABLE_HPP

#include <memory>

#include "../Graphics/Types.hpp"

#include "Component.hpp"
#include "../Resources/Types.hpp"

#include "../Resources/Resource.hpp"

namespace EngineQ
{
	class Renderable : public Component
	{
	private:
		std::unique_ptr<Graphics::ShaderProperties> forwardShader;
		std::unique_ptr<Graphics::ShaderProperties> deferredShader;
		Resources::Resource<Graphics::Mesh> mesh;
		
	public:
		Renderable(Scripting::ScriptEngine& scriptEngine, Entity& entity);
		
		void SetForwardShader(Resources::Resource<Graphics::Shader> shader);
		Graphics::ShaderProperties* GetForwardShader() const;

		void SetDeferredShader(Resources::Resource<Graphics::Shader> shader);
		Graphics::ShaderProperties* GetDeferredShader() const;

		
		Resources::Resource<Graphics::Mesh> GetMesh() const;
		void SetMesh(Resources::Resource<Graphics::Mesh> mesh);
	};
}

#endif // !ENGINEQ_RENDERABLE_HPP