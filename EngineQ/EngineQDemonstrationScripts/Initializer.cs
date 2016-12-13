using System;

using EngineQ;
using EngineQ.Math;

namespace QScripts
{
	static class Initializer
	{
		public static void OnInitialize(Scene scene)
		{
			Console.WriteLine("==== INITIALIZING ====");

			Console.WriteLine("Registering resources");
			RegisterResources();

			Console.WriteLine("Prepairing scene");
			PrepareScene(scene);
		}

		private static void PrepareScene(Scene scene)
		{
			var ent1 = scene.CreateEntity(true, "Camera");
			var ent2 = scene.CreateEntity(true, "Skull1");
			var ent3 = scene.CreateEntity(true, "Skull2");
			var ent4 = scene.CreateEntity(true, "Cube");

			var renderable1 = ent2.AddComponent<Renderable>();
			var renderable2 = ent3.AddComponent<Renderable>();
			var renderable3 = ent4.AddComponent<Renderable>();
			var camera = ent1.AddComponent<Camera>();

			var rm = ResourceManager.Instance;

			var cubeMesh = rm.GetResource<Mesh>("EngineQ/Cube");
			var skullMesh = rm.GetResource<Mesh>("Skull");

			var texture = rm.GetResource<Texture>("Numbers");

			var shader = rm.GetResource<Shader>("1");
			var deferredShader = rm.GetResource<Shader>("9");
			var deferredShaderCustom = rm.GetResource<Shader>("9");

			renderable1.Mesh = skullMesh;
			renderable1.Entity.Transform.Scale = new Vector3(0.1f);
			renderable1.UseForwardShader(shader);
			renderable1.UseDeferredShader(deferredShader);
			renderable1.DeferredShader.Material.DiffuseTexture = texture;

			renderable2.Mesh = skullMesh;
			renderable2.Entity.Transform.Scale = new Vector3(0.1f);
			renderable2.UseForwardShader(shader);
			renderable2.UseDeferredShader(deferredShader);
			renderable2.DeferredShader.Material.DiffuseTexture = texture;

			renderable3.Mesh = cubeMesh;
			renderable3.UseForwardShader(shader);
			renderable3.UseDeferredShader(deferredShader);
			renderable3.DeferredShader.Material.DiffuseTexture = texture;


			ent1.AddComponent<CameraMoveClass>();
			ent2.AddComponent<RotateTest>();

			var lightEntity = scene.CreateEntity(true, "Light0");
			lightEntity.AddComponent<Light>();

			scene.ActiveCamera = camera;

			ent1.Transform.Position = new Vector3(0.0f, 0.0f, -2.0f);
			ent2.Transform.Position = new Vector3(0.0f, 0.0f, 0.0f);
			ent3.Transform.Position = new Vector3(1.0f, 0.0f, 0.0f);
			ent4.Transform.Position = new Vector3(2.0f, 0.0f, 0.0f);
		}

		private static void RegisterResources()
		{
			var resourceManager = ResourceManager.Instance;

			resourceManager.RegisterResource<Shader>("1", "./Shaders/Basic.shd");
			resourceManager.RegisterResource<Shader>("2", "./Shaders/Custom.shd");
			resourceManager.RegisterResource<Shader>("3", "./Shaders/Quad.shd");
			resourceManager.RegisterResource<Shader>("4", "./Shaders/Bloom/Blur.shd");
			resourceManager.RegisterResource<Shader>("5", "./Shaders/Bloom/BlurV.shd");
			resourceManager.RegisterResource<Shader>("6", "./Shaders/Bloom/BrightExtract.shd");
			resourceManager.RegisterResource<Shader>("7", "./Shaders/Bloom/Combine.shd");
			resourceManager.RegisterResource<Shader>("8", "./Shaders/Deferred/DeferredLightning.shd");
			resourceManager.RegisterResource<Shader>("9", "./Shaders/Deferred/DeferredGeometry.shd");
			resourceManager.RegisterResource<Shader>("TestDeferred1", "./Shaders/Deferred/DeferredGeometry2.shd");
			resourceManager.RegisterResource<Shader>("TestDeferred2", "./Shaders/Deferred/DeferredGeometry3.shd");
			resourceManager.RegisterResource<Shader>("10", "./Shaders/Deferred/DeferredCustom.shd");
			resourceManager.RegisterResource<Shader>("11", "./Shaders/Shadows/DepthRender.shd");


			resourceManager.RegisterResource<Texture>("Numbers", "./Textures/Numbers.qres");

			resourceManager.RegisterResource<Mesh>("Skull", "./Meshes/Skull.qres");
		}
	}
}
