using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EngineQ.Math
{
	public struct Capsule
	{
		public Vector3 Point1;
		public Vector3 Point2;
		public float Radius;

		public Capsule(Vector3 point1, Vector3 point2, float radius)
		{
			this.Point1 = point1;
			this.Point2 = point2;
			this.Radius = radius;
		}
	}
}
