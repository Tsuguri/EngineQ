using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using EngineQ;
using EngineQ.Math;

namespace QScripts
{
	public class SSRController : EffectController
	{
		private ShaderProperty<bool> enabledProp;

		protected override void OnCreate()
		{
			var changer = this.Scene.ActiveCamera.Entity.GetComponent<OptionChanger>();

			this.enabledProp = this.Shader.GetProperty<bool>("enabled");
			changer.AddOption(new SimpleBoolOption("Use SSR", true, (bool value) => { this.Shader.Set(enabledProp, value); }));
		}
	}
}
