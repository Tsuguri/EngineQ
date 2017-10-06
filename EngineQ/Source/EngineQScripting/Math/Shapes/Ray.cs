namespace EngineQ.Math
{
	/// <summary>
	/// Math prepresentation of ray. It starts in Origin point and infinitely expands in given Direction.
	/// </summary>
	public struct Ray
	{
		/// <summary>
		/// Start point of <see cref="Ray"/>.
		/// </summary>
		public Vector3 Origin;

		/// <summary>
		/// Direction in which <see cref="Ray"/> is expanding.
		/// </summary>
		public Vector3 Direction;

		public Ray(Vector3 origin, Vector3 direction)
		{
			this.Origin = origin;
			this.Direction = direction;
		}

		/// <summary>
		/// Creates <see cref="Vector3"/> coordinates of point in given <paramref name="distance"/> from <see cref="Origin"/>.
		/// </summary>
		/// <param name="distance">Distance from <see cref="Origin"/> along <see cref="Direction"/> line.</param>
		/// <returns>Coordinates of point.</returns>
		public Vector3 GetPoint(float distance)
		{
			return Origin + Direction * distance;
		}

		public override string ToString()
		{
			return $"({Origin},{Direction})";
		}
	}
}
