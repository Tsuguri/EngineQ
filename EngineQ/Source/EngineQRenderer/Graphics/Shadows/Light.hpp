#ifndef ENGINEQ_GRAPHICS_SHADOWS_LIGHT_HPP
#define ENGINEQ_GRAPHICS_SHADOWS_LIGHT_HPP

// Standard includes
#include <memory>

// Other projects
#include "EngineQCommon/Math/Vector2.hpp"

// This project
#include "EngineQRenderer/Graphics/Framebuffer.hpp"
#include "EngineQRenderer/Graphics/Utils/ScreenDataProvider.hpp"


namespace EngineQ
{
	namespace Graphics
	{
		namespace Shadows
		{
			class Light
			{
			public:
				enum class Type
				{
					Directional = 0,
					Point = 1,
					Spot = 2
				};

			private:

				//GLuint depthMapFBO;
				std::unique_ptr<Graphics::Framebuffer> framebuffer;
				Resources::Resource<Texture> depthTexture;
				ScreenDataProvider* screenDataProvider = nullptr;
				Type type = Type::Directional;
				Math::Vector2i size = 2 * Math::Vector2i{ 1024, 1024 };
				
				float distance = 0.0f;
				float nearPlane = 0.1f;
				float farPlane = 15.0f;

			public:
				void Init(ScreenDataProvider* dataProvider);

				Light() = default;

				void RenderDepthMap(const std::vector<Renderable*>& renderables);

				Resources::Resource<Texture> GetDepthTexture();

				float GetNearPlane() const;
				float GetFarPlane() const;
				float GetDistance() const;

				Math::Matrix4 GetLightMatrix();

				virtual Math::Vector3 GetPosition() = 0;
				virtual Math::Vector3 GetDirection() = 0;
				virtual Math::Matrix4 GetViewMatrix() = 0;

				virtual ShaderProperties* GetShaderProperties() const = 0;

				virtual bool GetCastShadows() = 0;

				void SetLightType(Type type);

				Type GetLightType() const;
			};
		}
	}
}
#endif // !ENGINEQ_GRAPHICS_SHADOWS_LIGHT_HPP

