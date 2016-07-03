#include "API_Quaternion.hpp"

namespace EngineQ
{
	namespace Scripting
	{
		void API_Quaternion::API_GetEulerAngles(const Quaternion& quaternion, Vector3& eulerAngles)
		{
			eulerAngles = quaternion.GetEulerAngles();
		}

		void API_Quaternion::API_Normalize(Quaternion& quaternion)
		{
			quaternion.Normalize();
		}

		void API_Quaternion::API_CreateFromAxisAngle(Real x, Real y, Real z, Real angle, Quaternion& quaternion)
		{
			quaternion = Quaternion::CreateFromAxisAngle(x, y, z, angle);
		}

		void API_Quaternion::API_CreateRotationX(Real angle, Quaternion& quaternion)
		{
			quaternion = Quaternion::CreateRotationX(angle);
		}

		void API_Quaternion::API_CreateRotationY(Real angle, Quaternion& quaternion)
		{
			quaternion = Quaternion::CreateRotationY(angle);
		}

		void API_Quaternion::API_CreateRotationZ(Real angle, Quaternion& quaternion)
		{
			quaternion = Quaternion::CreateRotationZ(angle);
		}

		void API_Quaternion::API_CreateFromEuler(Real x, Real y, Real z, Quaternion& quaternion)
		{
			quaternion = Quaternion::CreateFromEuler(x, y, z);
		}

		void API_Quaternion::API_MultiplyQuaternion(const Quaternion& q1, const Quaternion& q2, Quaternion& quaternion)
		{
			quaternion = q1 * q2;
		}

		void API_Quaternion::API_MultiplyVector4(const Quaternion& q, const Vector4& v, Vector4& vector)
		{
			vector = q * v;
		}

		void API_Quaternion::API_MultiplyVector3(const Quaternion& q, const Vector3& v, Vector3& vector)
		{
			vector = q * v;
		}

		void API_Quaternion::API_Register(ScriptEngine& scriptEngine)
		{
			scriptEngine.API_Register("EngineQ.Math.Quaternion::API_GetEulerAngles", API_GetEulerAngles);
			scriptEngine.API_Register("EngineQ.Math.Quaternion::API_Normalize", API_Normalize);
			scriptEngine.API_Register("EngineQ.Math.Quaternion::API_CreateFromAxisAngle", API_CreateFromAxisAngle);
			scriptEngine.API_Register("EngineQ.Math.Quaternion::API_CreateRotationX", API_CreateRotationX);
			scriptEngine.API_Register("EngineQ.Math.Quaternion::API_CreateRotationY", API_CreateRotationY);
			scriptEngine.API_Register("EngineQ.Math.Quaternion::API_CreateRotationZ", API_CreateRotationZ);
			scriptEngine.API_Register("EngineQ.Math.Quaternion::API_CreateFromEuler", API_CreateFromEuler);
			scriptEngine.API_Register("EngineQ.Math.Quaternion::API_MultiplyQuaternion", API_MultiplyQuaternion);
			scriptEngine.API_Register("EngineQ.Math.Quaternion::API_MultiplyVector4", API_MultiplyVector4);
			scriptEngine.API_Register("EngineQ.Math.Quaternion::API_MultiplyVector3", API_MultiplyVector3);
		}
	}
}
