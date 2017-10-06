namespace EngineQ.Math
{
	/// <summary>
	/// Math representation of sphere. Based on central point and sphere radius.
	/// </summary>
	public struct Sphere
	{
		/// <summary>
		/// Coordinates of sphere centrum.
		/// </summary>
		public Vector3 Center;

		/// <summary>
		/// Radius of sphere.
		/// </summary>
		public float Radius;

		public Sphere(Vector3 center, float radius)
		{
			this.Center = center;
			this.Radius = radius;
		}
	}
}
