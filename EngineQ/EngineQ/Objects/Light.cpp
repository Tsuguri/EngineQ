#include "Light.hpp"

#include "../Scripting/ScriptEngine.hpp"
#include "../Serialization/Serializer.hpp"
#include "../Serialization/Deserializer.hpp"
#include "Entity.hpp"
#include "Scene.hpp"

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

	Light::Light(Scripting::ScriptEngine& scriptEngine, Entity& entity, bool enabled)
		: Component{ ComponentType::Light, scriptEngine, scriptEngine.GetClass(Scripting::ScriptEngine::Class::Light), entity, enabled }, Graphics::Shadows::Light(this)
	{
		// TMP
		Init();
		scriptEngine.InvokeConstructor(GetManagedObject());
	}
}