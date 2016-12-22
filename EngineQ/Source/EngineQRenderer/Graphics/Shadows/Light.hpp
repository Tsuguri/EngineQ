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
				enum LightType
				{
					Directional = 0,
					Point = 1,
					Spot = 2
				};
			private:

				GLuint depthMapFBO;
				Resources::Resource<Texture> depthTexture;
				ScreenDataProvider* screenDataProvider = nullptr;
				LightType type = LightType::Directional;
				Math::Vector2i size = 2 * Math::Vector2i{ 1024, 1024 };
			
			public:
				void Init(ScreenDataProvider* dataProvider);

				Light() = default;

				void RenderDepthMap(const std::vector<Renderable*>& renderables) const;

				Resources::Resource<Texture> GetDepthTexture();

				Math::Matrix4 GetLightMatrix() const;

				virtual Math::Vector3 GetPosition() const = 0;

				virtual ShaderProperties* GetShaderProperties() const = 0;

				virtual bool GetCastShadows() = 0;

				void SetLightType(LightType type);

				LightType GetLightType() const;
			};
		}
	}
}
#endif // !ENGINEQ_GRAPHICS_SHADOWS_LIGHT_HPP

