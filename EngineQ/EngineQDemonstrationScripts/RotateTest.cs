using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using EngineQ;
using EngineQ.Math;

namespace QScripts
{
	public class RotateTest : Script
	{
		private float X = 0, Y = 0;
		private int mode = 0;

		private Random random = new Random();

		public RotateTest()
		{
			Input.RegisterKeyEvent(Input.Key.N1, SwitchAction);

			Input.RegisterKeyEvent(Input.Key.LeftBracket, ChangeShader1);
			Input.RegisterKeyEvent(Input.Key.RightBracket, ChangeShader2);
		}

		private void SwitchAction(Input.Key key, Input.KeyAction action)
		{
			mode = (mode + 1) % 3;
		}

		private void ChangeShader1(Input.Key key, Input.KeyAction action)
		{
			if(action == Input.KeyAction.Press)
			{
				Renderable renderable = this.Entity.GetComponent<Renderable>();

				renderable.UseDeferredShader(ResourceManager.Instance.GetResource<Shader>("TestDeferred1"));

				var myColorProperty = renderable.DeferredShader.GetProperty<Vector3f>("material.diffuse");
				
				renderable.DeferredShader.Set(myColorProperty, new Vector3f((float)random.NextDouble(), (float)random.NextDouble(), (float)random.NextDouble()));
				Vector3f color = renderable.DeferredShader.Get(myColorProperty);


				Mesh mesh = ResourceManager.Instance.GetResource<Mesh>("EngineQ/Cube");
				renderable.Mesh = mesh;

				Console.WriteLine($"Set color to {color}");
			}
		}

		private void ChangeShader2(Input.Key key, Input.KeyAction action)
		{
			if (action == Input.KeyAction.Press)
			{
				Renderable renderable = this.Entity.GetComponent<Renderable>();

				renderable.UseDeferredShader(ResourceManager.Instance.GetResource<Shader>("TestDeferred2"));

				var texture = ResourceManager.Instance.GetResource<Texture>("Numbers");

				var texturePropert = renderable.DeferredShader.GetProperty<Texture>("material.diffuseTexture");
				renderable.DeferredShader.Set(texturePropert, texture);

				Mesh mesh = ResourceManager.Instance.GetResource<Mesh>("Skull");
				renderable.Mesh = mesh;
			}
		}

		private void CheckAngles()
		{
			if (X > 360)
				X -= 360;
			if (Y > 360)
				Y -= 360;
		}
		private float DegToRad(float val)
		{
			return (float)(Math.PI * val / 180);
		}

		protected override void OnUpdate()
		{
			base.OnUpdate();

			X += 30 * Time.DeltaTime;
			Y += 30 * Time.DeltaTime;
			CheckAngles();
			switch (mode)
			{
				case 0:
					Transform.Rotation = Quaternion.CreateFromEuler(DegToRad(X), DegToRad(Y), 0);
					break;
				case 1:
					Transform.Rotation = Quaternion.CreateFromEuler(0, DegToRad(Y), 0);
					break;
				case 2:
					Transform.Rotation = Quaternion.CreateFromEuler(DegToRad(X), 0, 0);
					break;
			}
		}

		protected override void OnActivate()
		{
			Console.WriteLine($"{this.Entity.Name} activated");
		}

		protected override void OnDeactivate()
		{
			Console.WriteLine($"{this.Entity.Name} deactivated");
		}

		protected override void OnDisable()
		{
			Console.WriteLine($"{this.Entity.Name} disabled");
		}

		protected override void OnEnable()
		{
			Console.WriteLine($"{this.Entity.Name} enabled");
		}
	}
}
