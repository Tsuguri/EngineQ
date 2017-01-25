using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using EngineQ;
using EngineQ.Math;

namespace QScripts
{
	public class BrightExtractController : EffectController
	{
		private ShaderProperty<float> thresholdProp;
		private ShaderProperty<bool> enabledProp;

		protected override void OnCreate()
		{
			var changer = this.Scene.ActiveCamera.Entity.GetComponent<OptionChanger>();

			this.enabledProp = this.Shader.GetProperty<bool>("enabled");
			changer.AddOption(new SimpleBoolOption("Use Bloom", true, (bool value) => { this.Shader.Set(this.enabledProp, value); }));

			this.thresholdProp = this.Shader.GetProperty<float>("threshold");
			changer.AddOption(new SimpleFloatOption("Bloom Threshold", 1.0f, 0.0f, 5.0f, 0.01f, (float value) => { this.Shader.Set(this.thresholdProp, value); }));
		}
	}
}
