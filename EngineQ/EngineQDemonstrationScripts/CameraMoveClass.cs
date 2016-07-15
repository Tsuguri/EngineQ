using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using EngineQ;
using EngineQ.Math;


namespace QScripts
{
	public class CameraMoveClass : Script
	{
		public CameraMoveClass()
		{
			Input.ListenKey(Input.Key.A, AKeyAction);
			Input.ListenKey(Input.Key.Escape, EscapeAction);
			Input.ListenKey(Input.Key.Space, SpaceAction);
		}



		protected override void Update()
		{
			base.Update();

		}
		private void SpaceAction(Input.KeyAction action)
		{
			var p = Entity.Transform.Position;
			p.Y = (float)Math.Sin(Time.TimeFromStart);
			Console.WriteLine(p + " " + Input.MousePosition);
			Entity.Transform.Position = p;
		}

		private void AKeyAction(Input.KeyAction action)
		{
			Console.WriteLine("a key: "+action);
		}

		private void EscapeAction(Input.KeyAction action)
		{
			if(action== Input.KeyAction.Press)
				Application.Exit();
		}
	}
}
