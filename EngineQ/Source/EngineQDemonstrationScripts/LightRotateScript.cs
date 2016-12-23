using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using EngineQ;
using EngineQ.Math;

namespace QScripts
{
	public class LightRotateScript : Script
	{
		/// <summary>
		/// In radians per second
		/// </summary>
		public float RotationSpeed { get; set; } = 1.0f;
		public float InitialRotation { get; set; } = 0.0f;

		private Vector3 rotationAxis = Vector3.Up;
		public Vector3 RotationAxis
		{
			get
			{
				return this.rotationAxis;
			}

			set
			{
				var length = value.Length;

				if (length == 0.0f)
					this.rotationAxis = Vector3.Up;
				else
					this.rotationAxis = value / length;
			}
		}

		public float Radius { get; set; } = 5.0f;
		public Vector3 RotationPoint { get; set; } = Vector3.Zero;


		private float currentRotation = 0.0f;

		protected override void OnEnable()
		{
			currentRotation = InitialRotation;
		}

		protected override void OnUpdate()
		{
			currentRotation += RotationSpeed * Time.DeltaTime;

			while (currentRotation >= Utils.PI)
				currentRotation -= Utils.PI * 2.0f;
			while (currentRotation < -Utils.PI)
				currentRotation += Utils.PI * 2.0f;

			Quaternion rotation = Quaternion.CreateFromAxisAngle(rotationAxis, currentRotation);


			var rotatedPoint = Vector3.CrossProduct(rotationAxis, Vector3.Right);
			if (Math.Abs(rotatedPoint.LengthSquared) < 0.001f)
				rotatedPoint = Vector3.CrossProduct(rotationAxis, Vector3.Forward);

			rotatedPoint = rotatedPoint.Normalized * Radius;

		//	var lookAtMatrix = Matrix4.CreateLookAt(Transform.Position, Vector3.Zero, Vector3.Up);
			var lookAtQuaternion = Quaternion.CreateLookAt(Transform.Position, Vector3.Zero, Vector3.Up);
		//	Vector3 point = Vector3.Forward;
		//	Console.WriteLine("Mat: " + Matrix4.TransformVector(lookAtMatrix, point));
		//	Console.WriteLine("Qat: " + lookAtQuaternion * point);

			Transform.Position = RotationPoint + rotation * rotatedPoint;
		//	Transform.Rotation = CalculateRotation(lookAtMatrix);
			Transform.Rotation = lookAtQuaternion;
		}

		private Quaternion CalculateRotation(Matrix4 matrix)
		{
			Quaternion q;

			float trace = matrix[0,0] + matrix[1,1] + matrix[2,2];
			if (trace > 0)
			{
				float s = 0.5f / (float)Math.Sqrt(trace + 1.0f);
				q.W = 0.25f / s;
				q.X = (matrix[2,1] - matrix[1,2]) * s;
				q.Y = (matrix[0,2] - matrix[2,0]) * s;
				q.Z = (matrix[1,0] - matrix[0,1]) * s;
			}
			else
			{
				if (matrix[0,0] > matrix[1,1] && matrix[0,0] > matrix[2,2])
				{
					float s = 2.0f * (float)Math.Sqrt(1.0f + matrix[0,0] - matrix[1,1] - matrix[2,2]);
					q.W = (matrix[2,1] - matrix[1,2]) / s;
					q.X = 0.25f * s;
					q.Y = (matrix[0,1] + matrix[1,0]) / s;
					q.Z = (matrix[0,2] + matrix[2,0]) / s;
				}
				else if (matrix[1,1] > matrix[2,2])
				{
					float s = 2.0f * (float)Math.Sqrt(1.0f + matrix[1,1] - matrix[0,0] - matrix[2,2]);
					q.W = (matrix[0,2] - matrix[2,0]) / s;
					q.X = (matrix[0,1] + matrix[1,0]) / s;
					q.Y = 0.25f * s;
					q.Z = (matrix[1,2] + matrix[2,1]) / s;
				}
				else
				{
					float s = 2.0f * (float)Math.Sqrt(1.0f + matrix[2,2] - matrix[0,0] - matrix[1,1]);
					q.W = (matrix[1,0] - matrix[0,1]) / s;
					q.X = (matrix[0,2] + matrix[2,0]) / s;
					q.Y = (matrix[1,2] + matrix[2,1]) / s;
					q.Z = 0.25f * s;
				}
			}

			return q;
		}
	}
}
