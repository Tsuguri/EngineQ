#include "Light.hpp"

// This project
#include "EngineQRenderer/Graphics/Renderable.hpp"
#include "EngineQRenderer/Graphics/Mesh.hpp"
#include "DirectionalShadowCaster.hpp"
#include "PointShadowCaster.hpp"


namespace EngineQ
{
	namespace Graphics
	{
		namespace Shadows
		{

			void Light::Init(ScreenDataProvider* dataProvider)
			{
				this->screenDataProvider = dataProvider;
				shadowCaster->Init(dataProvider);
			}

			void Light::UnsubscribeFromResize()
			{
				shadowCaster->Deinitialize();
			}

			Light::Light()
			{
				shadowCaster = std::make_unique<DirectionalShadowCaster>();
			}

			Light::~Light()
			{

			}

			void Light::SetLightInShader(const ShaderProperties::Light& light)
			{
				light.Position = GetPosition();
				light.Direction = GetDirection();
				light.Right = GetRight();
				light.Distance = GetDistance();

				light.Diffuse = GetDiffuseColor();
				light.Ambient = GetAmbientColor();
				light.Specular = GetSpecularColor();

				light.CastsShadows = GetCastShadows();

				light.FarPlane = GetFarPlane();
				light.LightType = (int)this->type;
				shadowCaster->SetLightDataInShader(light,this);
			}

			void Light::RenderDepthMap(const std::vector<Renderable*>& renderables)
			{
				auto shader = GetShaderProperties();
				if (shader == nullptr)
					return;
				shadowCaster->RenderDepthMap(renderables, shader,this);
			}

			float Light::GetNearPlane() const
			{
				return shadowCaster->GetNearPlane();
			}

			void Light::SetNearPlane(float value)
			{
				shadowCaster->SetNearPlane(value);
			}

			float Light::GetFarPlane() const
			{
				return shadowCaster->GetFarPlane();
			}

			void Light::SetFarPlane(float value)
			{
				shadowCaster->SetFarPlane(value);
			}

			float Light::GetRange() const
			{
				return shadowCaster->GetRange();
			}

			void Light::SetRange(float value)
			{
				shadowCaster->SetRange(value);
			}

			float Light::GetDistance() const
			{
				return shadowCaster->GetDistance();
			}

			void Light::SetDistance(float value)
			{
				shadowCaster->SetDistance(value);
			}

			void Light::SetLightType(Type type)
			{
				if (this->type != type)
				{
					this->type = type;

					switch (type)
					{
					case EngineQ::Graphics::Shadows::Light::Type::Directional:
						shadowCaster = std::make_unique<DirectionalShadowCaster>();
						shadowCaster->Init(screenDataProvider);
						break;
					case EngineQ::Graphics::Shadows::Light::Type::Point:
						shadowCaster = std::make_unique<PointShadowCaster>();
						shadowCaster->Init(screenDataProvider);
						break;
					case EngineQ::Graphics::Shadows::Light::Type::Spot:
						break;
					default:
						break;
					}


				}
			}

			Light::Type Light::GetLightType() const
			{
				return this->type;
			}

			Math::Vector3 Light::GetAmbientColor() const
			{
				return ambient;
			}

			void Light::SetAmbientColor(Math::Vector3 color)
			{
				this->ambient = color;
			}

			Math::Vector3 Light::GetDiffuseColor() const
			{
				return diffuse;
			}

			void Light::SetDiffuseColor(Math::Vector3 color)
			{
				this->diffuse = color;
			}

			Math::Vector3 Light::GetSpecularColor() const
			{
				return specular;
			}

			void Light::SetSpecularColor(Math::Vector3 color)
			{
				this->specular = color;
			}
		}
	}
}