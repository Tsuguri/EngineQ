#ifndef ENGINEQ_GRAPHICS_IMPLEMENTATION_MOVEABLE_HPP
#define ENGINEQ_GRAPHICS_IMPLEMENTATION_MOVEABLE_HPP


#include "EngineQCommon/Math/Vector3.hpp"
#include "EngineQCommon/Math/Matrix4.hpp"
#include "EngineQCommon/Math/Quaternion.hpp"
#include "EngineQRenderer/Graphics/Shadows/Light.hpp"
#include "EngineQRenderer/Graphics/ShaderProperties.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		namespace Implementation
		{
			class Moveable
			{
				Math::Vector3 position = Math::Vector3::GetZero();
				Math::Vector3 scale = Math::Vector3::GetOne();
				Math::Quaternion rotation = Math::Quaternion::GetIdentity();

				Math::Matrix4 matrix;
				bool matrixChanged = false;

			public :
				void SetPosition(const Math::Vector3& position);
				Math::Vector3 GetPosition() const;

				void SetScale(const Math::Vector3& scale);
				Math::Vector3 GetScale() const;

				void SetRotation(const Math::Quaternion& rotation);
				Math::Quaternion GetRotation() const;

				Math::Matrix4 GetLocalMatrix();

				Math::Matrix4 GetLocalMatrixInverse();
			};
		}
	}
}
#endif // !ENGINEQ_GRAPHICS_IMPLEMENTATION_MOVEABLE_HPP
