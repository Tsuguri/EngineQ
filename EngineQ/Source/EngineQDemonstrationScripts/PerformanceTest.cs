using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using EngineQ;
using EngineQ.Math;
using System.Diagnostics;
using System.Runtime.CompilerServices;

namespace QScripts
{
	public class PerformanceTest : Script
	{
		private const int DefaultIterations = 5000000 * 10;
		private int iterations = DefaultIterations;
		private Stopwatch sw = new Stopwatch();
	
		private void QuaternionMultiplyTest()
		{
			Setup("Quaternion Multiplication");

			Quaternion q1 = Quaternion.CreateFromEuler(0.2f, 2.4f, -3.1f);
			Quaternion q2 = Quaternion.CreateFromEuler(1.2f, -0.6f, -1.1f);

			sw.Reset();
			sw.Start();
			for (int i = 0; i < iterations; ++i)
			{
				Quaternion q = q1 * q2;
			}
			sw.Stop();
			PrintResults("Internal Call (C++)");


			sw.Reset();
			sw.Start();
			for (int i = 0; i < iterations; ++i)
			{
				Quaternion q = Quaternion_Multiply(q1, q2);
			}
			sw.Stop();
			PrintResults("Managed Code (C#)");
		}

		private void Matrix4InverseTest()
		{
			Setup("Matrix4 Inverse");

			Matrix4 matrix = Matrix4.CreateTranslation(new Vector3(-10.4f, 23.2f, 0.12f)) * Matrix4.CreateRotation(Quaternion.CreateFromEuler(1.2f, 0.1f, -2.0f)) * Matrix4.CreateScale(new Vector3(1.2f, -4.0f, 2.3f));

			sw.Reset();
			sw.Start();
			for (int i = 0; i < iterations; ++i)
			{
				Matrix4 mat = matrix.Inverse;
			}
			sw.Stop();
			PrintResults("Internal Call (C++)");


			sw.Reset();
			sw.Start();
			for (int i = 0; i < iterations; ++i)
			{
				Matrix4 mat = Matrix4_GetInversed(matrix);
			}
			sw.Stop();
			PrintResults("Managed Code (C#)");
		}

		private void Matrix4MultiplicationTest()
		{
			Setup("Matrix Multiplication");

			Matrix4 m1 = Matrix4.CreateTranslation(new Vector3(-10.4f, 23.2f, 0.12f));
			Matrix4 m2 = Matrix4.CreateRotation(Quaternion.CreateFromEuler(1.2f, 0.1f, -2.0f));
			Matrix4 m3 = Matrix4.CreateScale(new Vector3(1.2f, -4.0f, 2.3f));

			sw.Reset();
			sw.Start();
			for (int i = 0; i < iterations; ++i)
			{
				Matrix4 mat1 = m2 * m3;
				Matrix4 mat2 = m1 * mat1;
			}
			sw.Stop();
			PrintResults("Internal Call (C++)");


			sw.Reset();
			sw.Start();
			for (int i = 0; i < iterations; ++i)
			{
				Matrix4 mat1 = Matrix4_Multiply(m2, m3);
				Matrix4 mat2 = Matrix4_Multiply(m1, mat1);
			}
			sw.Stop();
			PrintResults("Managed Code (C#)");
		}

		protected override void OnUpdate()
		{
			QuaternionMultiplyTest();
			Matrix4InverseTest();
			Matrix4MultiplicationTest();
		}

		private void Setup(string intro)
		{
			this.iterations = DefaultIterations;
			Console.WriteLine(intro);
			Console.WriteLine($"\tIterations: {iterations:N0}");
		}

		private void Setup(string intro, int iterations)
		{
			this.iterations = iterations;
			Console.WriteLine(intro);
			Console.WriteLine($"\tIterations: {iterations:N0}");
		}

		private void PrintResults(string caption)
		{
			Console.WriteLine($"\t{caption}");
			Console.WriteLine($"\t\tTime: {sw.ElapsedMilliseconds.ToString().PadLeft(4, ' ')}ms, \tAvg. Time: {(float)sw.ElapsedMilliseconds / (float)iterations}ms");
		}




		private static Quaternion Quaternion_Multiply(Quaternion q1, Quaternion q2)
		{
			return new Quaternion(
				q1.W * q2.W - q1.X * q2.X - q1.Y * q2.Y - q1.Z * q2.Z,
				q1.W * q2.X + q1.X * q2.W + q1.Y * q2.Z - q1.Z * q2.Y,
				q1.W * q2.Y - q1.X * q2.Z + q1.Y * q2.W + q1.Z * q2.X,
				q1.W * q2.Z + q1.X * q2.Y - q1.Y * q2.X + q1.Z * q2.W
			);
		}


