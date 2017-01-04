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
		private float rotationSpeed = 5;
		private bool reverseY = true;
		private bool reverseX = true;
		private const float pi = (float)Math.PI;
		private float boost = 1.0f;

		private Entity Skull1;
		private Entity Skull2;

		public float BoostMultiplier { get; set; } = 2.0f;
		public float MoveSpeed { get; set; } = 1.0f;
 
		public CameraMoveClass()
		{
			
		}

		private float DegToRad(float val)
		{
			return (float)(Math.PI * val / 180);
		}

		private float RadToDeg(float val)
		{
			return (float)(val * 180.0 / Math.PI);
		}

		private void CheckAngles()
		{
			if (rotationX > pi / 2)
				rotationX = pi / 2;
			if (rotationX < -pi / 2)
				rotationX = -pi / 2;
			if (rotationY > pi * 2)
				rotationY -= pi * 2;
			if (rotationY < 0)
				rotationY += pi * 2;
		}
		protected override void OnUpdate()
		{
			tmp = Vector3.Zero;
			if (Input.IsKeyPressed(Input.Key.A))
				tmp += Vector3.Left;
			if (Input.IsKeyPressed(Input.Key.D))
				tmp += Vector3.Right;
			if (Input.IsKeyPressed(Input.Key.S))
				tmp += Vector3.Back;
			if (Input.IsKeyPressed(Input.Key.W))
				tmp += Vector3.Forward;
			if (Input.IsKeyPressed(Input.Key.Space))
				tmp += Vector3.Up;
			if (Input.IsKeyPressed(Input.Key.LeftControl))
				tmp += Vector3.Down;
			if (tmp.LengthSquared > 0)
				MoveInDirection(tmp.Normalized);
			if (Input.IsMouseButtonPressed(Input.MouseButton.Right) && (tmp2 = Input.MouseDeltaPosition).LengthSquared > 0)
			{
				rotationX += DegToRad(tmp2.Y * (reverseX ? 1 : -1)) / rotationSpeed;
				rotationY += DegToRad(tmp2.X * (reverseY ? 1 : -1)) / rotationSpeed;

				CheckAngles();
				//	Console.WriteLine($"Angles: {RadToDeg(rotationX)} {RadToDeg(rotationY)}");
				Transform.Rotation = Quaternion.CreateFromEuler(rotationX, rotationY, 0);
			}
		}

		protected override void OnActivate()
		{
			rotationX = Transform.Rotation.EulerAngles.X;
			rotationY = Transform.Rotation.EulerAngles.Y;
			Transform.Rotation = Quaternion.CreateFromEuler(new Vector3(rotationX, rotationY, 0.0f));

			this.Skull1 = this.Entity.Scene.FindEntity("Skull1");
			this.Skull2 = this.Entity.Scene.FindEntity("Skull2");

			Input.RegisterKeyEvent(Input.Key.Escape, EscapeAction);
			Input.RegisterKeyEvent(Input.Key.F1, F1Action);
			Input.RegisterKeyEvent(Input.Key.F2, F2Action);

			Input.RegisterKeyEvent(Input.Key.Minus, ChangeFOVAction);
			Input.RegisterKeyEvent(Input.Key.Equal, ChangeFOVAction);

			Input.RegisterKeyEvent(Input.Key.LeftShift, BoostAction);

			Console.WriteLine($"{this.Entity.Name} activated");
		}

		private void BoostAction(Input.Key key, Input.KeyAction action)
		{
			if (action == Input.KeyAction.Press)
				this.boost = BoostMultiplier;
			if (action == Input.KeyAction.Release)
				this.boost = 1.0f;
		}

		protected override void OnDeactivate()
		{
			Input.DeregisterKeyEvent(Input.Key.Escape, EscapeAction);
			Input.DeregisterKeyEvent(Input.Key.F1, F1Action);
			Input.DeregisterKeyEvent(Input.Key.F2, F2Action);

			Input.DeregisterKeyEvent(Input.Key.Minus, ChangeFOVAction);
			Input.DeregisterKeyEvent(Input.Key.Equal, ChangeFOVAction);

			Input.DeregisterKeyEvent(Input.Key.LeftShift, BoostAction);

			Console.WriteLine($"{this.Entity.Name} deactivated");
		}

		private void MoveInDirection(Vector3 direction)
		{
			Transform.Position += Transform.Rotation * direction * Time.DeltaTime * MoveSpeed * boost;
		//	Console.WriteLine($"Position: {Transform.Position}");
		}

		private void ChangeFOVAction(Input.Key key, Input.KeyAction action)
		{
			if (action != Input.KeyAction.Repeat && action != Input.KeyAction.Press)
				return;

			var camera = this.Entity.GetComponent<Camera>();
			var fov = camera.FieldOfView;

			if (key == Input.Key.Equal)
			{
				fov += 1.0f;
				if (fov > 170.0f)
					fov = 170.0f;
			}
			else
			{
				fov -= 1.0f;
				if (fov < 10.0f)
					fov = 10.0f;
			}

			camera.FieldOfView = fov;
		}

		private void EscapeAction(Input.Key key, Input.KeyAction action)
		{
			if (action == Input.KeyAction.Press)
				Application.Exit();
		}

		private void F1Action(Input.Key key, Input.KeyAction action)
		{
			if (action == Input.KeyAction.Press)
				reverseX = !reverseX;
		}

		private void F2Action(Input.Key key, Input.KeyAction action)
		{
			if (action == Input.KeyAction.Press)
				reverseY = !reverseY;
		}
	}
}
