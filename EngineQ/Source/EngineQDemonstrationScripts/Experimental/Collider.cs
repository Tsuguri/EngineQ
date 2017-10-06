using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using EngineQ;
using EngineQ.Math;

namespace QScripts
{
	public abstract class Collider : Script
	{
		public abstract bool RayCast(Ray ray, out float distance);
	}
}
