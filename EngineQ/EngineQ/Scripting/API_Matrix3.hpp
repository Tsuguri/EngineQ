#ifndef ENGINEQ_SCRIPTING_API_MATRIX3_HPP
#define ENGINEQ_SCRIPTING_API_MATRIX3_HPP

#include "Types.hpp"
#include <Math/Types.hpp>

namespace EngineQ
{
	namespace Scripting
	{
		class API_Matrix3
		{
		public:
			static void API_Inverse(const Math::Matrix3& matrix, Math::Matrix3& value);
			static void API_Determinant(const Math::Matrix3& matrix, Math::Real& value);
			static void API_Transpose(Math::Matrix3& value);
			static void API_MultiplyMatrix(const Math::Matrix3& lhs, const Math::Matrix3& rhs, Math::Matrix3& value);
			static void API_MultiplyVector3(const Math::Matrix3& lhs, const Math::Vector3& rhs, Math::Vector3& value);
			static void API_MultiplyScalar(const Math::Matrix3& lhs, Math::Real rhs, Math::Matrix3& value);
			static void API_DivideScalar(const Math::Matrix3& lhs, Math::Real rhs, Math::Matrix3& value);
			static void API_Equal(const Math::Matrix3& lhs, const Math::Matrix3& rhs, bool& value);
			static void API_NotEqual(const Math::Matrix3& lhs, const Math::Matrix3& rhs, bool& value);
			
			static void API_Register(ScriptEngine& scriptEngine);
		};
	}
}

#endif // !ENGINEQ_SCRIPTING_API_MATRIX3_HPP
