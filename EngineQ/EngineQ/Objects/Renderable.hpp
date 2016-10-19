#ifndef ENGINEQ_RENDERABLE_HPP
#define ENGINEQ_RENDERABLE_HPP

#include <memory>

#include "../Graphics/Types.hpp"

#include "Component.hpp"
#include "../Resources/Types.hpp"

namespace EngineQ
{
	class Renderable : public Component
	{
	private:
		std::unique_ptr<Graphics::ShaderProperties> forwardShader;
		std::unique_ptr<Graphics::ShaderProperties> deferredShader;
		Graphics::Mesh* mesh;
		
	public:
		Renderable(Scripting::ScriptEngine& scriptEngine, Entity& entity);
		virtual ComponentType GetType() const override;

		void SetForwardShader(Resources::Resource<Graphics::Shader> shader);
		Graphics::ShaderProperties* GetForwardShader() const;

		void SetDeferredShader(Resources::Resource<Graphics::Shader> shader);
		Graphics::ShaderProperties* GetDeferredShader() const;

		
		Graphics::Mesh* GetMesh() const;
		void SetMesh(Graphics::Mesh* mesh);
	};
}

#endif // !ENGINEQ_RENDERABLE_HPP