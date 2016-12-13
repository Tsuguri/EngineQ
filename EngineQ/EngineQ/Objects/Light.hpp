#ifndef ENGINEQ_LIGHT_HPP
#define ENGINEQ_LIGHT_HPP

#include "Component.hpp"
#include "Graphics\Shadows\Light.hpp"
#include "Graphics\Utils\ScreenDataProvider.hpp"
#include "../EngineShaderProperties.hpp"

namespace EngineQ
{
	class Light final : public Component,public Graphics::Shadows::Light, Graphics::Utils::ScreenDataProvider
	{
		Math::Vector2i textureSize = Math::Vector2i{ 1024,1024 };
		std::unique_ptr<EngineShaderProperties> shaderProperties;

	public:
		virtual Math::Vector2i GetScreenSize() const override;
		void SetShadowTextureSize(Math::Vector2i size);

		/*
	#pragma region Serialization

		Light(Serialization::Deserializer& deserialzier);
		virtual void Serialize(Serialization::Serializer& serializer) const override;

	#pragma endregion
		*/

		virtual Math::Vector3 GetPosition() override;

		virtual EngineShaderProperties* GetShaderProperties() const override;

		Light(Scripting::ScriptEngine& scriptEngine, Entity& entity, bool enabled);
	};
}

#endif // !ENGINEQ_LIGHT_HPP
