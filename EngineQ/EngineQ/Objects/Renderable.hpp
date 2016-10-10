#ifndef ENGINEQ_RENDERABLE_HPP
#define ENGINEQ_RENDERABLE_HPP

#include <memory>

#include "../Graphics/Types.hpp"

#include "Component.hpp"

namespace EngineQ
{
	class Renderable : public Component
	{
		std::shared_ptr<Graphics::Shader> forwardShader;
		std::shared_ptr<Graphics::Shader> deferredShader;
		Graphics::Mesh* model;

	public:
		Renderable(Scripting::ScriptEngine& scriptEngine, Entity& entity);
		virtual ComponentType GetType() const override;

		Graphics::Shader* GetForwardShader() const;
		Graphics::Shader* GetDeferredShader() const;
		void SetForwardShader(std::shared_ptr<Graphics::Shader> shader);
		void SetDeferredShader(std::shared_ptr<Graphics::Shader> shader);
		Graphics::Mesh* GetModel() const;
		void SetModel(Graphics::Mesh* mesh);
	};
}

#endif // !ENGINEQ_RENDERABLE_HPP