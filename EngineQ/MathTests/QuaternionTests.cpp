#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "Helpers.hpp"

namespace MathTests
{
	TEST_CLASS(QuaternionTests)
	{
	public:

		TEST_METHOD(Equal_1)
		{
			Quaternion q1{ 1, 0.2f, 0.3f, 0.0f };
			Quaternion q2{ 1, 0.2f, 0.3f, 0.0f };

			Assert::AreEqual(q1, q2);
		}

		TEST_METHOD(Equal_2)
		{
			Quaternion q1{ 1, 0.2f + Utils::Eps<Real> / 2.0f, 0.3f, 0.0f };
			Quaternion q2{ 1, 0.2f, 0.3f, 0.0f };

			Assert::AreEqual(q1, q2);
		}

		TEST_METHOD(Equal_3)
		{
			Quaternion q1{ 1, 0.2f + Utils::Eps<Real> / 2.0f, 0.3f, 0.0f };
			Quaternion q2{ -1, -0.2f, -0.3f, -0.0f };

			Assert::AreEqual(q2, q1);
		}

		TEST_METHOD(NotEqual_1)
		{
			Quaternion q1{ 1, 0.4f, 0.3f, 0.0f };
			Quaternion q2{ 1, 0.2f, 0.3f, 0.0f };

			Assert::AreNotEqual(q1, q2);
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

			Assert::AreEqual(v3, v2);
		}

		TEST_METHOD(MultiplyVector_3)
		{
			Quaternion q1 = Quaternion::CreateRotationX(Utils::PI<Real> / 2.0f);
			Vector3 v1 = Vector3::GetUp();

			Vector3 v2 = q1 * v1;
			Vector3 v3{ 0.0f, 0.0f, 1.0f };

			Assert::AreEqual(v3, v2);
		}

		TEST_METHOD(GetEulerAngles_1)
		{
			Vector3 v1{ 2.0f, 1.0f, -1.0f };
			Quaternion q1 = Quaternion::CreateFromEuler(v1);

			Vector3 v2 = q1.GetEulerAngles();

			Quaternion q2 = Quaternion::CreateFromEuler(v2);

			Assert::AreEqual(q1, q2);
		}

		TEST_METHOD(GetEulerAngles_2)
		{
			Vector3 v1{ -5.0f, 10.0f, 1.64f };
			Quaternion q1 = Quaternion::CreateFromEuler(v1);

			Vector3 v2 = q1.GetEulerAngles();

			Quaternion q2 = Quaternion::CreateFromEuler(v2);

			Assert::AreEqual(q1, q2);
		}

		TEST_METHOD(GetAxisAngle_1)
		{
			Vector4 v1{ 2.0f, 1.0f, -1.0f, 5.0f };
			Quaternion q1 = Quaternion::CreateFromAxisAngle(static_cast<Vector3>(v1), v1.W);

			Vector4 v2 = q1.GetAxisAngle();

			Quaternion q2 = Quaternion::CreateFromAxisAngle(static_cast<Vector3>(v2), v2.W);

			Assert::AreEqual(q1, q2);
		}

		TEST_METHOD(GetAxisAngle_2)
		{
			Vector4 v1{ -5.0f, 10.0f, 1.64f, 15.0f };
			Quaternion q1 = Quaternion::CreateFromAxisAngle(static_cast<Vector3>(v1), v1.W);

			Vector4 v2 = q1.GetAxisAngle();

			Quaternion q2 = Quaternion::CreateFromAxisAngle(static_cast<Vector3>(v2), v2.W);

			Assert::AreEqual(q1, q2);
		}

		TEST_METHOD(Inversed_1)
		{
			Quaternion q1 = Quaternion::CreateFromEuler(3, -1.5, 2.1);
			Quaternion q2 = -q1;

			Vector3 v1{ 4.34f, 12.7f, -3.2f };
			Vector3 v2 = q1 * v1;
			Vector3 v3 = q2 * v2;

			Assert::AreEqual(v1, v3);
		}

		TEST_METHOD(Inversed_2)
		{
			Quaternion q1 = Quaternion::CreateFromEuler(3, -1.5, 2.1);
			Quaternion q2 = -q1;

			Assert::AreEqual(Quaternion::GetIdentity(), q1 * q2);
		}

		TEST_METHOD(CreateFromEuler_1)
		{
			Vector3 v1{ 0.2f, -2.5f, 3.1f };

			Quaternion q1 = Quaternion::CreateFromEuler(v1);

			Quaternion rotX = Quaternion::CreateRotationX(v1.X);
			Quaternion rotY = Quaternion::CreateRotationY(v1.Y);
			Quaternion rotZ = Quaternion::CreateRotationZ(v1.Z);

			Quaternion q2 = rotY * rotX * rotZ;

			Assert::AreEqual(q2, q1);
		}

		TEST_METHOD(CreateFromEuler_2)
		{
			Vector3 v1{ -0.6f, 0.2f, -2.1f };

			Quaternion q1 = Quaternion::CreateFromEuler(v1);

			Quaternion rotX = Quaternion::CreateRotationX(v1.X);
			Quaternion rotY = Quaternion::CreateRotationY(v1.Y);
			Quaternion rotZ = Quaternion::CreateRotationZ(v1.Z);

			Quaternion q2 = rotY * rotX * rotZ;

			Assert::AreEqual(q2, q1);
		}

		TEST_METHOD(CreateFromEuler_3)
		{
			Vector3 v1{ 0.2f, -2.5f, 3.1f };

			Quaternion q1 = Quaternion::CreateFromEuler(v1);

			Matrix4 rotX = Matrix4::CreateRotationX(v1.X);
			Matrix4 rotY = Matrix4::CreateRotationY(v1.Y);
			Matrix4 rotZ = Matrix4::CreateRotationZ(v1.Z);

			Matrix4 m1 = Matrix4::CreateRotation(q1);
			Matrix4 m2 = rotY * rotX * rotZ;

			Assert::AreEqual(m1, m2);
		}

		TEST_METHOD(CreateFromAxisAngle_1)
		{
			Vector3 axis{ 1.0f, 1.0f, 0.0f };
			Real angle = Utils::PI<Real> / 2.0f;

			Quaternion q1 = Quaternion::CreateFromAxisAngle(axis, angle);

			Vector3 point{ 1, 0, 0 };

			Assert::AreEqual(Vector3{ 0.5f, 0.5f, -std::sqrt(2.0f) / 2.0f }, q1 * point);
		}

		TEST_METHOD(CreateLookAt_1)
		{
			Vector3 source = Vector3{ 1.0f, 2.3f, -2.0f };
			Vector3 target = Vector3{ -2.0f, 1.0f, 5.4f };
			Vector3 up = Vector3::GetUp();

			Quaternion q1 = Quaternion::CreateLookAt(source, target);
			Matrix4 m1 = Matrix4::CreateLookAt(source, target, up);
			
			Vector3 point{ 1.0f, 2.0f, -2.0f };

			Assert::AreEqual(Matrix4::TransformPosition(m1, point), q1 * point);
		}

		TEST_METHOD(GetIdentity_1)
		{
			Quaternion q1 = Quaternion::GetIdentity();
		
			Vector3 point{ 2.5f, 12.3f, -2.12f };

			Assert::AreEqual(point, q1 * point);
		}

		TEST_METHOD(GetIdentity_2)
		{
			Quaternion q1 = Quaternion::GetIdentity();

			Vector3 point{ -5.5f, 0.95f, 3.3f };

			Assert::AreEqual(point, q1 * point);
		}

		TEST_METHOD(GetLength_1)
		{
			Vector3 angles{ 2.6f, -3.1f, 0.26f };
			Real multiplier = 8.3f;
			Quaternion q1 = Quaternion::CreateFromEuler(angles);
			
			Real expected = multiplier * std::sqrt(q1.X * q1.X + q1.Y * q1.Y + q1.Z * q1.Z + q1.W * q1.W);

			q1.X *= multiplier;
			q1.Y *= multiplier;
			q1.Z *= multiplier;
			q1.W *= multiplier;

			Real length = q1.GetLength();

			Assert::AreEqual(expected, length, Utils::Eps<Real>);
		}

		TEST_METHOD(GetLengthSquared_1)
		{
			Vector3 angles{ 2.6f, -3.1f, 0.26f };
			Real multiplier = 8.3f;
			Quaternion q1 = Quaternion::CreateFromEuler(angles);

			Real expected = multiplier * multiplier * (q1.X * q1.X + q1.Y * q1.Y + q1.Z * q1.Z + q1.W * q1.W);

			q1.X *= multiplier;
			q1.Y *= multiplier;
			q1.Z *= multiplier;
			q1.W *= multiplier;

			Real length = q1.GetLengthSquared();

			Assert::AreEqual(expected, length, Utils::Eps<Real>);
		}

		TEST_METHOD(Normalize_1)
		{
			Vector3 angles{ 2.6f, -3.1f, 0.26f };
			Real multiplier = 8.3f;
			Quaternion q1 = Quaternion::CreateFromEuler(angles);
			Quaternion q2 = q1;

			Real expected = multiplier * std::sqrt(q1.X * q1.X + q1.Y * q1.Y + q1.Z * q1.Z + q1.W * q1.W);

			q1.X *= multiplier;
			q1.Y *= multiplier;
			q1.Z *= multiplier;
			q1.W *= multiplier;

			q1.Normalize();

			Assert::AreEqual(q2, q1);
		}

		TEST_METHOD(GetNormalized_1)
		{
			Vector3 angles{ 2.6f, -3.1f, 0.26f };
			Real multiplier = 8.3f;
			Quaternion q1 = Quaternion::CreateFromEuler(angles);
			Quaternion q2 = q1;

			Real expected = multiplier * std::sqrt(q1.X * q1.X + q1.Y * q1.Y + q1.Z * q1.Z + q1.W * q1.W);

			q1.X *= multiplier;
			q1.Y *= multiplier;
			q1.Z *= multiplier;
			q1.W *= multiplier;

			Assert::AreEqual(q2, q2.GetNormalized());
		}

		TEST_METHOD(CreateRotationX)
		{
			Real angle = 2.5f;
			Quaternion q1 = Quaternion::CreateRotationX(angle);
			Matrix4 m1 = Matrix4::CreateRotationX(angle);

			Vector3 point{ -5.5f, 0.95f, 3.3f };

			Assert::AreEqual(Matrix4::TransformPosition(m1, point), q1 * point);
		}

		TEST_METHOD(CreateRotationY)
		{
			Real angle = 2.5f;
			Quaternion q1 = Quaternion::CreateRotationY(angle);
			Matrix4 m1 = Matrix4::CreateRotationY(angle);

			Vector3 point{ -5.5f, 0.95f, 3.3f };

			Assert::AreEqual(Matrix4::TransformPosition(m1, point), q1 * point);
		}

		TEST_METHOD(CreateRotationZ)
		{
			Real angle = 2.5f;
			Quaternion q1 = Quaternion::CreateRotationZ(angle);
			Matrix4 m1 = Matrix4::CreateRotationZ(angle);

			Vector3 point{ -5.5f, 0.95f, 3.3f };

			Assert::AreEqual(Matrix4::TransformPosition(m1, point), q1 * point);
		}
	};
}