		private static Matrix4 Matrix4_Multiply(Matrix4 lhs, Matrix4 rhs)
		{
			return new Matrix4(
				lhs.M00 * rhs.M00 + lhs.M01 * rhs.M10 + lhs.M02 * rhs.M20 + lhs.M03 * rhs.M30,
				lhs.M00 * rhs.M01 + lhs.M01 * rhs.M11 + lhs.M02 * rhs.M21 + lhs.M03 * rhs.M31,
				lhs.M00 * rhs.M02 + lhs.M01 * rhs.M12 + lhs.M02 * rhs.M22 + lhs.M03 * rhs.M32,
				lhs.M00 * rhs.M03 + lhs.M01 * rhs.M13 + lhs.M02 * rhs.M23 + lhs.M03 * rhs.M33,

				lhs.M10 * rhs.M00 + lhs.M11 * rhs.M10 + lhs.M12 * rhs.M20 + lhs.M13 * rhs.M30,
				lhs.M10 * rhs.M01 + lhs.M11 * rhs.M11 + lhs.M12 * rhs.M21 + lhs.M13 * rhs.M31,
				lhs.M10 * rhs.M02 + lhs.M11 * rhs.M12 + lhs.M12 * rhs.M22 + lhs.M13 * rhs.M32,
				lhs.M10 * rhs.M03 + lhs.M11 * rhs.M13 + lhs.M12 * rhs.M23 + lhs.M13 * rhs.M33,

				lhs.M20 * rhs.M00 + lhs.M21 * rhs.M10 + lhs.M22 * rhs.M20 + lhs.M23 * rhs.M30,
				lhs.M20 * rhs.M01 + lhs.M21 * rhs.M11 + lhs.M22 * rhs.M21 + lhs.M23 * rhs.M31,
				lhs.M20 * rhs.M02 + lhs.M21 * rhs.M12 + lhs.M22 * rhs.M22 + lhs.M23 * rhs.M32,
				lhs.M20 * rhs.M03 + lhs.M21 * rhs.M13 + lhs.M22 * rhs.M23 + lhs.M23 * rhs.M33,

				lhs.M30 * rhs.M00 + lhs.M31 * rhs.M10 + lhs.M32 * rhs.M20 + lhs.M33 * rhs.M30,
				lhs.M30 * rhs.M01 + lhs.M31 * rhs.M11 + lhs.M32 * rhs.M21 + lhs.M33 * rhs.M31,
				lhs.M30 * rhs.M02 + lhs.M31 * rhs.M12 + lhs.M32 * rhs.M22 + lhs.M33 * rhs.M32,
				lhs.M30 * rhs.M03 + lhs.M31 * rhs.M13 + lhs.M32 * rhs.M23 + lhs.M33 * rhs.M33
			);
		}

