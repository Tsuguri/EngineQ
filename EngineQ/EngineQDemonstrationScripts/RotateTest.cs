using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using EngineQ;
using EngineQ.Math;

namespace QScripts
{
	class RotateTest : Script
	{
		private float X = 0, Y = 0;
		private int mode = 0;
		private Renderable renderable;

		public RotateTest()
		{
			Input.ListenKey(Input.Key.N1, SwitchAction);

			renderable = this.Entity.GetComponent<Renderable>();
		}

		private void SwitchAction(Input.KeyAction action)
		{
			mode = (mode + 1) % 3;
		}


		private void CheckAngles()
		{
			if (X > 360)
				X -= 360;
			if (Y > 360)
				Y -= 360;
		}
		private float DegToRad(float val)
		{
			return (float)(Math.PI * val / 180);
		}

		protected override void Update()
		{
			base.Update();

			X += 30 * Time.DeltaTime;
			Y += 30 * Time.DeltaTime;
			CheckAngles();
			switch (mode)
			{
				case 0:
					transform.Rotation = Quaternion.CreateFromEuler(DegToRad(X), DegToRad(Y), 0);
					break;
				case 1:
					transform.Rotation = Quaternion.CreateFromEuler(0, DegToRad(Y), 0);
					break;
				case 2:
					transform.Rotation = Quaternion.CreateFromEuler(DegToRad(X), 0, 0);
					break;
			}


		}
	}
}
