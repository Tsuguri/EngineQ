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

		bool CalculateInvertedProjectionMatrix() const;
		void CalculateInvertedProjectionMatrix(bool value);

		bool CalculateProjectionMatrix() const;
		void CalculateProjectionMatrix(bool value);

		float AspectRatio() const;
		void AspectRatio(float value);

		float FOV() const;
		void FOV(float value);

	public:
	#pragma region Serialization

		Camera(Serialization::Deserializer& deserialzier);
		virtual void Serialize(Serialization::Serializer& serializer) const override;

	#pragma endregion

		Camera(Scripting::ScriptEngine& scriptEngine, Entity& entity);
		virtual ComponentType GetType() const override;

		Math::Matrix4 ProjectionMatrix();

		Math::Matrix4 ViewMatrix();

		Math::Matrix4 InvertedViewMatrix();

		Math::Matrix4 InvertedProjectionMatrix();
	};
}

#endif // !ENGINEQ_CAMERA_HPP
