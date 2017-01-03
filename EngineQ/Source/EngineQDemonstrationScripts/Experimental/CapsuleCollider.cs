using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using EngineQ;
using EngineQ.Math;

namespace QScripts
{
	public class CapsuleCollider : Collider
	{
		private float radius = 0.5f;
		public float Radius
		{
			get
			{
				return this.radius;
			}
			set
			{
				if (this.radius == value)
					return;

				this.radius = value;
				this.capsuleRenderable.Mesh = PrefabGenerator.GenerateCapsule(this.Height, this.Radius);
			}
		}

		private float height = 1.0f;
		public float Height
		{
			get
			{
				return this.height;
			}
			set
			{
				if (this.height == value)
					return;

				this.height = value;
				this.capsuleRenderable.Mesh = PrefabGenerator.GenerateCapsule(this.Height, this.Radius);
			}
		}

		private Quaternion rotation = Quaternion.Identity;
		public Quaternion Rotation
		{
			get
			{
				return this.rotation;
			}
			set
			{
				this.rotation = value;
				this.capsuleRenderable.Entity.Transform.Rotation = this.Rotation;
			}
		}

		private Vector3 position = Vector3.Zero;
		public Vector3 Position
		{
			get
			{
				return this.position;
			}
			set
			{
				this.position = value;
				this.capsuleRenderable.Entity.Transform.Position = this.Position;
			}
		}

		private Renderable capsuleRenderable;

		protected override void OnCreate()
		{
			var resourceManager = ResourceManager.Instance;

			var capsuleEntity = this.Entity.Scene.CreateEntity();

			capsuleEntity.Transform.Parent = this.Entity.Transform;
			capsuleEntity.Transform.Rotation = this.Rotation;
			capsuleEntity.Transform.Position = this.Position;
			
			capsuleRenderable = capsuleEntity.AddComponent<Renderable>(false);
			capsuleRenderable.UseDeferredShader(resourceManager.GetResource<Shader>("SkullDeferred"));
			capsuleRenderable.Mesh = PrefabGenerator.GenerateCapsule(this.Height, this.Radius);
		}

		public override bool RayCast(Ray ray, out float distance)
		{
			// Transform ray to model space
			var matrix = this.Entity.Transform.GlobalMatrixInverse;

			ray.Origin = Matrix4.TransformPosition(matrix, ray.Origin) - this.Position;
			ray.Direction = Matrix4.TransformVector(matrix, ray.Direction).Normalized;

			// Transform capsule
			var height = this.Height * 0.5f;
			var point1 = this.Rotation * new Vector3(0.0f, height, 0.0f);
			var point2 = this.Rotation * new Vector3(0.0f, -height, 0.0f);
			
			var capsule = new Capsule(point1, point2, this.Radius);
			
			return Utils.RayCapsuleIntersection(capsule, ray, out distance);
		}
	}
}
