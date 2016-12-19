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
				
		private void SwitchAction(Input.Key key, Input.KeyAction action)
		{
			mode = (mode + 1) % 3;
		}

		private void ChangeShader1(Input.Key key, Input.KeyAction action)
		{
			if(action == Input.KeyAction.Press)
			{
				var resourceManager = ResourceManager.Instance;
				var renderable = this.Entity.GetComponent<Renderable>();

				renderable.UseDeferredShader(resourceManager.GetResource<Shader>("TestDeferred1"));

				renderable.DeferredShader.Material.Diffuse = new Vector3f((float)random.NextDouble(), (float)random.NextDouble(), (float)random.NextDouble());

				renderable.Mesh = resourceManager.GetResource<Mesh>("EngineQ/Cube");

				Console.WriteLine($"Set diffuse color to {renderable.DeferredShader.Material.Diffuse}");
			}
		}

		private void ChangeShader2(Input.Key key, Input.KeyAction action)
		{
			if (action == Input.KeyAction.Press)
			{
				var resourceManager = ResourceManager.Instance;
				var renderable = this.Entity.GetComponent<Renderable>();

				renderable.UseDeferredShader(resourceManager.GetResource<Shader>("TestDeferred2"));

				renderable.DeferredShader.Material.DiffuseTexture = resourceManager.GetResource<Texture>("Numbers");

				renderable.Mesh = resourceManager.GetResource<Mesh>("Skull");
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

		protected override void OnCreate()
		{
			Console.WriteLine($"{this.Entity.Name} created");

			Input.RegisterKeyEvent(Input.Key.N1, SwitchAction);

			Input.RegisterKeyEvent(Input.Key.LeftBracket, ChangeShader1);
			Input.RegisterKeyEvent(Input.Key.RightBracket, ChangeShader2);
		}

		protected override void OnDestroy()
		{
			Console.WriteLine($"{this.Entity.Name} destroyed");

			Input.DeregisterKeyEvent(Input.Key.N1, SwitchAction);

			Input.DeregisterKeyEvent(Input.Key.LeftBracket, ChangeShader1);
			Input.DeregisterKeyEvent(Input.Key.RightBracket, ChangeShader2);
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
