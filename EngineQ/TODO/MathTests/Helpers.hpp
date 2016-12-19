#pragma once

using namespace EngineQ::Math;

namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework
		{
			template<> inline std::wstring ToString<Quaternion>(const Quaternion& t) { RETURN_WIDE_STRING(t.ToString().c_str()); }
			template<> inline std::wstring ToString<Matrix3>(const Matrix3& t) { RETURN_WIDE_STRING(t.ToString().c_str()); }
			template<> inline std::wstring ToString<Matrix4>(const Matrix4& t) { RETURN_WIDE_STRING(t.ToString().c_str()); }
			template<> inline std::wstring ToString<Vector2>(const Vector2& t) { RETURN_WIDE_STRING(t.ToString().c_str()); }
			template<> inline std::wstring ToString<Vector3>(const Vector3& t) { RETURN_WIDE_STRING(t.ToString().c_str()); }
			template<> inline std::wstring ToString<Vector4>(const Vector4& t) { RETURN_WIDE_STRING(t.ToString().c_str()); }
		}
	}
}