		private static Matrix4 Matrix4_GetInversed(Matrix4 mat)
		{
			float tmp1 =
				mat.M11 * mat.M22 * mat.M33 -
				mat.M11 * mat.M23 * mat.M32 -
				mat.M21 * mat.M12 * mat.M33 +
				mat.M21 * mat.M13 * mat.M32 +
				mat.M31 * mat.M12 * mat.M23 -
				mat.M31 * mat.M13 * mat.M22;

			float tmp2 =
				-mat.M10 * mat.M22 * mat.M33 +
				mat.M10 * mat.M23 * mat.M32 +
				mat.M20 * mat.M12 * mat.M33 -
				mat.M20 * mat.M13 * mat.M32 -
				mat.M30 * mat.M12 * mat.M23 +
				mat.M30 * mat.M13 * mat.M22;

			float tmp3 =
				mat.M10 * mat.M21 * mat.M33 -
				mat.M10 * mat.M23 * mat.M31 -
				mat.M20 * mat.M11 * mat.M33 +
				mat.M20 * mat.M13 * mat.M31 +
				mat.M30 * mat.M11 * mat.M23 -
				mat.M30 * mat.M13 * mat.M21;

			float tmp4 =
				-mat.M10 * mat.M21 * mat.M32 +
				mat.M10 * mat.M22 * mat.M31 +
				mat.M20 * mat.M11 * mat.M32 -
				mat.M20 * mat.M12 * mat.M31 -
				mat.M30 * mat.M11 * mat.M22 +
				mat.M30 * mat.M12 * mat.M21;

			float det = mat.M00 * tmp1 + mat.M01 * tmp2 + mat.M02 * tmp3 + mat.M03 * tmp4;

			if (det == 0.0f)
				return new Matrix4();

			float invdet = 1.0f / det;

			return new Matrix4(
				tmp1 * invdet,

				(-mat.M01 * mat.M22 * mat.M33 +
				mat.M01 * mat.M23 * mat.M32 +
				mat.M21 * mat.M02 * mat.M33 -
				mat.M21 * mat.M03 * mat.M32 -
				mat.M31 * mat.M02 * mat.M23 +
				mat.M31 * mat.M03 * mat.M22) * invdet,

				(mat.M01 * mat.M12 * mat.M33 -
				mat.M01 * mat.M13 * mat.M32 -
				mat.M11 * mat.M02 * mat.M33 +
				mat.M11 * mat.M03 * mat.M32 +
				mat.M31 * mat.M02 * mat.M13 -
				mat.M31 * mat.M03 * mat.M12) * invdet,

				(-mat.M01 * mat.M12 * mat.M23 +
				mat.M01 * mat.M13 * mat.M22 +
				mat.M11 * mat.M02 * mat.M23 -
				mat.M11 * mat.M03 * mat.M22 -
				mat.M21 * mat.M02 * mat.M13 +
				mat.M21 * mat.M03 * mat.M12) * invdet,

				tmp2 * invdet,

				(mat.M00 * mat.M22 * mat.M33 -
				mat.M00 * mat.M23 * mat.M32 -
				mat.M20 * mat.M02 * mat.M33 +
				mat.M20 * mat.M03 * mat.M32 +
				mat.M30 * mat.M02 * mat.M23 -
				mat.M30 * mat.M03 * mat.M22) * invdet,

				(-mat.M00 * mat.M12 * mat.M33 +
				mat.M00 * mat.M13 * mat.M32 +
				mat.M10 * mat.M02 * mat.M33 -
				mat.M10 * mat.M03 * mat.M32 -
				mat.M30 * mat.M02 * mat.M13 +
				mat.M30 * mat.M03 * mat.M12) * invdet,

				(mat.M00 * mat.M12 * mat.M23 -
				mat.M00 * mat.M13 * mat.M22 -
				mat.M10 * mat.M02 * mat.M23 +
				mat.M10 * mat.M03 * mat.M22 +
				mat.M20 * mat.M02 * mat.M13 -
				mat.M20 * mat.M03 * mat.M12) * invdet,

				tmp3 * invdet,

				(-mat.M00 * mat.M21 * mat.M33 +
				mat.M00 * mat.M23 * mat.M31 +
				mat.M20 * mat.M01 * mat.M33 -
				mat.M20 * mat.M03 * mat.M31 -
				mat.M30 * mat.M01 * mat.M23 +
				mat.M30 * mat.M03 * mat.M21) * invdet,

				(mat.M00 * mat.M11 * mat.M33 -
				mat.M00 * mat.M13 * mat.M31 -
				mat.M10 * mat.M01 * mat.M33 +
				mat.M10 * mat.M03 * mat.M31 +
				mat.M30 * mat.M01 * mat.M13 -
				mat.M30 * mat.M03 * mat.M11) * invdet,

				(-mat.M00 * mat.M11 * mat.M23 +
				mat.M00 * mat.M13 * mat.M21 +
				mat.M10 * mat.M01 * mat.M23 -
				mat.M10 * mat.M03 * mat.M21 -
				mat.M20 * mat.M01 * mat.M13 +
				mat.M20 * mat.M03 * mat.M11) * invdet,

				tmp4 * invdet,

				(mat.M00 * mat.M21 * mat.M32 -
				mat.M00 * mat.M22 * mat.M31 -
				mat.M20 * mat.M01 * mat.M32 +
				mat.M20 * mat.M02 * mat.M31 +
				mat.M30 * mat.M01 * mat.M22 -
				mat.M30 * mat.M02 * mat.M21) * invdet,

				(-mat.M00 * mat.M11 * mat.M32 +
				mat.M00 * mat.M12 * mat.M31 +
				mat.M10 * mat.M01 * mat.M32 -
				mat.M10 * mat.M02 * mat.M31 -
				mat.M30 * mat.M01 * mat.M12 +
				mat.M30 * mat.M02 * mat.M11) * invdet,

				(mat.M00 * mat.M11 * mat.M22 -
				mat.M00 * mat.M12 * mat.M21 -
				mat.M10 * mat.M01 * mat.M22 +
				mat.M10 * mat.M02 * mat.M21 +
				mat.M20 * mat.M01 * mat.M12 -
				mat.M20 * mat.M02 * mat.M11) * invdet
			);
		}
	}
}
