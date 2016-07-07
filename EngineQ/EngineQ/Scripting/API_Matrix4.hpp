#ifndef ENGINEQ_SCRIPTING_API_MATRIX4_HPP
#define ENGINEQ_SCRIPTING_API_MATRIX4_HPP

#include "ScriptEngine.hpp"

#include "../Math/Matrix4.hpp"

namespace EngineQ
{
	namespace Scripting
	{
		using namespace EngineQ::Math;

		class API_Matrix4
		{
		public:
			static void API_Determinant(const Matrix4& matrix, Real& value);
			static void API_Inversed(const Matrix4& matrix, Matrix4& value);
			static void API_Transpose(Matrix4& value);
			static void API_CreateRotation(const Quaternion& quaternion, Matrix4& value);
			static void API_CreateFrustum(Real fovy, Real aspect, Real near, Real far, Matrix4& value);
			static void API_CreateLookAt(const Vector3& cameraPosition, const Vector3& cameraTarget, const Vector3& upVector, Matrix4& value);
			static void API_TransformVector(const Matrix4& matrix, const Vector3& vector, Vector3& value);
			static void API_TransformPosition(const Matrix4& matrix, const Vector3& position, Vector3& value);
			static void API_TransformNormal(const Matrix4& matrix, const Vector3& normal, Vector3& value);
			static void API_TransformPerspective(const Matrix4& matrix, const Vector3& vector, Vector3& value);
			static void API_AddMatrix(const Matrix4& lhs, const Matrix4& rhs, Matrix4& value);
			static void API_SubtractMatrix(const Matrix4& lhs, const Matrix4& rhs, Matrix4& value);
			static void API_MultiplyScalar(const Matrix4& lhs, Real scalar, Matrix4& value);
			static void API_MultiplyVector4(const Matrix4& lhs, const Vector4& rhs, Vector4& value);
			static void API_MultiplyMatrix(const Matrix4& lhs, const Matrix4& rhs, Matrix4& value);
			static void API_DivideScalar(const Matrix4& lhs, Real rhs, Matrix4& value);
			
			static void API_Register(ScriptEngine& scriptEngine);
		};
	}
}

#endif // !ENGINEQ_SCRIPTING_API_MATRIX3_HPP
