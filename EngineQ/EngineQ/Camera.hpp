#ifndef ENGINEQ_CAMERA_HPP
#define ENGINEQ_CAMERA_HPP

#include "Component.hpp" 
#include "Math/Matrix4.hpp"

namespace EngineQ
{
	class Camera : public Component
	{
	private:

		Math::Matrix4 projectionMatrix;

		Math::Matrix4 invertedProjectionMatrix;

		bool calculateProjectionMatrix = true;
		bool calculateViewProjectionMatrix = true;

		float fov;
		float aspectRatio;

		bool calculateRotation = true;

		bool calculateInvertedProjectionMatrix = true;

		bool GetCalculateInvertedProjectionMatrix() const;
		void SetCalculateInvertedProjectionMatrix(bool value);

		bool GetCalculateProjectionMatrix() const;
		void SetCalculateProjectionMatrix(bool value);

		float GetAspectRatio() const;
		void SetAspectRatio(float value);

		float GetFOV() const;
		void SetFOV(float value);

	public:
	#pragma region Serialization

		Camera(Serialization::Deserializer& deserialzier);
		virtual void Serialize(Serialization::Serializer& serializer) const override;

	#pragma endregion

		Camera(Scripting::ScriptEngine& scriptEngine, Entity& entity);
		virtual ComponentType GetType() const override;

		Math::Matrix4 GetProjectionMatrix();

		Math::Matrix4 GetViewMatrix();

		Math::Matrix4 GetInvertedViewMatrix();

		Math::Matrix4 GetInvertedProjectionMatrix();
	};
}

#endif // !ENGINEQ_CAMERA_HPP
