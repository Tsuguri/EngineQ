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
		ShaderProperty<float> timeProp;

		float time = 0.0f;

		protected override void OnCreate()
		{
			var changer = this.Scene.ActiveCamera.Entity.GetComponent<OptionChanger>();

			this.useSSAOProp = this.Shader.GetProperty<bool>("useSSAO");
			changer.AddOption(new SimpleBoolOption("Use SSAO", true, (bool value) => { this.Shader.Set(useSSAOProp, value); }));

			this.usePCFProp = this.Shader.GetProperty<bool>("usePCF");
			changer.AddOption(new SimpleBoolOption("Use PCF", true, (bool value) => { this.Shader.Set(usePCFProp, value); }));

			this.useRaysProp = this.Shader.GetProperty<bool>("useRays");
			changer.AddOption(new SimpleBoolOption("Use Rays", true, (bool value) => { this.Shader.Set(useRaysProp, value); }));

			this.timeProp = this.Shader.GetProperty<float>("time");
		}

		protected override void OnUpdate()
		{
			time += Time.DeltaTime / 10.0f;
			if (time > Math.PI * 2.0f)
				time -= (float)Math.PI * 2.0f;

			this.Shader.Set(timeProp, time);
		}
	}
}
