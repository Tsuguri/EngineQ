#ifndef ENGINEQ_GRAPHICS_SHADOWS_POINT_SHADOWCASTER_HPP
#define ENGINEQ_GRAPHICS_SHADOWS_POINT_SHADOWCASTER_HPP

// Standard includes
#include <memory>

// This project
#include "EngineQRenderer/Graphics/Texture.hpp"
#include "EngineQRenderer/Graphics/Types.hpp"
#include "ShadowCaster.hpp"


namespace EngineQ
{
	namespace Graphics
	{
		namespace Shadows
		{
			class PointShadowCaster : public ShadowCaster
			{

			private:
				static bool matricesComputed;
				static Math::Matrix4 cameraMatrices[6];


				float nearPlane = 0.1f;
				float farPlane = 90.0f;

				//std::unique_ptr<Graphics::Framebuffer> framebuffer;
				std::unique_ptr<Graphics::Framebuffer> framebuffers[6];
				//GLuint framebuffer;
				Resources::Resource<CubeTexture> depthTexture;

				Math::Matrix4 GetCameraMatrice(int face);
				void DrawFace(const std::vector<Renderable*>& renderables, ShaderProperties* shader, Light* light, int i);
			public:
				virtual void Init(ScreenDataProvider* dataProvider) override;

				virtual void SetLightDataInShader(const ShaderProperties::Light& lightProperties, Light* light) override;

				virtual void RenderDepthMap(const std::vector<Renderable*>& renderables, ShaderProperties* shader, Light* light) override;
				virtual void Deinitialize() override;

				virtual float GetNearPlane() const override;
				virtual void SetNearPlane(float value) override;
				virtual float GetFarPlane() const override;
				virtual void SetFarPlane(float value) override;

			};
		}
	}
}

#endif // !ENGINEQ_GRAPHICS_SHADOWS_POINT_SHADOWCASTER_HPP
