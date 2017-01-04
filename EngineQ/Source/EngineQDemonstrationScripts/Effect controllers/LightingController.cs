using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using EngineQ;
using EngineQ.Math;

namespace QScripts
{
	public class LightingController : EffectController
	{
		ShaderProperty<bool> useSSAOProp;
		ShaderProperty<bool> usePCFProp;
		ShaderProperty<bool> useRaysProp;

		protected override void OnCreate()
		{
			var changer = this.Scene.ActiveCamera.Entity.GetComponent<OptionChanger>();

			this.useSSAOProp = this.Shader.GetProperty<bool>("useSSAO");
			changer.AddOption(new SimpleBoolOption("Use SSAO", true, (bool value) => { this.Shader.Set(useSSAOProp, value); }));

			this.usePCFProp = this.Shader.GetProperty<bool>("usePCF");
			changer.AddOption(new SimpleBoolOption("Use PCF", true, (bool value) => { this.Shader.Set(usePCFProp, value); }));

			this.useRaysProp = this.Shader.GetProperty<bool>("useRays");
			changer.AddOption(new SimpleBoolOption("Use Rays", true, (bool value) => { this.Shader.Set(useRaysProp, value); }));
		}
	}
}
