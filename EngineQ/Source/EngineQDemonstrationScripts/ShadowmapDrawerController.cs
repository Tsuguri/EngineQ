using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using EngineQ;
using EngineQ.Math;

namespace QScripts
{
	public class ShadowmapDrawerController : EffectController
	{
		private const int MaxMode = 3;

		private int mode = 0;
		ShaderProperty<int> modeProp;

		protected override void OnCreate()
		{
			modeProp = this.Shader.GetProperty<int>("mode");
			this.Shader.Set(modeProp, mode);

			Input.RegisterKeyEvent(Input.Key.Kp8, ChangeModeAction);
			Input.RegisterKeyEvent(Input.Key.Kp2, ChangeModeAction);
		}

		private void ChangeModeAction(Input.Key key, Input.KeyAction action)
		{
			if (action != Input.KeyAction.Press)
				return;

			if (key == Input.Key.Kp8)
			{
				mode = (mode + 1) % MaxMode;
			}
			else
			{
				mode = (mode + MaxMode - 1) % MaxMode;
			}

			this.Shader.Set(modeProp, mode);
		}

		protected override void OnDestroy()
		{
			Input.DeregisterKeyEvent(Input.Key.Kp2, ChangeModeAction);
			Input.DeregisterKeyEvent(Input.Key.Kp8, ChangeModeAction);
		}
	}
}
