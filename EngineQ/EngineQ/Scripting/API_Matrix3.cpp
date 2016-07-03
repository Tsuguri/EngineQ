#include "API_Matrix3.hpp"

namespace EngineQ
{
	namespace Scripting
	{
		using namespace EngineQ::Math;

		void API_Matrix3::API_Inverse(const Matrix3& matrix, Matrix3& value)
		{
			value = matrix.GetInversed();
		}

		void API_Matrix3::API_Determinant(const Matrix3& matrix, Real& value)
		{
			value = matrix.GetDeterminant();
		}

		void API_Matrix3::API_Transpose(Matrix3& value)
		{
			value.Transpose();
		}

		void API_Matrix3::API_MultiplyMatrix(const Matrix3& lhs, const Matrix3& rhs, Matrix3& value)
		{
			value = lhs * rhs;
		}

		void API_Matrix3::API_MultiplyVector3(const Matrix3& lhs, const Vector3& rhs, Vector3& value)
		{
			value = lhs * rhs;
		}

		void API_Matrix3::API_MultiplyScalar(const Matrix3& lhs, Real rhs, Matrix3& value)
		{
			value = lhs * rhs;
		}

		void API_Matrix3::API_DivideScalar(const Matrix3& lhs, Real rhs, Matrix3& value)
		{
			value = lhs / rhs;
		}

		void API_Matrix3::API_Equal(const Matrix3& lhs, const Matrix3& rhs, bool& value)
		{
			value = lhs == rhs;
		}

		void API_Matrix3::API_NotEqual(const Matrix3& lhs, const Matrix3& rhs, bool& value)
		{
			value = lhs != rhs;
		}

		void API_Matrix3::API_Register(ScriptEngine& scriptEngine)
		{
			scriptEngine.API_Register("EngineQ.Math.Matrix3::API_Inverse", API_Inverse);
			scriptEngine.API_Register("EngineQ.Math.Matrix3::API_Determinant", API_Determinant);
			scriptEngine.API_Register("EngineQ.Math.Matrix3::API_Transpose", API_Transpose);
			scriptEngine.API_Register("EngineQ.Math.Matrix3::API_MultiplyMatrix", API_MultiplyMatrix);
			scriptEngine.API_Register("EngineQ.Math.Matrix3::API_MultiplyVector3", API_MultiplyVector3);
			scriptEngine.API_Register("EngineQ.Math.Matrix3::API_MultiplyScalar", API_MultiplyScalar);
			scriptEngine.API_Register("EngineQ.Math.Matrix3::API_DivideScalar", API_DivideScalar);
			scriptEngine.API_Register("EngineQ.Math.Matrix3::API_Equal", API_Equal);
			scriptEngine.API_Register("EngineQ.Math.Matrix3::API_NotEqual", API_NotEqual);
		}
	}
}