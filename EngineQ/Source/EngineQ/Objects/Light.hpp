#ifndef ENGINEQ_LIGHT_HPP
#define ENGINEQ_LIGHT_HPP

// Other projects
#include "EngineQRenderer/Graphics/Shadows/Light.hpp"
#include "EngineQRenderer/Graphics/Utils/ScreenDataProvider.hpp"

// This project
#include "Component.hpp"
#include "EngineQ/Graphics/EngineShaderProperties.hpp"


namespace EngineQ
{
	class Light final : public Component, public Graphics::Shadows::Light, public Graphics::ScreenDataProvider
	{
		Math::Vector2i textureSize = Math::Vector2i{ 1024, 1024 };
		std::unique_ptr<EngineShaderProperties> shaderProperties;
		bool castShadows = true;
	public:
		virtual Math::Vector2i GetScreenSize() const override;
		void SetShadowTextureSize(Math::Vector2i size);
		Math::Vector2i GetShadowTextureSize() const;

		/*
	#pragma region Serialization

		Light(Serialization::Deserializer& deserialzier);
		virtual void Serialize(Serialization::Serializer& serializer) const override;

	#pragma endregion
		*/

		virtual Math::Vector3 GetPosition() override;
		virtual Math::Vector3 GetDirection() override;
		virtual Math::Matrix4 GetViewMatrix() override;

		virtual EngineShaderProperties* GetShaderProperties() const override;

		virtual bool GetCastShadows() const override;

		virtual void SetLightType(Type type) override;

		void SetCastShadows(bool val);
		Light(Scripting::ScriptEngine& scriptEngine, Entity& entity, bool enabled);
		virtual ~Light();
	};
}

#endif // !ENGINEQ_LIGHT_HPP
