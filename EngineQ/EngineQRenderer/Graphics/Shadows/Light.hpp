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
				Math::Matrix4 lightMatrix;
			//protected:
			public:
				void Init(ScreenDataProvider* dataProvider);

				Light() = default;

				void RenderDepthMap(const std::vector<Renderable*>& renderables) const;

				Resources::Resource<Texture> GetDepthTexture();

				virtual Math::Vector3 GetPosition() = 0;

				virtual ShaderProperties* GetShaderProperties() const = 0;

				virtual bool GetCastShadows() = 0;
			};
		}
	}
}
#endif // !ENGINEQ_GRAPHICS_SHADOWS_LIGHT_HPP

