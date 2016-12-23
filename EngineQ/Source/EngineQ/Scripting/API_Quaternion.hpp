#ifndef ENGINEQ_SCRIPTING_API_QUATERNION_HPP
#define ENGINEQ_SCRIPTING_API_QUATERNION_HPP

// Other projects
#include "EngineQCommon/Math/Types.hpp"

// This project
#include "Types.hpp"


namespace EngineQ
{
	namespace Scripting
	{
		class API_Quaternion
		{
		public:
			static void API_GetEulerAngles(const Math::Quaternion& quaternion, Math::Vector3& eulerAngles);
			static void API_GetAxisAngle(const Math::Quaternion& quaternion, Math::Vector4& axisAngle);
			static void API_Normalize(Math::Quaternion& quaternion);
			static void API_CreateFromAxisAngle(Math::Real x, Math::Real y, Math::Real z, Math::Real angle, Math::Quaternion& quaternion);
			static void API_CreateRotationX(Math::Real angle, Math::Quaternion& quaternion);
			static void API_CreateRotationY(Math::Real angle, Math::Quaternion& quaternion);
			static void API_CreateRotationZ(Math::Real angle, Math::Quaternion& quaternion);
			static void API_CreateFromEuler(Math::Real x, Math::Real y, Math::Real z, Math::Quaternion& quaternion);
			static void API_CreateLookAt(const Math::Vector3& sourcePoint, const Math::Vector3& targetPoint, const Math::Vector3& up, Math::Quaternion& quaternion);
			static void API_MultiplyQuaternion(const Math::Quaternion& q1, const Math::Quaternion& q2, Math::Quaternion& quaternion);
			static void API_MultiplyVector4(const Math::Quaternion& q, const Math::Vector4& v, Math::Vector4& vector);
			static void API_MultiplyVector3(const Math::Quaternion& q, const Math::Vector3& v, Math::Vector3& vector);

			static void API_Register(ScriptEngine& scriptEngine);
		};
	}
}


#endif // !ENGINEQ_SCRIPTING_API_QUATERNION_HPP
