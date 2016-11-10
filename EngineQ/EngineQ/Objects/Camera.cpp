#include "Camera.hpp"

#include "Entity.hpp"
#include "Transform.hpp"

#include "../Serialization/Serializer.hpp"
#include "../Serialization/Deserializer.hpp"
#include "../Scripting/ScriptEngine.hpp"
#include "../Math/Utilities.hpp"

#include "../Serialization/SerializationRules.hpp"

namespace EngineQ
{
/*
#pragma region Serialization

	Camera::Camera(Serialization::Deserializer& deserialzier) :
		Component{ deserialzier },
		fov{ deserialzier.GetValue<float>("fov") },
		aspectRatio{ deserialzier.GetValue<float>("aspect") }
	{

	}

	void Camera::Serialize(Serialization::Serializer& serializer) const
	{
		Component::Serialize(serializer);
		serializer.StoreValue("aspect", &this->aspectRatio);
		serializer.StoreValue("fov", &this->fov);
	}

#pragma endregion
*/

	bool Camera::GetCalculateInvertedProjectionMatrix() const
	{
		return calculateInvertedProjectionMatrix;
	}

	void Camera::SetCalculateInvertedProjectionMatrix(bool value)
	{
		calculateInvertedProjectionMatrix = value;
	}

	bool Camera::GetCalculateProjectionMatrix() const
	{
		return calculateProjectionMatrix;
	}

	void Camera::SetCalculateProjectionMatrix(bool value)
	{
		calculateProjectionMatrix = value;
		if (calculateProjectionMatrix)
			SetCalculateInvertedProjectionMatrix(true);
	}

	float Camera::GetAspectRatio() const
	{
		return aspectRatio;
	}

	void Camera::SetAspectRatio(float value)
	{
		if (aspectRatio == value)
			return;
		aspectRatio = value;
		SetCalculateProjectionMatrix(true);
	}

	float Camera::GetFOV() const
	{
		return fov;
	}

	void Camera::SetFOV(float value)
	{
		if (fov == value)
			return;
		fov = value;
		SetCalculateProjectionMatrix(true);
	}

	Camera::Camera(Scripting::ScriptEngine& scriptEngine, Entity& entity, bool enabled)
		: Component{ ComponentType::Camera, scriptEngine, scriptEngine.GetClass(Scripting::ScriptEngine::Class::Camera), entity, enabled }, fov(45.0f), aspectRatio(4 / 3.0f)
	{

	}
	
	Math::Matrix4 Camera::GetProjectionMatrix()
	{
		if (GetCalculateProjectionMatrix())
		{
			projectionMatrix = Math::Matrix4::CreateFrustum(Math::DegToRad(GetFOV()), GetAspectRatio(), 0.1f, 100.0f);
			SetCalculateProjectionMatrix(false);
		}
		return projectionMatrix;
	}

	Math::Matrix4 Camera::GetViewMatrix()
	{
		return GetEntity().GetTransform().GetGlobalMatrixInverse();
	}

	Math::Matrix4 Camera::GetInvertedViewMatrix()
	{
		return GetEntity().GetTransform().GetGlobalMatrix();
	}

	Math::Matrix4 Camera::GetInvertedProjectionMatrix()
	{
		if (GetCalculateInvertedProjectionMatrix())
		{
			invertedProjectionMatrix = GetProjectionMatrix().GetInversed();
			SetCalculateInvertedProjectionMatrix(false);
		}
		return invertedProjectionMatrix;
	}
}
