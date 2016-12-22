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
			if (!ResizeEventIsEmpty())
			{
				ResizeEventInvoke(size.X, size.Y);
			}
		}
	}

	Math::Vector3 Light::GetPosition() const
	{
		return GetEntity().GetTransform().GetPosition();
	}

	EngineShaderProperties * Light::GetShaderProperties() const
	{
		return shaderProperties.get();
	}

	bool Light::GetCastShadows()
	{
		return castShadows;
	}

	void Graphics::Shadows::Light::SetLightType(LightType type)
	{
		if (this->type != type)
		{
			this->type = type;
		}
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