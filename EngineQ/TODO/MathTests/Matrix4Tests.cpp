#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "Helpers.hpp"

namespace MathTests
{
	TEST_CLASS(Matrix4Tests)
	{
	public:
		TEST_METHOD(Equal_1)
		{
			Matrix4 m1{ 2, 5, 3, 7, 0.3f, 2.5f, -2, -12.0f, 9, 6, 0.55f, -0.1f, 3.6f, 12.76f, -1.123f, 0.0002f };
			Matrix4 m2{ 2, 5, 3, 7, 0.3f, 2.5f, -2, -12.0f, 9, 6, 0.55f, -0.1f, 3.6f, 12.76f, -1.123f, 0.0002f };

			Assert::AreEqual(m1, m2);
		}
		
		TEST_METHOD(Equal_2)
		{
			Matrix4 m1{ 2, 5, 3, 7, 0.3f, 2.5f, -2, -12.0f, 9, 6, 0.55f, -0.1f, 3.6f, 12.76f, -1.123f, 0.0002f };
			Matrix4 m2{ 2, 5, 3 + Utils::Eps<Real> / 2.0f, 7, 0.3f, 2.5f + Utils::Eps<Real> / 2.0f, -2, -12.0f, 9 + Utils::Eps<Real> / 2.0f, 6 - Utils::Eps<Real> / 2.0f, 0.55f - Utils::Eps<Real> / 2.0f, -0.1f, 3.6f, 12.76f, -1.123f, 0.0002f };

			Assert::AreEqual(m1, m2);
		}

		TEST_METHOD(NotEqual_1)
		{
			Matrix4 m1{ 2, 5, 3, 7, 0.3f, 2.5f, -2, -12.0f, 9, 6, 0.55f, -0.1f, 3.6f, 12.76f, -1.123f, 0.0002f };
			Matrix4 m2{ 0.5f, 6, 7, -74, 2, 8, 0.35f, 1, -4, -3.36f, 1.0f, 0.003f, -3.5f, 35, 1.6f, 76 };
			
			Assert::AreNotEqual(m1, m2);
		}

		TEST_METHOD(NotEqual_2)
		{
			Matrix4 m1{ 2, 5, 3, 7, 0.3f, 2.5f, -2, -12.0f, 9, 6, 0.55f, -0.1f, 3.6f, 12.76f, -1.123f, 0.0002f };
			Matrix4 m2{ 2, 5, 3 + Utils::Eps<Real> / 2.0f, 7, 0.3f, 2.5f + Utils::Eps<Real> / 2.0f, -2, -12.0f, 9 + Utils::Eps<Real> / 2.0f, 6 - Utils::Eps<Real> / 2.0f, 0.55f - Utils::Eps<Real> / 2.0f, -0.1f, 3.6f, 12.76f, -1.123f, 0.0002f + 2.0f * Utils::Eps<Real> };

			Assert::AreNotEqual(m1, m2);
		}

		TEST_METHOD(CreateFromColumns_1)
		{
			Vector4 v1{ 1, 2, 3, 4 };
			Vector4 v2{ 6, 3, 2, 6 };
			Vector4 v3{ -4, -7, 2, 0 };
			Vector4 v4{ 2, 6, -3, 0.556f };

			Matrix4 m1 = Matrix4::CreateFromColumns(v1, v2, v3, v4);
			Matrix4 m2{ v1.X, v2.X, v3.X, v4.X, v1.Y, v2.Y, v3.Y, v4.Y, v1.Z, v2.Z, v3.Z, v4.Z, v1.W, v2.W, v3.W, v4.W };

			Assert::AreEqual(m2, m1);
		}

		TEST_METHOD(CreateFromRows_1)
		{
			Vector4 v1{ 1, 2, 3, 4 };
			Vector4 v2{ 6, 3, 2, 6 };
			Vector4 v3{ -4, -7, 2, 0 };
			Vector4 v4{ 2, 6, -3, 0.556f };

			Matrix4 m1 = Matrix4::CreateFromRows(v1, v2, v3, v4);
			Matrix4 m2{ v1.X, v1.Y, v1.Z, v1.W, v2.X, v2.Y, v2.Z, v2.W, v3.X, v3.Y, v3.Z, v3.W, v4.X, v4.Y, v4.Z, v4.W };

			Assert::AreEqual(m2, m1);
		}

		TEST_METHOD(CreateScale_1)
		{
			Vector3 scale{ 2.0f, -1.5f, 2.5f };
			Matrix4 m1 = Matrix4::CreateScale(scale);

			Vector3 point{ 1.4f, 6.2f, -2.5f };

			Assert::AreEqual(point * scale, Matrix4::TransformPosition(m1, point));
		}

		TEST_METHOD(CreateScale_2)
		{
			Vector3 scale{ -0.4f, 0.0f, 20.0f };
			Matrix4 m1 = Matrix4::CreateScale(scale);

			Vector3 point{ 0.95f, -1.6f, 5.5f };

			Assert::AreEqual(point * scale, Matrix4::TransformPosition(m1, point));
		}

		TEST_METHOD(CreateTranslation_1)
		{
			Vector3 translation{ 2.0f, -1.5f, 2.5f };
			Matrix4 m1 = Matrix4::CreateTranslation(translation);

			Vector3 point{ 1.4f, 6.2f, -2.5f };

			Assert::AreEqual(point + translation, Matrix4::TransformPosition(m1, point));
		}

		TEST_METHOD(CreateTranslation_2)
		{
			Vector3 translation{ -0.4f, 0.0f, 20.0f };
			Matrix4 m1 = Matrix4::CreateTranslation(translation);

			Vector3 point{ 0.95f, -1.6f, 5.5f };

			Assert::AreEqual(point + translation, Matrix4::TransformPosition(m1, point));
		}

		TEST_METHOD(GetColumns_1)
		{
			Vector4 v1{ 1, 2, 3, 4 };
			Vector4 v2{ 6, 3, 2, 6 };
			Vector4 v3{ -4, -7, 2, 0 };
			Vector4 v4{ 2, 6, -3, 0.556f };

			Matrix4 m1 = Matrix4::CreateFromColumns(v1, v2, v3, v4);

			Vector4 r1, r2, r3, r4;
			m1.GetColumns(r1, r2, r3, r4);

			Assert::AreEqual(v1, r1);
			Assert::AreEqual(v2, r2);
			Assert::AreEqual(v3, r3);
			Assert::AreEqual(v4, r4);
		}

		TEST_METHOD(GetColumn_1)
		{
			Vector4 v1{ 1, 2, 3, 4 };
			Vector4 v2{ 6, 3, 2, 6 };
			Vector4 v3{ -4, -7, 2, 0 };
			Vector4 v4{ 2, 6, -3, 0.556f };

			Matrix4 m1 = Matrix4::CreateFromColumns(v1, v2, v3, v4);
		
			Vector4 col = m1.GetColumn(0);

			Assert::AreEqual(v1, col);
		}

		TEST_METHOD(GetColumn_2)
		{
			Vector4 v1{ 1, 2, 3, 4 };
			Vector4 v2{ 6, 3, 2, 6 };
			Vector4 v3{ -4, -7, 2, 0 };
			Vector4 v4{ 2, 6, -3, 0.556f };

			Matrix4 m1 = Matrix4::CreateFromColumns(v1, v2, v3, v4);

			Vector4 col = m1.GetColumn(1);

			Assert::AreEqual(v2, col);
		}

		TEST_METHOD(GetColumn_3)
		{
			Vector4 v1{ 1, 2, 3, 4 };
			Vector4 v2{ 6, 3, 2, 6 };
			Vector4 v3{ -4, -7, 2, 0 };
			Vector4 v4{ 2, 6, -3, 0.556f };

			Matrix4 m1 = Matrix4::CreateFromColumns(v1, v2, v3, v4);

			Vector4 col = m1.GetColumn(2);

			Assert::AreEqual(v3, col);
		}

		TEST_METHOD(GetColumn_4)
		{
			Vector4 v1{ 1, 2, 3, 4 };
			Vector4 v2{ 6, 3, 2, 6 };
			Vector4 v3{ -4, -7, 2, 0 };
			Vector4 v4{ 2, 6, -3, 0.556f };

			Matrix4 m1 = Matrix4::CreateFromColumns(v1, v2, v3, v4);

			Vector4 col = m1.GetColumn(3);

			Assert::AreEqual(v4, col);
		}

		TEST_METHOD(SetColumn_1)
		{
			Vector4 v1{ 1, 2, 3, 4 };
			Vector4 v2{ 6, 3, 2, 6 };
			Vector4 v3{ -4, -7, 2, 0 };
			Vector4 v4{ 2, 6, -3, 0.556f };
			Vector4 v5{ -1, -2, -3, -4 };

			Matrix4 m1 = Matrix4::CreateFromColumns(v1, v2, v3, v4);
			m1.SetColumn(0, v5);

			Vector4 col = m1.GetColumn(0);

			Assert::AreEqual(v5, col);
		}


		TEST_METHOD(SetColumn_2)
		{
			Vector4 v1{ 1, 2, 3, 4 };
			Vector4 v2{ 6, 3, 2, 6 };
			Vector4 v3{ -4, -7, 2, 0 };
			Vector4 v4{ 2, 6, -3, 0.556f };
			Vector4 v5{ -1, -2, -3, -4 };

			Matrix4 m1 = Matrix4::CreateFromColumns(v1, v2, v3, v4);
			m1.SetColumn(1, v5);

			Vector4 col = m1.GetColumn(1);

			Assert::AreEqual(v5, col);
		}


		TEST_METHOD(SetColumn_3)
		{
			Vector4 v1{ 1, 2, 3, 4 };
			Vector4 v2{ 6, 3, 2, 6 };
			Vector4 v3{ -4, -7, 2, 0 };
			Vector4 v4{ 2, 6, -3, 0.556f };
			Vector4 v5{ -1, -2, -3, -4 };

			Matrix4 m1 = Matrix4::CreateFromColumns(v1, v2, v3, v4);
			m1.SetColumn(2, v5);

			Vector4 col = m1.GetColumn(2);

			Assert::AreEqual(v5, col);
		}


		TEST_METHOD(SetColumn_4)
		{
			Vector4 v1{ 1, 2, 3, 4 };
			Vector4 v2{ 6, 3, 2, 6 };
			Vector4 v3{ -4, -7, 2, 0 };
			Vector4 v4{ 2, 6, -3, 0.556f };
			Vector4 v5{ -1, -2, -3, -4 };

			Matrix4 m1 = Matrix4::CreateFromColumns(v1, v2, v3, v4);
			m1.SetColumn(3, v5);

			Vector4 col = m1.GetColumn(3);

			Assert::AreEqual(v5, col);
		}

		TEST_METHOD(GetRows_1)
		{
			Vector4 v1{ 1, 2, 3, 4 };
			Vector4 v2{ 6, 3, 2, 6 };
			Vector4 v3{ -4, -7, 2, 0 };
			Vector4 v4{ 2, 6, -3, 0.556f };

			Matrix4 m1 = Matrix4::CreateFromRows(v1, v2, v3, v4);

			Vector4 r1, r2, r3, r4;
			m1.GetRows(r1, r2, r3, r4);

			Assert::AreEqual(v1, r1);
			Assert::AreEqual(v2, r2);
			Assert::AreEqual(v3, r3);
			Assert::AreEqual(v4, r4);
		}

		TEST_METHOD(GetRow_1)
		{
			Vector4 v1{ 1, 2, 3, 4 };
			Vector4 v2{ 6, 3, 2, 6 };
			Vector4 v3{ -4, -7, 2, 0 };
			Vector4 v4{ 2, 6, -3, 0.556f };

			Matrix4 m1 = Matrix4::CreateFromRows(v1, v2, v3, v4);

			Vector4 row = m1.GetRow(0);

			Assert::AreEqual(v1, row);
		}

		TEST_METHOD(GetRow_2)
		{
			Vector4 v1{ 1, 2, 3, 4 };
			Vector4 v2{ 6, 3, 2, 6 };
			Vector4 v3{ -4, -7, 2, 0 };
			Vector4 v4{ 2, 6, -3, 0.556f };

			Matrix4 m1 = Matrix4::CreateFromRows(v1, v2, v3, v4);

			Vector4 row = m1.GetRow(1);

			Assert::AreEqual(v2, row);
		}

		TEST_METHOD(GetRow_3)
		{
			Vector4 v1{ 1, 2, 3, 4 };
			Vector4 v2{ 6, 3, 2, 6 };
			Vector4 v3{ -4, -7, 2, 0 };
			Vector4 v4{ 2, 6, -3, 0.556f };

			Matrix4 m1 = Matrix4::CreateFromRows(v1, v2, v3, v4);

			Vector4 row = m1.GetRow(2);

			Assert::AreEqual(v3, row);
		}

		TEST_METHOD(GetRow_4)
		{
			Vector4 v1{ 1, 2, 3, 4 };
			Vector4 v2{ 6, 3, 2, 6 };
			Vector4 v3{ -4, -7, 2, 0 };
			Vector4 v4{ 2, 6, -3, 0.556f };

			Matrix4 m1 = Matrix4::CreateFromRows(v1, v2, v3, v4);

			Vector4 row = m1.GetRow(3);

			Assert::AreEqual(v4, row);
		}

		TEST_METHOD(SetRow_1)
		{
			Vector4 v1{ 1, 2, 3, 4 };
			Vector4 v2{ 6, 3, 2, 6 };
			Vector4 v3{ -4, -7, 2, 0 };
			Vector4 v4{ 2, 6, -3, 0.556f };
			Vector4 v5{ -1, -2, -3, -4 };

			Matrix4 m1 = Matrix4::CreateFromRows(v1, v2, v3, v4);
			m1.SetRow(0, v5);

			Vector4 row = m1.GetRow(0);

			Assert::AreEqual(v5, row);
		}

		TEST_METHOD(SetRow_2)
		{
			Vector4 v1{ 1, 2, 3, 4 };
			Vector4 v2{ 6, 3, 2, 6 };
			Vector4 v3{ -4, -7, 2, 0 };
			Vector4 v4{ 2, 6, -3, 0.556f };
			Vector4 v5{ -1, -2, -3, -4 };

			Matrix4 m1 = Matrix4::CreateFromRows(v1, v2, v3, v4);
			m1.SetRow(1, v5);

			Vector4 row = m1.GetRow(1);

			Assert::AreEqual(v5, row);
		}

		TEST_METHOD(SetRow_3)
		{
			Vector4 v1{ 1, 2, 3, 4 };
			Vector4 v2{ 6, 3, 2, 6 };
			Vector4 v3{ -4, -7, 2, 0 };
			Vector4 v4{ 2, 6, -3, 0.556f };
			Vector4 v5{ -1, -2, -3, -4 };

			Matrix4 m1 = Matrix4::CreateFromRows(v1, v2, v3, v4);
			m1.SetRow(2, v5);

			Vector4 row = m1.GetRow(2);

			Assert::AreEqual(v5, row);
		}

		TEST_METHOD(SetRow_4)
		{
			Vector4 v1{ 1, 2, 3, 4 };
			Vector4 v2{ 6, 3, 2, 6 };
			Vector4 v3{ -4, -7, 2, 0 };
			Vector4 v4{ 2, 6, -3, 0.556f };
			Vector4 v5{ -1, -2, -3, -4 };

			Matrix4 m1 = Matrix4::CreateFromRows(v1, v2, v3, v4);
			m1.SetRow(3, v5);

			Vector4 row = m1.GetRow(3);

			Assert::AreEqual(v5, row);
		}

		TEST_METHOD(Transpose_1)
		{
			Vector4 v1{ 1, 2, 3, 4 };
			Vector4 v2{ 6, 3, 2, 6 };
			Vector4 v3{ -4, -7, 2, 0 };
			Vector4 v4{ 2, 6, -3, 0.556f };

			Matrix4 m1 = Matrix4::CreateFromRows(v1, v2, v3, v4);
			Matrix4 m2 = Matrix4::CreateFromColumns(v1, v2, v3, v4);

			m2.Transpose();

			Assert::AreEqual(m1, m2);
		}

		TEST_METHOD(Transpose_2)
		{
			Vector4 v1{ 1, 2, 3, 4 };
			Vector4 v2{ 6, 3, 2, 6 };
			Vector4 v3{ -4, -7, 2, 0 };
			Vector4 v4{ 2, 6, -3, 0.556f };

			Matrix4 m1 = Matrix4::CreateFromRows(v1, v2, v3, v4);
			Matrix4 m2 = m1;

			m2.Transpose();
			m2.Transpose();

			Assert::AreEqual(m1, m2);
		}

		TEST_METHOD(GetTransposed_1)
		{
			Vector4 v1{ 1, 2, 3, 4 };
			Vector4 v2{ 6, 3, 2, 6 };
			Vector4 v3{ -4, -7, 2, 0 };
			Vector4 v4{ 2, 6, -3, 0.556f };

			Matrix4 m1 = Matrix4::CreateFromRows(v1, v2, v3, v4);
			Matrix4 m2 = Matrix4::CreateFromColumns(v1, v2, v3, v4);

			Assert::AreEqual(m1, m2.GetTransposed());
		}

		TEST_METHOD(GetTransposed_2)
		{
			Vector4 v1{ 1, 2, 3, 4 };
			Vector4 v2{ 6, 3, 2, 6 };
			Vector4 v3{ -4, -7, 2, 0 };
			Vector4 v4{ 2, 6, -3, 0.556f };

			Matrix4 m1 = Matrix4::CreateFromRows(v1, v2, v3, v4);
			Matrix4 m2 = m1;

			Assert::AreEqual(m1, m2.GetTransposed().GetTransposed());
		}

		TEST_METHOD(GetIdentity_1)
		{
			Matrix4 m1 = Matrix4::GetIdentity();
			Matrix4 m2{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };

			Assert::AreEqual(m2, m1);
		}

		TEST_METHOD(GetInversed_1)
		{
			Vector3 translation{ -6, -0.2f, 0.0f };
			Vector3 scale{ 2.5f, -1.3f, 1.6f };
			Quaternion rotation = Quaternion::CreateFromEuler(3, 0.2f, -1.4f);

			Matrix4 m1 = Matrix4::CreateTranslation(translation) * Matrix4::CreateScale(scale) * Matrix4::CreateRotation(rotation);
			Matrix4 m2 = m1.GetInversed();

			Assert::AreEqual(Matrix4::GetIdentity(), m1 * m2);
		}

		TEST_METHOD(Inverse_1)
		{
			Vector3 translation{ -6, -0.2f, 0.0f };
			Vector3 scale{ 2.5f, -1.3f, 1.6f };
			Quaternion rotation = Quaternion::CreateFromEuler(3, 0.2f, -1.4f);

			Matrix4 m1 = Matrix4::CreateTranslation(translation) * Matrix4::CreateScale(scale) * Matrix4::CreateRotation(rotation);
			Matrix4 m2 = m1;

			m2.Inverse();

			Assert::AreEqual(Matrix4::GetIdentity(), m1 * m2);
		}

		TEST_METHOD(SetDiagonal_1)
		{
			Matrix4 m1;

			m1.SetDiagonal(Vector4::GetOne());

			Assert::AreEqual(Matrix4::GetIdentity(), m1);
		}

		TEST_METHOD(GetDiagonal_1)
		{
			Vector4 v1{ 1, 2, 3, 4 };
			Vector4 v2{ 6, 3, 2, 6 };
			Vector4 v3{ -4, -7, 2, 0 };
			Vector4 v4{ 2, 6, -3, 0.556f };

			Matrix4 m1 = Matrix4::CreateFromRows(v1, v2, v3, v4);

			Assert::AreEqual(Vector4{ v1.X, v2.Y, v3.Z, v4.W }, m1.GetDiagonal());
		}

		TEST_METHOD(TransformPosition_1)
		{
			Vector3 translation{ -6, -0.2f, 0.0f };
			Vector3 scale{ 2.5f, -1.3f, 1.6f };
			Quaternion rotation = Quaternion::CreateFromEuler(3, 0.2f, -1.4f);

			Matrix4 m1 = Matrix4::CreateTranslation(translation) * Matrix4::CreateRotation(rotation) * Matrix4::CreateScale(scale);

			Vector3 v{ 4.3f, -2.0f, -1.5f };

			Assert::AreEqual(translation + (rotation * (scale * v)), Matrix4::TransformPosition(m1, v));
		}

		TEST_METHOD(TransformVector_1)
		{
			Vector3 translation{ -6, -0.2f, 0.0f };
			Vector3 scale{ 2.5f, -1.3f, 1.6f };
			Quaternion rotation = Quaternion::CreateFromEuler(3, 0.2f, -1.4f);

			Matrix4 m1 = Matrix4::CreateTranslation(translation) * Matrix4::CreateRotation(rotation) * Matrix4::CreateScale(scale);

			Vector3 v{ 4.3f, -2.0f, -1.5f };

			Assert::AreEqual(rotation * (scale * v), Matrix4::TransformVector(m1, v));
		}

		TEST_METHOD(TransformNormal_1)
		{
			Vector3 translation{ -6, -0.2f, 0.0f };
			Vector3 scale{ 2.5f, -1.3f, 1.6f };
			Quaternion rotation = Quaternion::CreateFromEuler(3, 0.2f, -1.4f);


			Matrix4 m1 = Matrix4::CreateTranslation(translation) * Matrix4::CreateRotation(rotation) * Matrix4::CreateScale(scale);
			Matrix4 m2 = m1.GetInversed().GetTransposed();

			Vector4 v{ 4.3f, -2.0f, -1.5f, 0.0f };

			Assert::AreEqual(static_cast<Vector3>(m2 * v), Matrix4::TransformNormal(m1, static_cast<Vector3>(v)));
		}

		TEST_METHOD(TransformPerspective_1)
		{
			Vector3 translation{ -6, -0.2f, 2.0f };
			Vector3 scale{ 2.5f, -1.3f, 1.6f };
			Quaternion rotation = Quaternion::CreateFromEuler(3, 0.2f, -1.4f);

			Matrix4 perspective = Matrix4::CreateFrustum(Utils::DegToRad(60.0f), 16.0f / 9.0f, 0.01f, 10.0f);
			Matrix4 m1 = perspective * Matrix4::CreateTranslation(translation) * Matrix4::CreateRotation(rotation) * Matrix4::CreateScale(scale);
			
			Vector3 v{ 4.3f, -2.0f, -1.5f };

			Vector4 v2{ translation + (rotation * (scale * v)), 1.0f };
			v2 = perspective * v2;
			v2 /= v2.W;

			Assert::AreEqual(static_cast<Vector3>(v2), Matrix4::TransformPerspective(m1, v));
		}
	};
}