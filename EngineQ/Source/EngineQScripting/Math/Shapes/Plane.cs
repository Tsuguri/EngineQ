using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EngineQ.Math
{
	/// <summary>
	/// Math representation of infinite plane based on central <see cref="Vector3"/> point and Normal <see cref="Vector3"/>.
	/// </summary>
	public struct Plane
	{
		/// <summary>
		/// Central point of plane.
		/// </summary>
		public Vector3 Point;

		/// <summary>
		/// Normal <see cref="Vector3"/> to <see cref="Plane"/> surface.
		/// </summary>
		public Vector3 Normal;

		public Plane(Vector3 point, Vector3 normal)
		{
			this.Point = point;
			this.Normal = normal;
		}
	}
}
