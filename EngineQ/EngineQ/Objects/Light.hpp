#ifndef ENGINEQ_LIGHT_HPP
#define ENGINEQ_LIGHT_HPP

#include "Component.hpp"
#include "Graphics\Shadows\Light.hpp"
#include "Graphics\Utils\ScreenDataProvider.hpp"

namespace EngineQ
{
	class Light final : public Component,public Graphics::Shadows::Light, Graphics::Utils::ScreenDataProvider
	{
		Math::Vector2i textureSize = Math::Vector2i{ 1024,1024 };
	public:
		virtual Math::Vector2i GetScreenSize() const;
		void SetShadowTextureSize(Math::Vector2i size);
		/*
	#pragma region Serialization

		Light(Serialization::Deserializer& deserialzier);
		virtual void Serialize(Serialization::Serializer& serializer) const override;

	#pragma endregion
		*/

		Light(Scripting::ScriptEngine& scriptEngine, Entity& entity, bool enabled);
	};
}

#endif // !ENGINEQ_LIGHT_HPP
