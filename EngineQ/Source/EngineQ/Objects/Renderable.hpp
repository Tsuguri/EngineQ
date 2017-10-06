#ifndef ENGINEQ_RENDERABLE_HPP
#define ENGINEQ_RENDERABLE_HPP

// Standard includes
#include <memory>

// Other projects
#include "EngineQCommon/Math/Vector3.hpp"
#include "EngineQCommon/Resources/Resource.hpp"
#include "EngineQRenderer/Graphics/Types.hpp"
#include "EngineQRenderer/Graphics/Renderable.hpp"
#include "EngineQRenderer/Graphics/Mesh.hpp"

// This project
#include "Component.hpp"
#include "EngineQ/Resources/Types.hpp"
#include "EngineQ/Graphics/EngineShaderProperties.hpp"


namespace EngineQ
{
	class Renderable final : public Component, public Graphics::Renderable
	{
	private:
		std::unique_ptr<EngineShaderProperties> forwardShader;
		std::unique_ptr<EngineShaderProperties> deferredShader;
		Resources::Resource<Graphics::Mesh> mesh;

	public:
		Renderable(Scripting::ScriptEngine& scriptEngine, Entity& entity, bool enabled);
		virtual ~Renderable();

		void SetForwardShader(Resources::Resource<Graphics::Shader> shader);
		virtual EngineShaderProperties* GetForwardShader() const override;
		
		void SetDeferredShader(Resources::Resource<Graphics::Shader> shader);
		virtual EngineShaderProperties* GetDeferredShader() const override;
		
		virtual Resources::Resource<Graphics::Mesh> GetMesh() const override;
		void SetMesh(Resources::Resource<Graphics::Mesh> mesh);

		Math::Vector3 GetPosition() override;

		Math::Matrix4 GetGlobalMatrix() override;
	};
}

#endif // !ENGINEQ_RENDERABLE_HPP