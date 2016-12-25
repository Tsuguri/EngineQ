namespace EngineQ.Math
{
	public struct Segment
	{
		public Vector3 Point1;
		public Vector3 Point2;

		public Segment(Vector3 point1, Vector3 point2)
		{
			this.Point1 = point1;
			this.Point2 = point2;
		}

		public override string ToString()
		{
			return $"{{{Point1},{Point2}}}";
		}
	}
}
