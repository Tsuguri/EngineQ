#ifndef ENGINEQ_GRAPHICS_SHADOWS_LIGHT_HPP
#define ENGINEQ_GRAPHICS_SHADOWS_LIGHT_HPP

// Standard includes
#include <memory>

// Other projects
#include "EngineQCommon/Math/Vector2.hpp"

// This project
#include "EngineQRenderer/Graphics/Shadows/ShadowCaster.hpp"
#include "EngineQRenderer/Graphics/Framebuffer.hpp"
#include "EngineQRenderer/Graphics/Utils/ScreenDataProvider.hpp"
#include "EngineQRenderer/Graphics/ShaderProperties.hpp"


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
				std::unique_ptr<ShadowCaster> shadowCaster;

				ScreenDataProvider* screenDataProvider = nullptr;
				Type type = Type::Directional;

				Math::Vector3 ambient = Math::Vector3(1.0f);
				Math::Vector3 diffuse = Math::Vector3(1.0f);
				Math::Vector3 specular = Math::Vector3(1.0f);


			public:
				void Init(ScreenDataProvider* dataProvider);
				Light();
				virtual ~Light();

				void SetLightInShader(const ShaderProperties::Light& light);

				void RenderDepthMap(const std::vector<Renderable*>& renderables);

				float GetNearPlane() const;
				void SetNearPlane(float value);
				float GetFarPlane() const;
				void SetFarPlane(float value);
				float GetRange() const;
				void SetRange(float value);
				float GetDistance() const;
				void SetDistance(float value);

				virtual Math::Vector3 GetPosition() = 0;
				virtual Math::Vector3 GetDirection() = 0;
				virtual Math::Matrix4 GetViewMatrix() = 0;

				virtual ShaderProperties* GetShaderProperties() const = 0;

				virtual bool GetCastShadows() const = 0;

				void SetLightType(Type type);
				Type GetLightType() const;

				Math::Vector3 GetAmbientColor() const;
				void SetAmbientColor(Math::Vector3 color);

				Math::Vector3 GetDiffuseColor() const;
				void SetDiffuseColor(Math::Vector3 color);

				Math::Vector3 GetSpecularColor() const;
				void SetSpecularColor(Math::Vector3 color);

			protected:
				void UnsubscribeFromResize();

			};
		}
	}
}
#endif // !ENGINEQ_GRAPHICS_SHADOWS_LIGHT_HPP

