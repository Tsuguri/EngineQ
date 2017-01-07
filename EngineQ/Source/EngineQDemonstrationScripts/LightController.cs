using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using EngineQ;
namespace QScripts
{
	class LightController : Script
	{
		Light light;
		private void ResizeDown(Input.Key key, Input.KeyAction action)
		{
			if (action == Input.KeyAction.Press && light != null)
			{
				light.TextureSize = light.TextureSize / 2;
				Console.WriteLine("Pressed: " + light.TextureSize);

			}
		}

		private void ResizeUp(Input.Key key, Input.KeyAction action)
		{
			if (action == Input.KeyAction.Press && light != null)
			{
				light.TextureSize = light.TextureSize * 2;
				Console.WriteLine("Pressed: " + light.TextureSize);

			}
		}

		protected override void OnActivate()
		{
			light = Entity.GetComponent<Light>();
			Input.RegisterKeyEvent(Input.Key.K, ResizeDown);
			Input.RegisterKeyEvent(Input.Key.L, ResizeUp);
		}

		protected override void OnDeactivate()
		{
			Input.DeregisterKeyEvent(Input.Key.K, ResizeDown);
			Input.DeregisterKeyEvent(Input.Key.L, ResizeUp);
		}
	}
}
