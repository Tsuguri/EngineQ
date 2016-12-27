#include "Moveable.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		namespace Implementation
		{
			void Moveable::SetPosition(const Math::Vector3& position)
			{
				this->position = position;
				matrixChanged = true;
			}

			Math::Vector3 Moveable::GetPosition() const
			{
				return position;
			}

			void Moveable::SetScale(const Math::Vector3& scale)
			{
				this->scale = scale;
				matrixChanged = true;
			}

			Math::Vector3 Moveable::GetScale() const
			{
				return scale;
			}

			void Moveable::SetRotation(const Math::Quaternion& rotation)
			{
				this->rotation = rotation;
				matrixChanged = true;
			}

			Math::Quaternion Moveable::GetRotation() const
			{
				return rotation;
			}

			Math::Matrix4 Moveable::GetLocalMatrix()
			{
				if (matrixChanged)
				{
					matrix = Math::Matrix4::CreateTranslation(position) * Math::Matrix4::CreateRotation(rotation) * Math::Matrix4::CreateScale(scale);

					matrixChanged = false;
				}

				return matrix;
			}

			Math::Matrix4 Moveable::GetLocalMatrixInverse()
			{
				return matrix.GetInversed();
			}
		}
	}
}