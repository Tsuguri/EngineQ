#include "Light.hpp"

// Other projects
#include "EngineQRenderer/Graphics/Shadows/Light.hpp"

// This project
#include "Entity.hpp"
#include "Transform.hpp"
#include "Scene.hpp"
#include "EngineQ/Engine.hpp"
#include "EngineQ/Resources/ResourceManager.hpp"
#include "EngineQ/Scripting/ScriptEngine.hpp"
#include "EngineQ/Serialization/Serializer.hpp"
#include "EngineQ/Serialization/Deserializer.hpp"


namespace EngineQ
{
	/*
#pragma region Serialization

	Light::Light(Serialization::Deserializer& deserialzier) :
		Component{ deserialzier }
	{
	}

	void Light::Serialize(Serialization::Serializer& serializer) const
	{
		Component::Serialize(serializer);
	}

#pragma endregion
	*/

	Math::Vector2i Light::GetScreenSize() const
	{
		return textureSize;
	}

	void Light::SetShadowTextureSize(Math::Vector2i size)
	{
		if (textureSize != size)
		{
			textureSize = size;
			Init(this);
		}
	}

	Math::Vector2i Light::GetShadowTextureSize() const
	{
		return textureSize;
	}

	Math::Vector3 Light::GetPosition()
	{
		return GetEntity().GetTransform().GetGlobalPosition();
	}

	Math::Vector3 Light::GetDirection()
	{
		return this->entity.GetTransform().GetGlobalRotation() * Math::Vector3::GetForward();
	}
	
	Math::Matrix4 Light::GetViewMatrix()
	{
		return this->entity.GetTransform().GetGlobalMatrixInverse();
	}

	EngineShaderProperties * Light::GetShaderProperties() const
	{
		return shaderProperties.get();
	}

	bool Light::GetCastShadows() const
	{
		return castShadows;
	}

	void Light::SetCastShadows(bool val)
	{
		castShadows = val;
	}

	Light::Light(Scripting::ScriptEngine& scriptEngine, Entity& entity, bool enabled)
		: Component{ ComponentType::Light, scriptEngine, scriptEngine.GetClass(Scripting::ScriptEngine::Class::Light), entity, enabled }
	{
		Init(static_cast<Graphics::ScreenDataProvider*>(this));
		shaderProperties = std::make_unique<EngineShaderProperties>(this->scriptEngine, entity.GetScene().GetEngine()->GetResourceManager().GetResource<Graphics::Shader>("LightDepthRender") );
	}
}