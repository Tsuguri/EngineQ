#ifndef ENGINEQ_SCRIPTING_API_MATRIX4_HPP
#define ENGINEQ_SCRIPTING_API_MATRIX4_HPP

#include "Types.hpp"
#include "../Math/Types.hpp"

namespace EngineQ
{
	namespace Scripting
	{
		class API_Matrix4
		{
		public:
			static void API_Determinant(const Math::Matrix4& matrix, Math::Real& value);
			static void API_Inversed(const Math::Matrix4& matrix, Math::Matrix4& value);
			static void API_Transpose(Math::Matrix4& value);
			static void API_CreateRotation(const Math::Quaternion& quaternion, Math::Matrix4& value);
			static void API_CreateFrustum(Math::Real fovy, Math::Real aspect, Math::Real near, Math::Real far, Math::Matrix4& value);
			static void API_CreateLookAt(const Math::Vector3& cameraPosition, const Math::Vector3& cameraTarget, const Math::Vector3& upVector, Math::Matrix4& value);
			static void API_TransformVector(const Math::Matrix4& matrix, const Math::Vector3& vector, Math::Vector3& value);
			static void API_TransformPosition(const Math::Matrix4& matrix, const Math::Vector3& position, Math::Vector3& value);
			static void API_TransformNormal(const Math::Matrix4& matrix, const Math::Vector3& normal, Math::Vector3& value);
			static void API_TransformPerspective(const Math::Matrix4& matrix, const Math::Vector3& vector, Math::Vector3& value);
			static void API_AddMatrix(const Math::Matrix4& lhs, const Math::Matrix4& rhs, Math::Matrix4& value);
			static void API_SubtractMatrix(const Math::Matrix4& lhs, const Math::Matrix4& rhs, Math::Matrix4& value);
			static void API_MultiplyScalar(const Math::Matrix4& lhs, Math::Real scalar, Math::Matrix4& value);
			static void API_MultiplyVector4(const Math::Matrix4& lhs, const Math::Vector4& rhs, Math::Vector4& value);
			static void API_MultiplyMatrix(const Math::Matrix4& lhs, const Math::Matrix4& rhs, Math::Matrix4& value);
			static void API_DivideScalar(const Math::Matrix4& lhs, Math::Real rhs, Math::Matrix4& value);
			
			static void API_Register(ScriptEngine& scriptEngine);
		};
	}
}

#endif // !ENGINEQ_SCRIPTING_API_MATRIX3_HPP
