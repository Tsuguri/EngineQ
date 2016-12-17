#ifndef ENGINEQ_GRAPHICS_SHADOWS_LIGHT_HPP
#define ENGINEQ_GRAPHICS_SHADOWS_LIGHT_HPP

#include <memory>
#include "../Framebuffer.hpp"
#include"../Utils/ScreenDataProvider.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		namespace Shadows
		{
			class Light
			{
				GLuint depthMapFBO;
				Resources::Resource<Texture> depthTexture;
				ScreenDataProvider* screenDataProvider = nullptr;
			public:
				void Init(ScreenDataProvider* dataProvider);

				Light() = default;

				void RenderDepthMap(const std::vector<Renderable*>& renderables) const;

				Resources::Resource<Texture> GetDepthTexture();

				Math::Matrix4 GetLightMatrix() const;

				virtual Math::Vector3 GetPosition() const = 0;

				virtual ShaderProperties* GetShaderProperties() const = 0;

				virtual bool GetCastShadows() = 0;
			};
		}
	}
}
#endif // !ENGINEQ_GRAPHICS_SHADOWS_LIGHT_HPP

