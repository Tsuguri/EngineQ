using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using EngineQ;
using EngineQ.Math;

namespace QScripts
{
	public class TesterScript : EngineQ.Script
	{
		private Vector2 lastMousePos;

		protected override void OnEnable()
		{
			lastMousePos = Input.MousePosition;
		}

		protected override void OnUpdate()
		{
			var currMousePos = Input.MousePosition;
			if(lastMousePos != currMousePos)
			{
		//		Console.WriteLine("Mouse pos: {0}", currMousePos);
				lastMousePos = currMousePos;
			}

		}
	}
}
