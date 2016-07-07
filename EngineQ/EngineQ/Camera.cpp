#include "Camera.hpp" 
#include "Entity.hpp"
#include "Utils.hpp"

namespace EngineQ
{


	bool Camera::CalculateInvertedProjectionMatrix() const
	{
		return calculateInvertedProjectionMatrix;
	}

	void Camera::CalculateInvertedProjectionMatrix(bool value)
	{
		calculateInvertedProjectionMatrix = value;
	}

	bool Camera::CalculateProjectionMatrix() const
	{
		return calculateProjectionMatrix;
	}

	void Camera::CalculateProjectionMatrix(bool value)
	{
		calculateProjectionMatrix = value;
		if (calculateProjectionMatrix)
			CalculateInvertedProjectionMatrix(true);
	}

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

	Camera::Camera(Scripting::ScriptEngine& scriptEngine, Entity& entity)
		: Component{ scriptEngine, scriptEngine.GetCameraClass(), entity }, fov(45.0f), aspectRatio(4 / 3.0f)
	{

	}

	ComponentType Camera::GetType() const
	{
		return ComponentType::Camera;
	}

	Math::Matrix4 Camera::ProjectionMatrix()
	{
		if (CalculateProjectionMatrix())
		{
			projectionMatrix = Math::Matrix4::CreateFrustum(Math::Utils::DegToRad(FOV()), AspectRatio(), 0.1f, 100.0f);
			CalculateProjectionMatrix(false);
		}
		return projectionMatrix;
	}

	Math::Matrix4 Camera::ViewMatrix()
	{
		return GetEntity().GetTransform().GetGlobalMatrix().GetInversed();
	}

	Math::Matrix4 Camera::InvertedViewMatrix()
	{
		return GetEntity().GetTransform().GetGlobalMatrix();
	}

	Math::Matrix4 Camera::InvertedProjectionMatrix()
	{
		if (CalculateInvertedProjectionMatrix())
		{
			invertedProjectionMatrix = ProjectionMatrix().GetInversed();
			CalculateInvertedProjectionMatrix(false);
		}
		return invertedProjectionMatrix;
	}
}
