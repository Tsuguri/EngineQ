#ifndef ENGINEQ_CAMERA_HPP
#define ENGINEQ_CAMERA_HPP

#include "Types.hpp"
#include "../Math/Matrix4.hpp"
#include "../Scripting/Types.hpp"
#include "../Serialization/Types.hpp"

#include "Component.hpp"

namespace EngineQ
{
	class Camera final : public Component
	{
	private:

		Math::Matrix4 customProjectionMatrix = Math::Matrix4::GetIdentity();

		Math::Matrix4 projectionMatrix = Math::Matrix4::GetIdentity();
		Math::Matrix4 invertedProjectionMatrix = Math::Matrix4::GetIdentity();

		float fov = 45.0f;
		float aspectRatio = 4.0f / 3.0f;

		float nearDistance = 0.01f;
		float farDistance = 100.0f;

		bool useCustomProjectionmatrix = false;
	
		bool calculateProjectionMatrix = true;
		bool calculateProjectionMatrixInverse = true;

		void VoidProjectionMatrix();
		void VoidProjectionMatrixInverse();
		
	public:
		/*
	#pragma region Serialization

		Camera(Serialization::Deserializer& deserialzier);
		virtual void Serialize(Serialization::Serializer& serializer) const override;

	#pragma endregion
		*/

		Camera(Scripting::ScriptEngine& scriptEngine, Entity& entity, bool enabled);

		bool IsUsingCustomProjectionMatrix() const;
		void SetUsingCustomProjectionMatrix(bool value);

		float GetAspectRatio() const;
		void SetAspectRatio(float value);

		float GetFieldOfView() const;
		void SetFieldOfView(float value);

		float GetNearDistance() const;
		void SetNewarDistance(float distance);

		float GetFarDistance() const;
		void SetFarDistance(float distance);

		Math::Matrix4 GetCustomProjectionMatrix() const;
		void SetCustomProjectionMatrix(const Math::Matrix4& matrix);

		Math::Matrix4 GetProjectionMatrix();
		Math::Matrix4 GetProjectionMatrixInverse();

		Math::Matrix4 GetViewMatrix();
		Math::Matrix4 GetViewMatrixInverse();
	};
}

#endif // !ENGINEQ_CAMERA_HPP
