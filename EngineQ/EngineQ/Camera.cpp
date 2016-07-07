#include "Camera.hpp" 
#include "Entity.hpp"
#include "Utils.hpp"

namespace EngineQ
{
	bool Camera::CalculateInvertedViewMatrix() const
	{
		return calculateInvertedViewMatrix;
	}

	void Camera::CalculateInvertedViewMatrix(bool value)
	{
		calculateInvertedViewMatrix = value;
	}

	bool Camera::CalculateInvertedProjectionMatrix() const
	{
		return calculateInvertedProjectionMatrix;
	}

	void Camera::CalculateInvertedProjectionMatrix(bool value)
	{
		calculateInvertedProjectionMatrix = value;
	}

	bool Camera::CalculateViewMatrix() const
	{
		return calculateViewMatrix;
	}

	void Camera::CalculateViewMatrix(bool value)
	{
		calculateViewMatrix = value;
		if(calculateViewMatrix)
		{
			CalculateViewProjectionMatrix(true);
			CalculateInvertedViewMatrix(true);
		}
	}

	bool Camera::CalculateProjectionMatrix() const
	{
		return calculateProjectionMatrix;
	}

	void Camera::CalculateProjectionMatrix(bool value)
	{
		calculateProjectionMatrix = value;
		if(calculateProjectionMatrix)
		{
			CalculateViewProjectionMatrix(true);
			CalculateViewProjectionMatrix(true);
		}
	}

	bool Camera::CalculateViewProjectionMatrix() const
	{
		return calculateViewProjectionMatrix;
	}

	void Camera::CalculateViewProjectionMatrix(bool value)
	{
		calculateViewProjectionMatrix = value;
	}

	//bool Camera::CalculateRotation() const
	//{
	//	return calculateRotation;
	//}

	//void Camera::CalculateRotation(bool value)
	//{
	//	calculateRotation = value;
	//	if (calculateRotation)
	//		CalculateViewMatrix(true);
	//}

	float Camera::AspectRatio() const
	{
		return aspectRatio;
	}

	void Camera::AspectRatio(float value)
	{
		if (aspectRatio == value)
			return;
		aspectRatio = value;
		CalculateProjectionMatrix(true);
	}

	float Camera::FOV() const
	{
		return fov;
	}

	void Camera::FOV(float value)
	{
		if (fov == value)
			return;
		fov = value;
		CalculateProjectionMatrix(true);
	}

	//float Camera::RotationX() const
	//{
	//	return rotationX;
	//}

	//void Camera::RotationX(float value)
	//{
	//	if (rotationX == value)
	//		return;
	//	rotationX = value;
	//	if (rotationX < -180.0f)
	//		rotationX += 360.0f;
	//	if (rotationX > 180.0f)
	//		rotationX -= 360.0f;
	//	CalculateRotation(true);
	//}

	//float Camera::RotationY() const
	//{
	//	return rotationY;
	//}

	//void Camera::RotationY(float value)
	//{
	//	if (rotationY == value)
	//		return;

	//	rotationY = value;

	//	if (rotationY < -180.0f)
	//		rotationY += 360.0f;

	//	if (rotationY >= 180.0f)
	//		rotationY -= 360.0f;

	//	CalculateRotation(true);
	//}

	Camera::Camera(Scripting::ScriptEngine& scriptEngine, Entity& entity)
		: Component{ scriptEngine, scriptEngine.GetCameraClass(), entity }, fov(45.0f), aspectRatio(16 / 9.0f), distance(0.0f)
	{

	}

	ComponentType Camera::GetType() const
	{
		return ComponentType::Camera;
	}

	float Camera::Distance() const
	{
		return distance;
	}

	void Camera::Distance(float value)
	{
		if (distance == value)
			return;
		distance = value;
		CalculateViewMatrix(true);
	}

	Math::Matrix4 Camera::ProjectionMatrix()
	{
		if(CalculateProjectionMatrix())
		{
			projectionMatrix = Math::Matrix4::CreateFrustum(Math::Utils::DegToRad( FOV()), AspectRatio(), 0.1f, 100.0f);
			CalculateProjectionMatrix(false);
		}
		return projectionMatrix;
	}
						

	Math::Matrix4 Camera::ViewMatrix()
	{
		if(CalculateViewMatrix())
		{
			auto& tr = GetEntity().GetTransform();
			viewMatrix = Math::Matrix4::CreateTranslation(-GetEntity().GetTransform().GetPosition())*Math::Matrix4::CreateRotation(GetEntity().GetTransform().GetRotation())*Math::Matrix4::CreateTranslation(0.0f,0.0f,-Distance());
			CalculateViewMatrix(false);
		}
		return viewMatrix;
	}

	Math::Matrix4 Camera::ViewProjectionMatrix()
	{
		if(CalculateViewProjectionMatrix())
		{
			viewProjectionMatrix = ViewMatrix()*ProjectionMatrix();
			CalculateViewProjectionMatrix(false);
		}
		return viewProjectionMatrix;
	}

	Math::Matrix4 Camera::InvertedViewMatrix()
	{
		if(CalculateInvertedViewMatrix())
		{
			invertedViewMatrix = ViewMatrix().GetInversed();
			CalculateInvertedViewMatrix(false);
		}
		return invertedViewMatrix;
	}

	Math::Matrix4 Camera::InvertedProjectionMatrix()
	{
		if(CalculateInvertedProjectionMatrix())
		{
			invertedProjectionMatrix = ProjectionMatrix().GetInversed();
			CalculateInvertedProjectionMatrix(false);
		}
		return invertedProjectionMatrix;
	}
}
