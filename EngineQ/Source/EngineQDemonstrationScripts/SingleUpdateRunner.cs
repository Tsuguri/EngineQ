using System;

using EngineQ;

namespace QScripts
{
	public class SingleUpdateRunner : Script
	{
		public event Action RunEvent;

		protected override void OnUpdate()
		{
			if (RunEvent != null)
				RunEvent.Invoke();
			
			this.Entity.RemoveComponent(this);
		}
	}
}
