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

		protected override void OnCreate()
		{
			var resourceManager = ResourceManager.Instance;
			var scene = this.Scene;
			var shader = this.Shader;

			var noiseTexture = resourceManager.GetResource<Texture>("EngineQ/Random4x4");
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
				ssaoKernel[i] = sample;
			}

			for(int i = 0; i < ssaoKernel.Length; ++i)
			{
				var prop = shader.GetProperty<Vector3f>($"samples[{i}]");
				shader.Set(prop, ssaoKernel[i]);
			}
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