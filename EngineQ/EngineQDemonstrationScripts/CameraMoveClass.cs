using System;

using EngineQ;
using EngineQ.Math;


namespace QScripts
{
	public class CameraMoveClass : Script
	{ 
		private Vector3 tmp;
		private Vector2 tmp2;
		public CameraMoveClass()
		{
			Input.ListenKey(Input.Key.Escape, EscapeAction);
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
	}
}
