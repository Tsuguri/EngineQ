#include "API_Matrix4.hpp"

#include "ScriptEngine.hpp"

#include <Math/Vector3.hpp>
#include <Math/Vector4.hpp>
#include <Math/Matrix4.hpp>

using namespace EngineQ::Math;

namespace EngineQ
{
	namespace Scripting
	{
		void API_Matrix4::API_Determinant(const Matrix4& matrix, Real& value)
		{
			value = matrix.GetDeterminant();
		}

		void API_Matrix4::API_Inversed(const Matrix4& matrix, Matrix4& value)
		{
			value = matrix.GetInversed();
		}

		void API_Matrix4::API_Transpose(Matrix4& value)
		{
			value.Transpose();
		}

		void API_Matrix4::API_CreateRotation(const Quaternion& quaternion, Matrix4& value)
		{
			value = Matrix4::CreateRotation(quaternion);
		}

		void API_Matrix4::API_CreateFrustum(Real fovy, Real aspect, Real near, Real far, Matrix4& value)
		{
			value = Matrix4::CreateFrustum(fovy, aspect, near, far);
		}

		void API_Matrix4::API_CreateLookAt(const Vector3& cameraPosition, const Vector3& cameraTarget, const Vector3& upVector, Matrix4& value)
		{
			value = Matrix4::CreateLookAt(cameraPosition, cameraTarget, upVector);
		}

		void API_Matrix4::API_TransformVector(const Matrix4& matrix, const Vector3& vector, Vector3& value)
		{
			value = Matrix4::TransformVector(matrix, vector);
		}

		void API_Matrix4::API_TransformPosition(const Matrix4& matrix, const Vector3& position, Vector3& value)
		{
			value = Matrix4::TransformPosition(matrix, position);
		}

		void API_Matrix4::API_TransformNormal(const Matrix4& matrix, const Vector3& normal, Vector3& value)
		{
			value = Matrix4::TransformNormal(matrix, normal);
		}

		void API_Matrix4::API_TransformPerspective(const Matrix4& matrix, const Vector3& vector, Vector3& value)
		{
			value = Matrix4::TransformPerspective(matrix, vector);
		}

		void API_Matrix4::API_AddMatrix(const Matrix4& lhs, const Matrix4& rhs, Matrix4& value)
		{
			value = lhs + rhs;
		}

		void API_Matrix4::API_SubtractMatrix(const Matrix4& lhs, const Matrix4& rhs, Matrix4& value)
		{
			value = lhs - rhs;
		}

		void API_Matrix4::API_MultiplyScalar(const Matrix4& lhs, Real scalar, Matrix4& value)
		{
			value = lhs * scalar;
		}

		void API_Matrix4::API_MultiplyVector4(const Matrix4& lhs, const Vector4& rhs, Vector4& value)
		{
			value = lhs * rhs;
		}

		void API_Matrix4::API_MultiplyMatrix(const Matrix4& lhs, const Matrix4& rhs, Matrix4& value)
		{
			value = lhs * rhs;
		}

		void API_Matrix4::API_DivideScalar(const Matrix4& lhs, Real rhs, Matrix4& value)
		{
			value = lhs / rhs;
		}

		void API_Matrix4::API_Register(ScriptEngine& scriptEngine)
		{
			scriptEngine.API_Register("EngineQ.Math.Matrix4::API_Determinant", API_Determinant);
			scriptEngine.API_Register("EngineQ.Math.Matrix4::API_Inversed", API_Inversed);
			scriptEngine.API_Register("EngineQ.Math.Matrix4::API_Transpose", API_Transpose);
			scriptEngine.API_Register("EngineQ.Math.Matrix4::API_CreateRotation", API_CreateRotation);
			scriptEngine.API_Register("EngineQ.Math.Matrix4::API_CreateFrustum", API_CreateFrustum);
			scriptEngine.API_Register("EngineQ.Math.Matrix4::API_CreateLookAt", API_CreateLookAt);
			scriptEngine.API_Register("EngineQ.Math.Matrix4::API_TransformVector", API_TransformVector);
			scriptEngine.API_Register("EngineQ.Math.Matrix4::API_TransformPosition", API_TransformPosition);
			scriptEngine.API_Register("EngineQ.Math.Matrix4::API_TransformNormal", API_TransformNormal);
			scriptEngine.API_Register("EngineQ.Math.Matrix4::API_TransformPerspective", API_TransformPerspective);
			scriptEngine.API_Register("EngineQ.Math.Matrix4::API_AddMatrix", API_AddMatrix);
			scriptEngine.API_Register("EngineQ.Math.Matrix4::API_SubtractMatrix", API_SubtractMatrix);
			scriptEngine.API_Register("EngineQ.Math.Matrix4::API_MultiplyScalar", API_MultiplyScalar);
			scriptEngine.API_Register("EngineQ.Math.Matrix4::API_MultiplyVector4", API_MultiplyVector4);
			scriptEngine.API_Register("EngineQ.Math.Matrix4::API_MultiplyMatrix", API_MultiplyMatrix);
			scriptEngine.API_Register("EngineQ.Math.Matrix4::API_DivideScalar", API_DivideScalar);
		}
	}
}