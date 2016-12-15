#include "stdafx.h"
#include "CppUnitTest.h"

#include <locale>
#include <codecvt>
#include <string>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

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


namespace MathTests
{		
	TEST_CLASS(QuaternionTests)
	{
	public:
		
		TEST_METHOD(AreEquivalent_1)
		{
			Quaternion q1{ 1, 0.2f, 0.3f, 0.0f };
			Quaternion q2{ 1, 0.2f, 0.3f, 0.0f };

			Assert::IsTrue(Quaternion::AreEquivalent(q1, q2));
		}

		TEST_METHOD(AreEquivalent_2)
		{
			Quaternion q1{ 1, 0.4f, 0.3f, 0.0f };
			Quaternion q2{ 1, 0.2f, 0.3f, 0.0f };

			Assert::IsFalse(Quaternion::AreEquivalent(q1, q2));
		}

		TEST_METHOD(AreEquivalent_3)
		{
			Quaternion q1{ 1, 0.2f + Utils::EPS<Real> / 2.0f, 0.3f, 0.0f };
			Quaternion q2{ 1, 0.2f, 0.3f, 0.0f };

			Assert::IsTrue(Quaternion::AreEquivalent(q1, q2));
		}

		TEST_METHOD(AreEquivalent_4)
		{
			Quaternion q1{ 1, 0.2f + Utils::EPS<Real> / 2.0f, 0.3f, 0.0f };
			Quaternion q2{ -1, -0.2f, -0.3f, -0.0f };

			Assert::IsTrue(Quaternion::AreEquivalent(q1, q2));
		}

		TEST_METHOD(MultiplyVector_1)
		{
			Quaternion q1 = Quaternion::GetIdentity();
			Vector3 v1 = Vector3::GetUp();
		
			Vector3 v2 = q1 * v1;
			Assert::AreEqual(v1, v2);
		}

		TEST_METHOD(MultiplyVector_2)
		{
			Quaternion q1 = Quaternion::CreateRotationX(Utils::PI<Real> / 2.0f);
			Vector3 v1 = Vector3::GetUp();

			Vector3 v2 = q1 * v1;
			Vector3 v3{ 0.0f, 0.0f, 1.0f };

			Assert::IsTrue((v3 - v2).GetLengthSquared() < Utils::EPS<Real>);
		}

		TEST_METHOD(MultiplyVector_3)
		{
			Quaternion q1 = Quaternion::CreateRotationX(Utils::PI<Real> / 2.0f);
			Vector3 v1 = Vector3::GetUp();

			Vector3 v2 = q1 * v1;
			Vector3 v3{ 0.0f, 0.0f, 1.0f };

			Assert::IsTrue((v3 - v2).GetLengthSquared() < Utils::EPS<Real>);
		}

		TEST_METHOD(GetEulerAngles_1)
		{
			Vector3 v1{ 2.0f, 1.0f, -1.0f };
			Quaternion q1 = Quaternion::CreateFromEuler(v1);

			Vector3 v2 = q1.GetEulerAngles();

			Quaternion q2 = Quaternion::CreateFromEuler(v2);

			Assert::IsTrue(Quaternion::AreEquivalent(q1, q2));
		}

		TEST_METHOD(GetEulerAngles_2)
		{
			Vector3 v1{ -5.0f, 10.0f, 1.64f };
			Quaternion q1 = Quaternion::CreateFromEuler(v1);

			Vector3 v2 = q1.GetEulerAngles();

			Quaternion q2 = Quaternion::CreateFromEuler(v2);

			Assert::IsTrue(Quaternion::AreEquivalent(q1, q2));
		}

		TEST_METHOD(GetAxisAngle_1)
		{
			Vector4 v1{ 2.0f, 1.0f, -1.0f, 5.0f };
			Quaternion q1 = Quaternion::CreateFromAxisAngle(static_cast<Vector3>(v1), v1.W);

			Vector4 v2 = q1.GetAxisAngle();

			Quaternion q2 = Quaternion::CreateFromAxisAngle(static_cast<Vector3>(v2), v2.W);

			Assert::IsTrue(Quaternion::AreEquivalent(q1, q2));
		}

		TEST_METHOD(GetAxisAngle_2)
		{
			Vector4 v1{ -5.0f, 10.0f, 1.64f, 15.0f };
			Quaternion q1 = Quaternion::CreateFromAxisAngle(static_cast<Vector3>(v1), v1.W);

			Vector4 v2 = q1.GetAxisAngle();

			Quaternion q2 = Quaternion::CreateFromAxisAngle(static_cast<Vector3>(v2), v2.W);

			Assert::IsTrue(Quaternion::AreEquivalent(q1, q2));
		}

		TEST_METHOD(Inversed_1)
		{
			Quaternion q1 = Quaternion::CreateFromEuler(3, -1.5, 2.1);
			Quaternion q2 = -q1;

			Vector3 v1{ 4.34f, 12.7f, -3.2f };
			Vector3 v2 = q1 * v1;
			Vector3 v3 = q2 * v2;

			Assert::IsTrue(Vector3::AreEqual(v1, v3));
		}
	};
}