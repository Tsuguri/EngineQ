#include "Light.hpp"

#include "../Scripting/ScriptEngine.hpp"
#include "../Serialization/Serializer.hpp"
#include "../Serialization/Deserializer.hpp"
#include "Entity.hpp"
#include "Transform.hpp"
#include "Scene.hpp"
#include "../Resources/ResourceManager.hpp"
#include "../Engine.hpp"
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

	Math::Vector3 Light::GetPosition()
	{
		return GetEntity().GetTransform().GetPosition();
	}

	EngineShaderProperties * Light::GetShaderProperties() const
	{
		return shaderProperties.get();
	}

	Light::Light(Scripting::ScriptEngine& scriptEngine, Entity& entity, bool enabled)
		: Component{ ComponentType::Light, scriptEngine, scriptEngine.GetClass(Scripting::ScriptEngine::Class::Light), entity, enabled }
	{
		Init(static_cast<Graphics::ScreenDataProvider*>(this));
		scriptEngine.InvokeConstructor(GetManagedObject());
		shaderProperties = std::make_unique<EngineShaderProperties>(this->scriptEngine, entity.GetScene().GetEngine()->GetResourceManager().GetResource<Graphics::Shader>("11") );
	}
}