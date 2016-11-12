#ifndef ENGINEQ_RENDERABLE_HPP
#define ENGINEQ_RENDERABLE_HPP

#include <memory>

#include "../Graphics/Types.hpp"

#include "Component.hpp"
#include "../Resources/Types.hpp"

#include "../Resources/Resource.hpp"

#include "../Graphics/Renderable.hpp"

#include <Math\Vector3.hpp>
namespace EngineQ
{
	class Renderable final : public Component, public Graphics::Renderable
	{
	private:
		std::unique_ptr<Graphics::ShaderProperties> forwardShader;
		std::unique_ptr<Graphics::ShaderProperties> deferredShader;
		Resources::Resource<Graphics::Mesh> mesh;
		
	public:
		Renderable(Scripting::ScriptEngine& scriptEngine, Entity& entity, bool enabled);
		virtual ~Renderable();

		void SetForwardShader(Resources::Resource<Graphics::Shader> shader);
		 Graphics::ShaderProperties* GetForwardShader() const override;

		void SetDeferredShader(Resources::Resource<Graphics::Shader> shader);
		Graphics::ShaderProperties* GetDeferredShader() const override;

		
		Resources::Resource<Graphics::Mesh> GetMesh() const override;
		void SetMesh(Resources::Resource<Graphics::Mesh> mesh);

		Math::Vector3 GetPosition() override;
	};
}

#endif // !ENGINEQ_RENDERABLE_HPP