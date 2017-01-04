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
		private ShaderProperty<int> drawImageProp;

		private enum DrawImage
		{
			Normal,
			SSAO,
		}

		protected override void OnCreate()
		{
			var changer = this.Scene.ActiveCamera.Entity.GetComponent<OptionChanger>();


			this.exposureProp = this.Shader.GetProperty<float>("exposure");
			changer.AddOption(new SimpleFloatOption("Exposure", 1.1f, 0.1f, 5.0f, 0.01f, (float value) => { this.Shader.Set(this.exposureProp, value); }));

			this.gammaProp = this.Shader.GetProperty<float>("gamma");
			changer.AddOption(new SimpleFloatOption("Gamma", 2.2f, 0.1f, 5.0f, 0.01f, (float value) => { this.Shader.Set(this.gammaProp, value); }));

			this.drawImageProp = this.Shader.GetProperty<int>("drawImage");
			changer.AddOption(new GenericOption<DrawImage>("Draw Image", DrawImageHandler, DrawImage.Normal));
		}

		private void DrawImageHandler(ref DrawImage value, int direction)
		{
			if (direction != 0)
				direction = direction / Math.Abs(direction);
			
			int val = (int)value;
			var len = Enum.GetNames(typeof(DrawImage)).Length;

			val = (val + len + direction) % len;

			this.Shader.Set(drawImageProp, val);

			value = (DrawImage)val;
		}
	}
}
