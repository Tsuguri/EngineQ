namespace EngineQ
{
	public abstract class Script : Component
	{
		#region Properties

		protected Transform Transform
		{
			get
			{
				return this.Entity.Transform;
			}
		}

		#endregion

		#region Constructors

		protected Script()
		{
		}

		#endregion

		#region Methods

		protected virtual void Update()
		{
		}

		#endregion
	}
}
