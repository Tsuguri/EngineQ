using System;

using EngineQ;
using EngineQ.Math;

namespace ScriptTest
{
    public class MyScript : Script
    {
		public override void Update()
		{
			Console.WriteLine("=============MY SCRIPT UPDATE =============");

			if(this.Entity.Transform.Parent != null)
			{
				Console.WriteLine("Has parent");
			}
			else
			{
				Console.WriteLine("Does not have parent");
			}

			Entity other = this.Entity.Scene.CreateEntity();
			//	other.AddComponent<Transform>();
			other.AddComponent<Light>();
			other.AddComponent<MyScript>();

			for (int i = 0; i < other.ComponentsCount; ++i)
				Console.WriteLine("\t" + other.GetComponent(i).ToString());

			this.Entity.Transform.Position = new Vector3(1, 2, 3);
			this.Entity.Transform.Rotation = Quaternion.CreateFromEuler(4.1f, 2.0f, 1.7f);
			this.Entity.Transform.Scale = new Vector3(1, 0.5f, 0.3f);

			Matrix4 matrix = this.Entity.Transform.GlobalMatrix;

			Console.WriteLine("Matrix: " + matrix.ToString());
		}
	}
}
