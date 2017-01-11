#ifndef ENGINEQ_CAMERA_HPP
#define ENGINEQ_CAMERA_HPP

// Other projects
#include "EngineQCommon/Math/Matrix4.hpp"
#include "EngineQRenderer/Graphics/Camera.hpp"

// This project
#include "Types.hpp"
#include "Component.hpp"
#include "EngineQ/Scripting/Types.hpp"
#include "EngineQ/Serialization/Types.hpp"


namespace EngineQ
{
	/// <summary>
	/// Component providing Camera functionality for <see cref="Entity"/>. 
	/// </summary>
	class Camera final : public Component, public Graphics::Camera
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

		/// <summary>
		/// Checks if is using custom projection matrix.
		/// </summary>
		/// <returns>true if is using custom projection matrix.</returns>
		bool IsUsingCustomProjectionMatrix() const;
		void SetUsingCustomProjectionMatrix(bool value);

		virtual float GetAspectRatio() const override;
		void SetAspectRatio(float value);

		virtual float GetFieldOfView() const override;
		void SetFieldOfView(float value);

		float GetNearDistance() const;
		void SetNewarDistance(float distance);

		float GetFarDistance() const;
		void SetFarDistance(float distance);

		Math::Matrix4 GetCustomProjectionMatrix() const;
		void SetCustomProjectionMatrix(const Math::Matrix4& matrix);

		virtual Math::Matrix4 GetProjectionMatrix() override;
		virtual Math::Matrix4 GetProjectionMatrixInverse() override;

		virtual Math::Matrix4 GetViewMatrix() override;
		virtual Math::Matrix4 GetViewMatrixInverse() override;

		virtual Math::Vector3 GetPosition() override;
	};
}

#endif // !ENGINEQ_CAMERA_HPP
