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
			transform.Scale = new Vector3(0.4f);

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
			this.arrowX = SetupArrow(new Vector3(0.0f, 0.0f, Utils.DegToRad(-90)), "ArrowX", new Vector3(1.0f, 0.0f, 0.0f));
			this.arrowY = SetupArrow(new Vector3(0.0f, 0.0f, 0.0f), "ArrowY", new Vector3(0.0f, 1.0f, 0.0f));
			this.arrowZ = SetupArrow(new Vector3(Utils.DegToRad(90), 0.0f, 0.0f), "ArrowZ", new Vector3(0.0f, 0.0f, 1.0f));

			Input.RegisterMouseButtonEvent(Input.MouseButton.Left, ArrowPressAction);

			this.Transform.Rotation = Quaternion.CreateFromEuler(1.3f, -2.0f, 0.4f);
		}

		private bool HittestArrow(Transform arrow, Ray ray, out float distance)
		{
			var matrix = arrow.GlobalMatrix;

			var p1 = Matrix4.TransformPosition(matrix, capsulePoint1);
			var p2 = Matrix4.TransformPosition(matrix, capsulePoint2);
			var r = arrow.Scale.X * capsuleRadius;
			
			return Utils.RayCapsuleIntersection(new Capsule(p1, p2, r), ray, out distance);
		}

		private bool pressed = false;
		private Vector3 initialPosition;
		private Vector3 initialRayIntersection;

		private Vector3 arrowDir;

		private Transform transform;

		private void ArrowPressAction(Input.MouseButton button, Input.KeyAction action)
		{
			if(action == Input.KeyAction.Press)
			{
				var ray = this.Entity.Scene.ActiveCamera.GetViewRay(new Vector2(2.0f, -2.0f) * Input.MousePosition / (Vector2)Application.ScreenSize + new Vector2(-1.0f, 1.0f));

				Transform minTransform = null;
				float distance;
				float minDistance = float.PositiveInfinity;

				if(HittestArrow(this.arrowX, ray, out distance))
				{
					if(minDistance > distance)
					{
						minDistance = distance;
						minTransform = arrowX;
					}
				}
				if (HittestArrow(this.arrowY, ray, out distance))
				{
					if (minDistance > distance)
					{
						minDistance = distance;
						minTransform = arrowY;
					}
				}
				if (HittestArrow(this.arrowZ, ray, out distance))
				{
					if (minDistance > distance)
					{
						minDistance = distance;
						minTransform = arrowZ;
					}
				}

				if (minTransform != null)
				{
					this.arrowDir = minTransform.GlobalRotation * Vector3.Up;

					Vector3 cameraDir = (this.Entity.Scene.ActiveCamera.Entity.Transform.GlobalPosition - this.Transform.GlobalPosition).Normalized;

					Vector3 localUp = Vector3.CrossProduct(arrowDir, cameraDir).Normalized;
					Vector3 planeNormal = Vector3.CrossProduct(arrowDir, localUp);

				//	Console.WriteLine($"Arrow dir    {arrowDir}");
				//	Console.WriteLine($"Plane normal {planeNormal}");
				//	Console.WriteLine($"Local up     {localUp}");
				
					if (Utils.RayPlaneIntersection(new Plane(this.Transform.GlobalPosition, planeNormal), ray, out distance))
					{
						this.initialRayIntersection = ray.GetPoint(distance);
						this.initialPosition = this.Transform.GlobalPosition;
						this.pressed = true;
					}
				}
			}

			if(action == Input.KeyAction.Release)
			{
				pressed = false;
			}
		}

		protected override void OnUpdate()
		{
			if (pressed)
			{
				var ray = this.Entity.Scene.ActiveCamera.GetViewRay(new Vector2(2.0f, -2.0f) * Input.MousePosition / (Vector2)Application.ScreenSize + new Vector2(-1.0f, 1.0f));
				
				Vector3 cameraDir = (this.Entity.Scene.ActiveCamera.Entity.Transform.GlobalPosition - this.Transform.GlobalPosition).Normalized;
				Vector3 localUp = Vector3.CrossProduct(arrowDir, cameraDir).Normalized;
				Vector3 planeNormal = Vector3.CrossProduct(arrowDir, localUp);
				
				float distance;
				if (Utils.RayPlaneIntersection(new Plane(this.Transform.GlobalPosition, planeNormal), ray, out distance))
				{
					Vector3 intersectionPoint = ray.GetPoint(distance);

					Vector3 diff = intersectionPoint - this.initialRayIntersection;

					Vector3 diffInDirection = Project(diff, arrowDir);

					this.Transform.GlobalPosition = this.initialPosition + diffInDirection;

					if(transform != null)
					{
						transform.GlobalPosition = this.Transform.GlobalPosition;
					}
				}
			}
		}

		private Vector3 Project(Vector3 vector, Vector3 to)
		{
			to.Normalize();
			return to * Vector3.DotProduct(vector, to);
		}

		public void SetTransform(Transform transform)
		{
			this.transform = transform;
		}
	}
}
