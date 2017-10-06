#ifndef ENGINEQ_GRAPHICS_SHADOWS_DIRECTIONAL_SHADOWCASTER_HPP
#define ENGINEQ_GRAPHICS_SHADOWS_DIRECTIONAL_SHADOWCASTER_HPP

// Standard includes
#include <memory>

// This project
#include "EngineQRenderer/Graphics/Texture.hpp"
#include "EngineQRenderer/Graphics/Types.hpp"
#include "ShadowCaster.hpp"
#include "EngineQRenderer/Graphics/Utils/ScreenDataProvider.hpp"
#include "EngineQRenderer/Graphics/ShaderProperties.hpp"
#include "Types.hpp"


namespace EngineQ
{
	namespace Graphics
	{
		namespace Shadows
		{
			class DirectionalShadowCaster : public ShadowCaster
			{

			private:
				Math::Matrix4 GetLightMatrix();

				float distance = 0.0f;
				float range = 10.0f;
				float nearPlane = 0.1f;
				float farPlane = 30.0f;

				std::unique_ptr<Graphics::Framebuffer> framebuffer;
				Resources::Resource<Texture> depthTexture;
			
			public:
				virtual void Init(ScreenDataProvider* dataProvider) override;

				virtual void SetLightDataInShader(const ShaderProperties::Light& lightProperties, Light* light) override;

				virtual void RenderDepthMap(const std::vector<Renderable*>& renderables, ShaderProperties* shader, Light* light) override;
				virtual void Deinitialize() override;

				virtual float GetNearPlane() const override;
				virtual void SetNearPlane(float value) override;
				virtual float GetFarPlane() const override;
				virtual void SetFarPlane(float value) override;
				virtual float GetRange() const override;
				virtual void SetRange(float value) override;

			};
		}
	}
}

#endif // !ENGINEQ_GRAPHICS_SHADOWS_DIRECTIONAL_SHADOWCASTER_HPP
