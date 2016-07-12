#ifndef ENGINEQ_GRAPHICS_RENDERABLE_HPP
#define ENGINEQ_GRAPHICS_RENDERABLE_HPP
#include "Component.hpp"
#include "Graphics/Shader.hpp"
#include "Mesh.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		class Renderable : public Component
		{
			Shader* forwardShader;
			Mesh* model;

		public:
			Renderable(Scripting::ScriptEngine& scriptEngine, Entity& entity);
			virtual ComponentType GetType() const override;

			Shader* ForwardShader() const;
			void ForwardShader(Shader* shader);
			Mesh* Model() const;
			void Model(Mesh* mesh);
		};
	}
}

#endif // ENGINEQ_GRAPHICS_RENDERABLE_HPP