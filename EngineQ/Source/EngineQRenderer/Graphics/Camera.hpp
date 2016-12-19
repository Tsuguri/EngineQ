#ifndef ENGINEQ_GRAPHICS_CAMERA_HPP
#define ENGINEQ_GRAPHICS_CAMERA_HPP

// Other projects
#include "EngineQCommon/Math/Matrix4.hpp"


namespace EngineQ
{
	namespace Graphics
	{
		class Camera
		{
		public:
			virtual float GetAspectRatio() const = 0;
			virtual float GetFieldOfView() const = 0;

			virtual Math::Matrix4 GetProjectionMatrix() = 0;
			virtual Math::Matrix4 GetProjectionMatrixInverse() = 0;

			virtual Math::Matrix4 GetViewMatrix() = 0;
			virtual Math::Matrix4 GetViewMatrixInverse() = 0;

			virtual Math::Vector3 GetPosition() = 0;
		};
	}
}
#endif