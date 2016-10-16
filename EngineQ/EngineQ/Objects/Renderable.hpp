#ifndef ENGINEQ_RENDERABLE_HPP
#define ENGINEQ_RENDERABLE_HPP

#include <memory>

#include "../Graphics/Types.hpp"

#include "Component.hpp"

namespace EngineQ
{
	class Renderable : public Component
	{
		std::unique_ptr<Graphics::ShaderProperties> forwardShader;
		std::unique_ptr<Graphics::ShaderProperties> deferredShader;
		Graphics::Mesh* mesh;

	public:
		Renderable(Scripting::ScriptEngine& scriptEngine, Entity& entity);
		virtual ComponentType GetType() const override;

		void SetForwardShader(Graphics::Shader& shader);
		void SetForwardShader(std::unique_ptr<Graphics::ShaderProperties> shader);
		Graphics::ShaderProperties* GetForwardShader() const;
		
		void SetDeferredShader(Graphics::Shader& shader);
		void SetDeferredShader(std::unique_ptr<Graphics::ShaderProperties> shader);
		Graphics::ShaderProperties* GetDeferredShader() const;

		
		Graphics::Mesh* GetMesh() const;
		void SetMesh(Graphics::Mesh* mesh);
	};
}

#endif // !ENGINEQ_RENDERABLE_HPP