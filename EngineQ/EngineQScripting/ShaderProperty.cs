namespace EngineQ
{
	public struct ShaderProperty<TPropertyType>
	{
		private readonly int index;

		internal int Index
		{
			get
			{
				return this.index - 1;
			}
		}

		internal ShaderProperty(int index)
		{
			this.index = index + 1;
		}
	}
}
