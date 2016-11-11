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

		protected virtual void OnCreate()
		{
		}

		protected virtual void OnActivate()
		{
		}

		protected virtual void OnEnable()
		{
		}

		protected virtual void OnUpdate()
		{
		}

		protected virtual void OnDisable()
		{
		}

		protected virtual void OnDeactivate()
		{
		}

		protected virtual void OnDestroy()
		{
		}

		#endregion
	}
}
