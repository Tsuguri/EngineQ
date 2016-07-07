#ifndef ENGINEQ_SCRIPTING_API_QUATERNION_HPP
#define ENGINEQ_SCRIPTING_API_QUATERNION_HPP

#include "ScriptEngine.hpp"

#include "../Math/Quaternion.hpp"

namespace EngineQ
{
	namespace Scripting
	{
		using namespace EngineQ::Math;

		class API_Quaternion
		{
		public:
			static void API_GetEulerAngles(const Quaternion& quaternion, Vector3& eulerAngles);
			static void API_Normalize(Quaternion& quaternion);
			static void API_CreateFromAxisAngle(Real x, Real y, Real z, Real angle, Quaternion& quaternion);
			static void API_CreateRotationX(Real angle, Quaternion& quaternion);
			static void API_CreateRotationY(Real angle, Quaternion& quaternion);
			static void API_CreateRotationZ(Real angle, Quaternion& quaternion);
			static void API_CreateFromEuler(Real x, Real y, Real z, Quaternion& quaternion);
			static void API_MultiplyQuaternion(const Quaternion& q1, const Quaternion& q2, Quaternion& quaternion);
			static void API_MultiplyVector4(const Quaternion& q, const Vector4& v, Vector4& vector);
			static void API_MultiplyVector3(const Quaternion& q, const Vector3& v, Vector3& vector);

			static void API_Register(ScriptEngine& scriptEngine);
		};
	}
}


#endif // !ENGINEQ_SCRIPTING_API_QUATERNION_HPP
