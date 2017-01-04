using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using EngineQ;
using EngineQ.Math;

namespace QScripts
{
	public class CombineController : EffectController
	{
		private ShaderProperty<float> exposureProp;
		private ShaderProperty<float> gammaProp;

		protected override void OnCreate()
		{
			var changer = this.Scene.ActiveCamera.Entity.GetComponent<OptionChanger>();


			this.exposureProp = this.Shader.GetProperty<float>("exposure");
			changer.AddOption(new SimpleFloatOption("Exposure", 1.1f, 0.1f, 5.0f, 0.01f, (float value) => { this.Shader.Set(this.exposureProp, value); }));
			
			this.gammaProp = this.Shader.GetProperty<float>("gamma");
			changer.AddOption(new SimpleFloatOption("Gamma", 2.2f, 0.1f, 5.0f, 0.01f, (float value) => { this.Shader.Set(this.gammaProp, value); }));
		}
	}
}
