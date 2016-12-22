using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using EngineQ;
using EngineQ.Math;

namespace QScripts
{
	public class MyEffectController : EffectController
	{
	//	private const int MaxCounter = 60;
	//	private int counter = MaxCounter;
	//	private bool update = false;

		private const float ThresholdStep = 0.05f;
		private ShaderProperty<float> threshold;
		private float thresholdValue = 1.0f;

		protected override void OnCreate()
		{
			Console.WriteLine("MyEffectController.OnCreate");

			threshold = this.Shader.GetProperty<float>("threshold");
			this.Shader.Set(threshold, thresholdValue);

			Input.RegisterKeyEvent(Input.Key.RightBracket, ThresholdAction);
			Input.RegisterKeyEvent(Input.Key.LeftBracket, ThresholdAction);
		}

		private void ThresholdAction(Input.Key key, Input.KeyAction action)
		{
			if (action != Input.KeyAction.Press && action != Input.KeyAction.Repeat)
				return;

			if (key == Input.Key.RightBracket)
			{
				thresholdValue += ThresholdStep;
			}
			else
			{
				thresholdValue -= ThresholdStep;
				if (thresholdValue <= 0.0f)
					thresholdValue = 0.0f;
			}

			Console.WriteLine($"Bloom threshold value: {thresholdValue}");

			this.Shader.Set(threshold, thresholdValue);
		}

		protected override void OnUpdate()
		{
		//	counter += 1;
		//	if (counter >= MaxCounter)
		//	{
		//		counter = 0;
		//		update = true;
		//	}
		//	else
		//	{
		//		update = false;
		//	}
		//
		//	if (update)
		//		Console.WriteLine("MyEffectController.OnUpdate");
		}

		protected override void OnBeforeRender()
		{
		//	if (update)
		//		Console.WriteLine("MyEffectController.OnBeforeRender");
		}

		protected override void OnAfterRender()
		{
		//	if (update)
		//		Console.WriteLine("MyEffectController.OnAfterRender");
		}

		protected override void OnDestroy()
		{
			Console.WriteLine("MyEffectController.OnDestroy");

			Input.DeregisterKeyEvent(Input.Key.RightBracket, ThresholdAction);
			Input.DeregisterKeyEvent(Input.Key.LeftBracket, ThresholdAction);
		}
	}
}
