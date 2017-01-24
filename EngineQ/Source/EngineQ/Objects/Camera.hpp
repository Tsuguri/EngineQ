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
		
		/// <summary>
		/// Sets whether to use custom projection matrix.
		/// </summary>
		/// <param name="value">Value to set.</param>
		void SetUsingCustomProjectionMatrix(bool value);

		/// <summary>
		/// Returns current aspect ratio.
		/// </summary>
		/// <returns>Current aspect ratio.</returns>
		virtual float GetAspectRatio() const override;

		/// <summary>
		/// Sets current aspect ratio.
		/// </summary>
		/// <param name="value">Aspect ratio to set.</param>
		void SetAspectRatio(float value);

		/// <summary>
		/// Returns current field of view.
		/// </summary>
		/// <returns>Current field of view in degrees.</returns>
		virtual float GetFieldOfView() const override;

		/// <summary>
		/// Sets current field of view.
		/// </summary>
		/// <param name="value">Field of view in degrees to set.</param>
		void SetFieldOfView(float value);

		/// <summary>
		/// Returns near clipping plane distance.
		/// </summary>
		/// <returns>Near clipping plane distance.</returns>
		float GetNearDistance() const;

		/// <summary>
		/// Sets near clipping plane distance.
		/// </summary>
		/// <param name="distance">Near clipping plane distance to set.</param>
		void SetNearDistance(float distance);

		/// <summary>
		/// Returns far clipping plane distance.
		/// </summary>
		/// <returns>Far clipping plane distance.</returns>
		float GetFarDistance() const;

		/// <summary>
		/// Sets far clipping plane distance.
		/// </summary>
		/// <param name="distance">Far clipping plane distance to set.</param>
		void SetFarDistance(float distance);

		/// <summary>
		/// Returns current custom projection matrix.
		/// </summary>
		/// <returns>Current custom projection matrix.</returns>
		Math::Matrix4 GetCustomProjectionMatrix() const;

		/// <summary>
		/// Sets current custom projection matrix.
		/// UsingCustomProjectionMatrix must be set to true in order for this matrix to be used.
		/// </summary>
		/// <param name="matrix">Current custom projection matrix to set.</param>
		void SetCustomProjectionMatrix(const Math::Matrix4& matrix);

		/// <summary>
		/// Returns current projection matrix.
		/// Matrix is recalculated if necessary. 
		/// </summary>
		/// <returns>Current projection matrix.</returns>
		virtual Math::Matrix4 GetProjectionMatrix() override;

		/// <summary>
		/// Returns current projection matrix inverse.
		/// Matrix is recalculated if necessary.
		/// </summary>
		/// <returns>Current projection matrix inverse.</returns>
		virtual Math::Matrix4 GetProjectionMatrixInverse() override;

		/// <summary>
		/// Returns current view matrix.
		/// Matrix is recalculated if necessary. 
		/// </summary>
		/// <returns>Current view matrix.</returns>
		virtual Math::Matrix4 GetViewMatrix() override;

		/// <summary>
		/// Returns current view matrix inverse.
		/// Matrix is recalculated if necessary. 
		/// </summary>
		/// <returns>Current view matrix inverse.</returns>
		virtual Math::Matrix4 GetViewMatrixInverse() override;

		/// <summary>
		/// Returns camera position.
		/// </summary>
		/// <returns>Camera position.</returns>
		virtual Math::Vector3 GetPosition() override;
	};
}

#endif // !ENGINEQ_CAMERA_HPP
