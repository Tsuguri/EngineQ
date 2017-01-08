using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EngineQ.Math
{
	/// <summary>
	/// Representation of capsule based on two points and capsule radius.
	/// </summary>
	public struct Capsule
	{
		/// <summary>
		/// Coordinates of first <see cref="Capsule"/>'s point.
		/// </summary>
		public Vector3 Point1;

		/// <summary>
		/// Coordinates of second <see cref="Capsule"/>'s point.
		/// </summary>
		public Vector3 Point2;

		/// <summary>
		/// Radius of capsule.
		/// </summary>
		public float Radius;

		public Capsule(Vector3 point1, Vector3 point2, float radius)
		{
			this.Point1 = point1;
			this.Point2 = point2;
			this.Radius = radius;
		}
	}
}
