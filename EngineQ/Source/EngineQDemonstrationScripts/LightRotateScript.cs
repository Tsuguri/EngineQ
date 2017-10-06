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

		protected override void OnActivate()
		{
			this.currentRotation = InitialRotation;
		}
		
		public void Update()
		{
			Update(0.0f);
		}

		private void Update(float dt)
		{
			currentRotation += RotationSpeed * dt;

			while (currentRotation >= Utils.PI)
				currentRotation -= Utils.PI * 2.0f;
			while (currentRotation < -Utils.PI)
				currentRotation += Utils.PI * 2.0f;

			Quaternion rotation = Quaternion.CreateFromAxisAngle(rotationAxis, currentRotation);


			var rotatedPoint = Vector3.CrossProduct(rotationAxis, Vector3.Right);
			if (Math.Abs(rotatedPoint.LengthSquared) < 0.001f)
				rotatedPoint = Vector3.CrossProduct(rotationAxis, Vector3.Forward);

			rotatedPoint = rotatedPoint.Normalized * Radius;

			var lookAtQuaternion = Quaternion.CreateLookAt(Transform.Position, Vector3.Zero, Vector3.Up);
			
			Transform.Position = RotationPoint + rotation * rotatedPoint;
			Transform.Rotation = lookAtQuaternion;
		}

		protected override void OnUpdate()
		{
			this.Update(Time.DeltaTime);
		}
	}
}
