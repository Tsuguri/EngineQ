namespace EngineQ
{
	/// <summary>
	/// Object representing location of single <see cref="Shader"/> property retrieved from GPU data. Should be used together with <see cref="ShaderProperties"/>
	/// </summary>
	/// <typeparam name="TPropertyType"></typeparam>
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
