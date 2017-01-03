using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using EngineQ;
using EngineQ.Math;

namespace QScripts
{
	public class ColliderPicker : Script
	{
		protected override void OnActivate()
		{
			Input.RegisterMouseButtonEvent(Input.MouseButton.Left, LeftMouseAction);
		}

		protected override void OnDeactivate()
		{
			Input.DeregisterMouseButtonEvent(Input.MouseButton.Left, LeftMouseAction);
		}

		private Camera camera;
		private Vector2 lastMousePosition;

		public void Initialize(Camera camera)
		{
			this.camera = camera;
		}

		private void LeftMouseAction(Input.MouseButton button, Input.KeyAction action)
		{
			if (action == Input.KeyAction.Press)
			{
				lastMousePosition = Input.MousePosition;
			}

			if (action == Input.KeyAction.Release)
			{
				var pos = Input.MousePosition;
				var screenSize = Application.ScreenSize;

				if ((this.lastMousePosition - pos).Length < 10.0f)
				{
					var ray = camera.GetViewRay(new Vector2(2.0f * (float)pos.X / (float)screenSize.X - 1.0f, -2.0f * (float)pos.Y / (float)screenSize.Y + 1.0f));

					float closestDistance = float.PositiveInfinity;
					Collider closestCollider = null;
					
					var scene = this.Entity.Scene;
					for (int i = 0; i < scene.EntitiesCount; ++i)
					{
						var entity = scene.GetEntity(i);

						var collider = entity.GetComponent<Collider>();
						if (collider == null)
							continue;

						float distance = 0.0f;
						if (collider.RayCast(ray, out distance))
						{
							if (closestDistance > distance)
							{
								closestDistance = distance;
								closestCollider = collider;
							}
						}
					}

					if(closestCollider != null)
					{
						Console.WriteLine($"Pressed at {closestCollider.Entity.Name}");

						var arrows = scene.FindEntity("Arrows");

						arrows.Enabled = true;


						arrows.Transform.Position = closestCollider.Entity.Transform.GlobalPosition;
						arrows.Transform.Rotation = closestCollider.Entity.Transform.GlobalRotation;

						arrows.GetComponent<ArrowsController>().SetTransform(closestCollider.Entity.Transform);
					}
					else
					{
						var arrows = scene.FindEntity("Arrows");

						arrows.Enabled = false;

						Console.WriteLine("No collider found");
					}
				}
			}
		}
	}
}
