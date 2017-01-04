﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using EngineQ;
using EngineQ.Math;

namespace QScripts
{
	public class SSAOController : EffectController
	{
		private ShaderProperty<Matrix4> projectionMatrixProp;

		private ShaderProperty<int> screenWidthProp;
		private ShaderProperty<int> screenHeightProp;

		private ShaderProperty<float> radiusProp;
		private ShaderProperty<float> powerRadius;

		protected override void OnCreate()
		{
			var resourceManager = ResourceManager.Instance;
			var scene = this.Scene;
			var shader = this.Shader;

			var noiseTexture = PrefabGenerator.GenerateNoiseTexture(4, 4);
			var noiseTextureProp = shader.GetProperty<Texture>("noiseTexture");
			shader.Set(noiseTextureProp, noiseTexture);
			
			screenWidthProp = shader.GetProperty<int>("screenWidth");
			screenHeightProp = shader.GetProperty<int>("screenHeight");
			
			projectionMatrixProp = shader.GetProperty<Matrix4>("projection");

			Random rand = new Random();

			var ssaoKernel = new Vector3f[64];
			for(int i = 0; i < ssaoKernel.Length; ++i)
			{
				Vector3f sample = new Vector3f((float)rand.NextDouble() * 2.0f - 1.0f, (float)rand.NextDouble() * 2.0f - 1.0f, (float)rand.NextDouble());
				sample.Normalize();
				sample *= (float)rand.NextDouble();

				float scale = (float)i / (float)ssaoKernel.Length;
				scale = Utils.Lerp(0.1f, 1.0f, scale * scale);
				sample *= scale;
				ssaoKernel[i] = sample;
			}

			for(int i = 0; i < ssaoKernel.Length; ++i)
			{
				var prop = shader.GetProperty<Vector3f>($"samples[{i}]");
				shader.Set(prop, ssaoKernel[i]);
			}


			var changer = this.Scene.ActiveCamera.Entity.GetComponent<OptionChanger>();

			this.radiusProp = this.Shader.GetProperty<float>("radius");
			changer.AddOption(new SimpleFloatOption("SSAO Radius", 1.0f, 0.01f, 5.0f, 0.01f, (float value) => { this.Shader.Set(this.radiusProp, value); }));

			this.powerRadius = this.Shader.GetProperty<float>("power");
			changer.AddOption(new SimpleFloatOption("SSAO Power", 4.0f, 0.1f, 20.0f, 0.1f, (float value) => { this.Shader.Set(this.powerRadius, value); }));
		}

		protected override void OnBeforeRender()
		{
			var shader = this.Shader;
			var scene = this.Scene;
			
			var projectionMatrix = scene.ActiveCamera.ProjectionMatrix;
			shader.Set(projectionMatrixProp, projectionMatrix);

			var screenSize = Application.ScreenSize;
			shader.Set(screenWidthProp, screenSize.X);
			shader.Set(screenHeightProp, screenSize.Y);
		}
	}
}