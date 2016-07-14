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
		public override void Update()
		{
			base.Update();

			if (Input.KeyPressed(Input.Key.Space))
			{
				var p = Entity.Transform.Position;
				p.Y = (float)Math.Sin(Time.TimeFromStart);
				Console.WriteLine(p);
				Entity.Transform.Position = p;
			}
		}
	}
}
