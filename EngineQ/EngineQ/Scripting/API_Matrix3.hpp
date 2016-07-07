#ifndef ENGINEQ_SCRIPTING_API_MATRIX3_HPP
#define ENGINEQ_SCRIPTING_API_MATRIX3_HPP

#include "ScriptEngine.hpp"

#include "../Math/Matrix3.hpp"

namespace EngineQ
{
	namespace Scripting
	{
		using namespace EngineQ::Math;

		class API_Matrix3
		{
		public:
			static void API_Inverse(const Matrix3& matrix, Matrix3& value);
			static void API_Determinant(const Matrix3& matrix, Real& value);
			static void API_Transpose(Matrix3& value);
			static void API_MultiplyMatrix(const Matrix3& lhs, const Matrix3& rhs, Matrix3& value);
			static void API_MultiplyVector3(const Matrix3& lhs, const Vector3& rhs, Vector3& value);
			static void API_MultiplyScalar(const Matrix3& lhs, Real rhs, Matrix3& value);
			static void API_DivideScalar(const Matrix3& lhs, Real rhs, Matrix3& value);
			static void API_Equal(const Matrix3& lhs, const Matrix3& rhs, bool& value);
			static void API_NotEqual(const Matrix3& lhs, const Matrix3& rhs, bool& value);
			
			static void API_Register(ScriptEngine& scriptEngine);
		};
	}
}

#endif // !ENGINEQ_SCRIPTING_API_MATRIX3_HPP
