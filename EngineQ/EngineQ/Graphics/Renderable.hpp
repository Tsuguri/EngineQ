#ifndef ENGINEQ_GRAPHICS_RENDERABLE_HPP
#define ENGINEQ_GRAPHICS_RENDERABLE_HPP

#include "../Scripting/ScriptEngine.hpp"
#include "../Component.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"

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

			Shader* GetForwardShader() const;
			void SetForwardShader(Shader* shader);
			Mesh* GetModel() const;
			void SetModel(Mesh* mesh);
		};
	}
}

#endif // ENGINEQ_GRAPHICS_RENDERABLE_HPP