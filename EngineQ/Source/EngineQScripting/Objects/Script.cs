namespace EngineQ
{
	public abstract class Script : Component
	{
		#region Properties

		/// <summary>
		/// Shortcut to invoke <see cref="Component.Entity"/>'s <see cref="Entity.Transform"/>
		/// </summary>
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

		/// <summary>
		/// When overriden, invoked once, on script creation.
		/// </summary>
		protected virtual void OnCreate()
		{
		}

		/// <summary>
		/// When overriden, invoked once, on script first enable
		/// </summary>
		protected virtual void OnActivate()
		{
		}

		/// <summary>
		/// When overriden, invoked everytime script is enabled
		/// </summary>
		protected virtual void OnEnable()
		{
		}

		/// <summary>
		/// When overriden, invoked once every scene update.
		/// </summary>
		protected virtual void OnUpdate()
		{
		}

		/// <summary>
		/// When overriden, invoked everytime script is disabled
		/// </summary>
		protected virtual void OnDisable()
		{
		}

		/// <summary>
		/// When overriden, invoked only once before OnDestroy and only if OnActivate was invoked earlier
		/// </summary>
		protected virtual void OnDeactivate()
		{
		}

		/// <summary>
		/// When overriden, invoked once when script is removed.
		/// </summary>
		protected virtual void OnDestroy()
		{
		}

		#endregion
	}
}
