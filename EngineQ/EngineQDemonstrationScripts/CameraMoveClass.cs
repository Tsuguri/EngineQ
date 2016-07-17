using System;

using EngineQ;
using EngineQ.Math;


namespace QScripts
{
	public class CameraMoveClass : Script
	{ 
		private Vector3 tmp;
		private Vector2 tmp2;
		private float rotationX;
		private float rotationY;
		private float speed=5;
		private bool reverseY=true;
		private bool reverseX = true;
		private static float pi = (float)Math.PI;

		public CameraMoveClass()
		{
			Input.ListenKey(Input.Key.Escape, EscapeAction);
			Input.ListenKey(Input.Key.F1, F1Action);
			Input.ListenKey(Input.Key.F2, F2Action);
			rotationX = transform.Rotation.EulerAngles.X;
			rotationY = transform.Rotation.EulerAngles.Y;
		}

		private float DegToRad(float val)
		{
			return (float)(Math.PI*val/180);
		}

		private void CheckAngles()
		{
			if (rotationX > pi/2)
				rotationX = pi/2;
			if (rotationX < -pi/2)
				rotationX = -pi/2;
			if (rotationY > pi * 2)
				rotationY -= pi * 2;
			if (rotationY < 0)
				rotationY += pi * 2;
		}
		protected override void Update()
		{
			base.Update();
			tmp = Vector3.Zero;
			if (Input.KeyPressed(Input.Key.A))
				tmp += Vector3.Left;
			if (Input.KeyPressed(Input.Key.D))
				tmp += Vector3.Right;
			if (Input.KeyPressed(Input.Key.S))
				tmp += Vector3.Back;
			if (Input.KeyPressed(Input.Key.W))
				tmp += Vector3.Forward;
			if (Input.KeyPressed(Input.Key.Space))
				tmp += Vector3.Up;
			if (Input.KeyPressed(Input.Key.LeftShift))
				tmp += Vector3.Down;
			if (tmp.LengthSquared > 0)
				MoveInDirection(tmp.Normalized);
			if (Input.MouseButtonDown(1) && (tmp2=Input.MouseDeltaPosition).LengthSquared > 0)
			{
				rotationX += DegToRad(tmp2.Y*(reverseX?1:-1))/speed;
				rotationY += DegToRad(tmp2.X * (reverseY ? 1 : -1)) /speed;

				CheckAngles();
				Console.WriteLine($"Angles: {rotationX} {rotationY}");
				transform.Rotation =Quaternion.CreateFromEuler(rotationX,rotationY,0);
			}
	}

		private void MoveInDirection(Vector3 direction)
		{
			transform.Position = transform.Position + transform.Rotation * direction * Time.DeltaTime;
		}

		private void EscapeAction(Input.KeyAction action)
		{
			if(action== Input.KeyAction.Press)
				Application.Exit();
		}

		private void F1Action(Input.KeyAction action)
		{
			if (action == Input.KeyAction.Press)
				reverseX = !reverseX;
		}

		private void F2Action(Input.KeyAction action)
		{
			if (action == Input.KeyAction.Press)
				reverseY = !reverseY;
		}
	}
}
