#ifndef ENGINEQ_LIGHT_HPP
#define ENGINEQ_LIGHT_HPP

// Other projects
#include "EngineQRenderer/Graphics/Shadows/Light.hpp"
#include "EngineQRenderer/Graphics/Utils/ScreenDataProvider.hpp"

// This project
#include "Component.hpp"
#include "EngineQ/EngineShaderProperties.hpp"


namespace EngineQ
{
	class Light final : public Component, public Graphics::Shadows::Light, public Graphics::ScreenDataProvider
	{
		Math::Vector2i textureSize = Math::Vector2i{ 1024,1024 };
		std::unique_ptr<EngineShaderProperties> shaderProperties;
		bool castShadows = true;
	public:
		virtual Math::Vector2i GetScreenSize() const override;
		void SetShadowTextureSize(Math::Vector2i size);

		/*
	#pragma region Serialization

		Light(Serialization::Deserializer& deserialzier);
		virtual void Serialize(Serialization::Serializer& serializer) const override;

	#pragma endregion
		*/

		virtual Math::Vector3 GetPosition() const override;

		virtual EngineShaderProperties* GetShaderProperties() const override;

		virtual bool GetCastShadows() override;

		void SetCastShadows(bool val);
		Light(Scripting::ScriptEngine& scriptEngine, Entity& entity, bool enabled);
	};
}

#endif // !ENGINEQ_LIGHT_HPP
