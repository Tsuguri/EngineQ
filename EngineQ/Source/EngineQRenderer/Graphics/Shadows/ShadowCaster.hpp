#ifndef ENGINEQ_GRAPHICS_SHADOWS_SHADOWCASTER_HPP
#define ENGINEQ_GRAPHICS_SHADOWS_SHADOWCASTER_HPP

// Standard includes
#include <memory>

// This project
#include "EngineQRenderer/Graphics/Texture.hpp"
#include "EngineQRenderer/Graphics/Types.hpp"
#include "EngineQRenderer/Graphics/Utils/ScreenDataProvider.hpp"
#include "EngineQRenderer/Graphics/ShaderProperties.hpp"
#include "Types.hpp"


namespace EngineQ
{
	namespace Graphics
	{
		namespace Shadows
		{
			class ShadowCaster
			{
			protected:
				void Render(const std::vector<Renderable*>& renderables, ShaderProperties* shader);
			public:
				virtual void Init(ScreenDataProvider* dataProvider) = 0;

				virtual void SetLightDataInShader(const ShaderProperties::Light& lightProperties, Light* light) = 0;

				virtual void RenderDepthMap(const std::vector<Renderable*>& renderables, ShaderProperties* shader, Light* light) = 0;

				virtual void Deinitialize() = 0;
				
				virtual float GetNearPlane() const;
				virtual void SetNearPlane(float value);
				virtual float GetFarPlane() const;
				virtual void SetFarPlane(float value);
				virtual float GetRange() const;
				virtual void SetRange(float value);
				virtual float GetDistance() const;
				virtual void SetDistance(float value);


			};
		}
	}
}

#endif // !ENGINEQ_GRAPHICS_SHADOWS_SHADOWCASTER_HPP
