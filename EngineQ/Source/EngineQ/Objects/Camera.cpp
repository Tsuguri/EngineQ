#include "Camera.hpp"

// Other projects
#include "EngineQCommon/Math/Utils.hpp"

// This project
#include "Entity.hpp"
#include "Transform.hpp"
#include "EngineQ/Serialization/Serializer.hpp"
#include "EngineQ/Serialization/Deserializer.hpp"
#include "EngineQ/Scripting/ScriptEngine.hpp"
#include "EngineQ/Serialization/SerializationRules.hpp"


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

	Camera::Camera(Scripting::ScriptEngine& scriptEngine, Entity& entity, bool enabled)
		: Component{ ComponentType::Camera, scriptEngine, scriptEngine.GetClass(Scripting::ScriptEngine::Class::Camera), entity, enabled }
	{
	}

	bool Camera::IsUsingCustomProjectionMatrix() const
	{
		return this->useCustomProjectionmatrix;
	}

	void Camera::SetUsingCustomProjectionMatrix(bool value)
	{
		if (this->useCustomProjectionmatrix == value)
			return;

		this->useCustomProjectionmatrix = value;

		if (value)
		{
			this->projectionMatrix = this->customProjectionMatrix;
			
			this->calculateProjectionMatrix = false;
			this->VoidProjectionMatrixInverse();
		}
		else
		{
			this->VoidProjectionMatrix();
		}
	}

	Math::Matrix4 Camera::GetCustomProjectionMatrix() const
	{
		return this->customProjectionMatrix;
	}

	void Camera::SetCustomProjectionMatrix(const Math::Matrix4& matrix)
	{
		this->customProjectionMatrix = matrix;

		if (this->useCustomProjectionmatrix)
		{
			this->projectionMatrix = matrix;
			this->VoidProjectionMatrixInverse();
		}
	}

	void Camera::VoidProjectionMatrixInverse()
	{
		calculateProjectionMatrixInverse = true;
	}
	
	void Camera::VoidProjectionMatrix()
	{
		calculateProjectionMatrix = !useCustomProjectionmatrix;

		if (calculateProjectionMatrix)
			VoidProjectionMatrixInverse();
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
		VoidProjectionMatrix();
	}

	float Camera::GetFieldOfView() const
	{
		return fov;
	}

	void Camera::SetFieldOfView(float value)
	{
		if (fov == value)
			return;

		fov = value;
		VoidProjectionMatrix();
	}


	float Camera::GetNearDistance() const
	{
		return this->nearDistance;
	}

	void Camera::SetNearDistance(float distance)
	{
		if (this->nearDistance == distance)
			return;

		this->nearDistance = distance;
		VoidProjectionMatrix();
	}

	float Camera::GetFarDistance() const
	{
		return this->farDistance;
	}

	void Camera::SetFarDistance(float distance)
	{
		if (this->farDistance == distance)
			return;

		this->farDistance = distance;
		VoidProjectionMatrix();
	}

	Math::Matrix4 Camera::GetProjectionMatrix()
	{
		if (calculateProjectionMatrix)
		{
			projectionMatrix = Math::Matrix4::CreateFrustum(Math::Utils::DegToRad(GetFieldOfView()), GetAspectRatio(), GetNearDistance(), GetFarDistance());
			calculateProjectionMatrix = false;
		}

		return projectionMatrix;
	}

	Math::Matrix4 Camera::GetViewMatrix()
	{
		return GetEntity().GetTransform().GetGlobalMatrixInverse();
	}

	Math::Matrix4 Camera::GetViewMatrixInverse()
	{
		return GetEntity().GetTransform().GetGlobalMatrix();
	}

	Math::Matrix4 Camera::GetProjectionMatrixInverse()
	{
		if (this->calculateProjectionMatrixInverse)
		{
			invertedProjectionMatrix = GetProjectionMatrix().GetInversed();
			this->calculateProjectionMatrixInverse = false;
		}

		return invertedProjectionMatrix;
	}

	Math::Vector3 Camera::GetPosition()
	{
		return GetEntity().GetTransform().GetPosition();
	}
}
