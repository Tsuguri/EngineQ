namespace EngineQ
{
	public abstract class Script : Component
	{
		protected Transform transform => Entity.Transform;

		protected virtual void Update()
		{

		}
	}
}
