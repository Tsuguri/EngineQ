namespace EngineQ.Math
{
	public struct Ray
	{
		public Vector3 Origin;
		public Vector3 Direction;

		public Ray(Vector3 origin, Vector3 direction)
		{
			this.Origin = origin;
			this.Direction = direction;
		}

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
