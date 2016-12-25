using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EngineQ.Math
{
	public struct Plane
	{
		public Vector3 Point;
		public Vector3 Normal;

		public Plane(Vector3 point, Vector3 normal)
		{
			this.Point = point;
			this.Normal = normal;
		}
	}
}
