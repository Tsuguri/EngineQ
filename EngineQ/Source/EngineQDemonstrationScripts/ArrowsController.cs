using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using EngineQ;
using EngineQ.Math;

namespace QScripts
{
	public class ArrowsController : Script
	{
		private Transform arrowX;
		private Transform arrowY;
		private Transform arrowZ;

		private const float capsuleRadius = 0.1f;
		private const float capsuleHeight = 1.0f - 2.0f * capsuleRadius;
		private const float capsulePosition = capsuleRadius;

		private Vector3 capsulePoint1 = new Vector3(0.0f, capsulePosition, 0.0f);
		private Vector3 capsulePoint2 = new Vector3(0.0f, capsulePosition + capsuleHeight, 0.0f);

		private Transform SetupArrow(Vector3 angles, string name, Vector3 color)
		{
			var resourceManager = ResourceManager.Instance;
			var shader = resourceManager.GetResource<Shader>("ArrowsDeferred");
			var mesh = resourceManager.GetResource<Mesh>("Arrow");

			var entity = this.Entity.Scene.CreateEntity(true, name);

			var transform = entity.Transform;
			transform.Rotation = Quaternion.CreateFromEuler(angles);
			transform.Parent = this.Transform;

			var renderable = entity.AddComponent<Renderable>(false);
			renderable.UseDeferredShader(shader);
			renderable.DeferredShader.Material.Diffuse = (Vector3f)color;
			renderable.Mesh = mesh;

			// TMP
			
			var capsule = PrefabGenerator.GenerateCapsule(capsuleHeight, capsuleRadius);
			
			var capsuleEntity = this.Entity.Scene.CreateEntity();
			capsuleEntity.Transform.Parent = transform;
			capsuleEntity.Transform.Position = new Vector3(0.0f, capsulePosition + capsuleHeight * 0.5f, 0.0f);
			
			var capsuleRenderable = capsuleEntity.AddComponent<Renderable>();
			capsuleRenderable.Mesh = capsule;
			capsuleRenderable.UseDeferredShader(shader);
			capsuleRenderable.DeferredShader.Material.Diffuse = (Vector3f)color;
			

			return transform;
		}

		protected override void OnActivate()
		{
			this.arrowX = SetupArrow(new Vector3(0.0f, 0.0f, Utils.DegToRad(90)), "ArrowX", new Vector3(1.0f, 0.0f, 0.0f));
			this.arrowY = SetupArrow(new Vector3(0.0f, 0.0f, 0.0f), "ArrowY", new Vector3(0.0f, 1.0f, 0.0f));
			this.arrowZ = SetupArrow(new Vector3(Utils.DegToRad(90), 0.0f, 0.0f), "ArrowZ", new Vector3(0.0f, 0.0f, 1.0f));

			Input.RegisterMouseButtonEvent(Input.MouseButton.Left, ArrowPressAction);
		}

		private bool HittestArrow(Transform arrow, Ray ray)
		{
			var matrix = arrow.GlobalMatrix;

			var p1 = Matrix4.TransformPosition(matrix, capsulePoint1);
			var p2 = Matrix4.TransformPosition(matrix, capsulePoint2);

			var distance = Utils.SegmentToRayDistance(new Segment(p1, p2), ray);

			return distance <= capsuleRadius;
		}

		private void ArrowPressAction(Input.MouseButton button, Input.KeyAction action)
		{
			if(action == Input.KeyAction.Press)
			{
				var ray = this.Entity.Scene.ActiveCamera.GetViewRay(new Vector2(2.0f, -2.0f) * Input.MousePosition / (Vector2)Application.ScreenSize + new Vector2(-1.0f, 1.0f));

				if(HittestArrow(this.arrowX, ray))
				{
					Console.WriteLine($"Hit {arrowX.Entity.Name}");
				}
				if (HittestArrow(this.arrowY, ray))
				{
					Console.WriteLine($"Hit {arrowY.Entity.Name}");
				}
				if (HittestArrow(this.arrowZ, ray))
				{
					Console.WriteLine($"Hit {arrowZ.Entity.Name}");
				}
			}
		}
	}
}
