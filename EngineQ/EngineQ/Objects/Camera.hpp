#ifndef ENGINEQ_CAMERA_HPP
#define ENGINEQ_CAMERA_HPP

#include "Types.hpp"
#include <Math/Matrix4.hpp>
#include "../Scripting/Types.hpp"
#include "../Serialization/Types.hpp"

#include "Component.hpp"
#include "../Graphics/Camera.hpp"

namespace EngineQ
{
	class Camera final : public Component,public Graphics::Camera
	{
	private:

		Math::Matrix4 projectionMatrix;

		Math::Matrix4 invertedProjectionMatrix;

		bool calculateProjectionMatrix = true;
		//	bool calculateViewProjectionMatrix = true;

		float fov;
		float aspectRatio;

		//	bool calculateRotation = true;

		bool calculateInvertedProjectionMatrix = true;

		bool GetCalculateInvertedProjectionMatrix() const;
		void SetCalculateInvertedProjectionMatrix(bool value);

		bool GetCalculateProjectionMatrix() const;
		void SetCalculateProjectionMatrix(bool value);
		
	public:
		/*
	#pragma region Serialization

		Camera(Serialization::Deserializer& deserialzier);
		virtual void Serialize(Serialization::Serializer& serializer) const override;

	#pragma endregion
		*/

		Camera(Scripting::ScriptEngine& scriptEngine, Entity& entity, bool enabled);

		float GetAspectRatio() const override;
		void SetAspectRatio(float value);

		float GetFOV() const override;
		void SetFOV(float value);

		Math::Matrix4 GetProjectionMatrix() override;
		Math::Matrix4 GetInvertedViewMatrix() override;

		Math::Matrix4 GetViewMatrix() override;
		Math::Matrix4 GetInvertedProjectionMatrix() override;
	};
}

#endif // !ENGINEQ_CAMERA_HPP
