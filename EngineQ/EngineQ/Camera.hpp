#ifndef ENGINEQ_CAMERA_H 
#define ENGINEQ_CAMERA_H 

#include "Component.hpp" 
#include "Math/Matrix4.hpp"

namespace EngineQ
{
	class Camera : public Component
	{
	private:

		Math::Matrix4 projectionMatrix;
		Math::Matrix4 viewMatrix;

		Math::Matrix4 viewProjectionMatrix;

		Math::Matrix4 invertedViewMatrix;
		
		Math::Matrix4 invertedProjectionMatrix;

		bool calculateProjectionMatrix = true;
		bool calculateViewMatrix = true;
		bool calculateViewProjectionMatrix = true;

		//Math::Vector3 position = Math::Vector3::GetZero();
		//Math::Quaternion rotation = Math::Quaternion::GetIdentity();

		float fov;
		float aspectRatio;
		float distance;

		//float rotationX;
		//float rotationY;

		bool calculateRotation = true;

		bool calculateInvertedViewMatrix = true;
		bool calculateInvertedProjectionMatrix = true;

		bool CalculateInvertedViewMatrix() const;
		void CalculateInvertedViewMatrix(bool value);

		bool CalculateInvertedProjectionMatrix() const;
		void CalculateInvertedProjectionMatrix(bool value);

		bool CalculateViewMatrix() const;
		void CalculateViewMatrix(bool value);

		bool CalculateProjectionMatrix() const;
		void CalculateProjectionMatrix(bool value);

		bool CalculateViewProjectionMatrix() const;
		void CalculateViewProjectionMatrix(bool value);

		//bool CalculateRotation() const;
		//void CalculateRotation(bool value);

		float AspectRatio() const;
		void AspectRatio(float value);

		float FOV() const;
		void FOV(float value);

		//float RotationX() const;
		//void RotationX(float value);

		//float RotationY() const;
		//void RotationY(float value);



	public:
		Camera(Scripting::ScriptEngine& scriptEngine, Entity& entity);
		virtual ComponentType GetType() const override;


		float Distance() const;
		void Distance(float value);

		Math::Matrix4 ProjectionMatrix();

		Math::Matrix4 ViewMatrix();

		Math::Matrix4 ViewProjectionMatrix();

		Math::Matrix4 InvertedViewMatrix();

		Math::Matrix4 InvertedProjectionMatrix();
	};
}

#endif // !ENGINEQ_CAMERA_H 