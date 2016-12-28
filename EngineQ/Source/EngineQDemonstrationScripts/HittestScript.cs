using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using EngineQ;
using EngineQ.Math;

namespace QScripts
{
	public class HittestScript : Script
	{
		private Transform cameraTransform;

		private Vector3 capsuleA;
		private Vector3 capsuleB;
		private float capsuleRadius;

		protected override void OnActivate()
		{
			cameraTransform = this.Entity.Scene.ActiveCamera.Entity.Transform;
			this.Entity.Transform.Scale = new Vector3(-0.5f);

			var capsule = this.Entity.Scene.FindEntity("Capsule");

			capsuleA = new Vector3(0.0f, 1.0f, 0.0f);
			capsuleB = new Vector3(0.0f, -1.0f, 0.0f);
			capsuleRadius = 1.0f * capsule.Transform.Scale.X;

			var capsuleMatrix = capsule.Transform.GlobalMatrix;

			capsuleA = Matrix4.TransformPosition(capsuleMatrix, capsuleA);
			capsuleB = Matrix4.TransformPosition(capsuleMatrix, capsuleB);

			Console.WriteLine($"Capsule: A = {capsuleA}, B = {capsuleB}, R = {capsuleRadius}");

			Input.RegisterMouseButtonEvent(Input.MouseButton.Left, HitAction);
		}

		private void HitAction(Input.MouseButton button, Input.KeyAction action)
		{
			if(action == Input.KeyAction.Press)
			{
				var screenSize = Application.ScreenSize;
				var pos = Input.MousePosition;

				Console.WriteLine(pos);

				var camera = this.Entity.Scene.ActiveCamera;

				var ray = camera.GetViewRay(new Vector2(2.0f * (float)pos.X / (float)screenSize.X - 1.0f, -2.0f * (float)pos.Y / (float)screenSize.Y + 1.0f));

				float dist = Utils.SegmentToRayDistance(new Segment(capsuleA, capsuleB), ray);

				Console.WriteLine($"Capsule pressed: {dist <= capsuleRadius}");

			//	Console.WriteLine($"Dir: {this.Transform.Rotation * Vector3.Forward}");
			//	Console.WriteLine($"Casted ray: {ray}");
			}
		}

		protected override void OnUpdate()
		{
		//	var rotation = this.Entity.Transform.Rotation = cameraTransform.Rotation;
		//	var direction = rotation * Vector3.Forward;
		//	var position = this.Entity.Transform.Position = cameraTransform.Position + direction * 1.5f;
			
		//	float dist = Utils.SegmentToRayDistance(new Segment(capsuleA, capsuleB), new Ray(position, direction));

		//	Console.WriteLine($"Hit: {dist <= capsuleRadius}");
		}
	}
}
