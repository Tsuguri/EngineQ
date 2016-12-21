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
			var resourceManager = ResourceManager.Instance;


			// Camera
			var camera = scene.CreateEntity(true, "Camera");
			
			var cameraComponent = camera.AddComponent<Camera>();
			scene.ActiveCamera = cameraComponent;
			cameraComponent.FieldOfView = 70.0f;

			camera.Transform.Position = new Vector3(4, 2.0f, -6.0f);
			camera.Transform.Rotation = Quaternion.CreateLookAt(camera.Transform.Position, Vector3.Zero);
			var cameraMove = camera.AddComponent<CameraMoveClass>();
			cameraMove.MoveSpeed = 3.0f;

			camera.AddComponent<TesterScript>();


			// Skull
			var skull = scene.CreateEntity(true, "Skull");
			var skullRenderable = skull.AddComponent<Renderable>();
			skullRenderable.UseDeferredShader(resourceManager.GetResource<Shader>("SkullDeferred"));
			skullRenderable.Mesh = resourceManager.GetResource<Mesh>("Skull");

			skullRenderable.DeferredShader.Material.DiffuseTexture = resourceManager.GetResource<Texture>("Numbers");
			skullRenderable.DeferredShader.Material.Specular = new Vector3f(1.0f);

			skull.Transform.Rotation = Quaternion.CreateRotationX(Utils.DegToRad(29.0f));
			skull.Transform.Position -= new Vector3(0.0f, 0.07f, 0.0f);
			

			// Floor
			var floor = scene.CreateEntity(true, "Floor");

			var floorRenderable = floor.AddComponent<Renderable>();
			floorRenderable.Mesh = resourceManager.GetResource<Mesh>("EngineQ/Quad");
			floorRenderable.UseDeferredShader(resourceManager.GetResource<Shader>("SkullDeferred"));
			floorRenderable.DeferredShader.Material.DiffuseTexture = resourceManager.GetResource<Texture>("Numbers");

			floor.Transform.Rotation = Quaternion.CreateRotationX(Utils.DegToRad(90.0f));
			floor.Transform.Scale = new Vector3(7.0f);


			// Lights
			var lightsDeferredShader = resourceManager.GetResource<Shader>("LightDeferred");
			var lightsDeferredShader2 = resourceManager.GetResource<Shader>("LightDeferred");
			var lightsMesh = resourceManager.GetResource<Mesh>("EngineQ/Cube");
			var lightsMesh2 = resourceManager.GetResource<Mesh>("EngineQ/Cube");

			// Light1
			var light1 = scene.CreateEntity(true, "Light1");
			
			var light1light = light1.AddComponent<Light>();

			var light1renderable = light1.AddComponent<Renderable>();
			light1renderable.UseDeferredShader(lightsDeferredShader);
			light1renderable.DeferredShader.Material.Diffuse = 5.0f * new Vector3f(1.0f, 0.0f, 0.0f);
			light1renderable.Mesh = lightsMesh;
			light1renderable.CastShadows = false;

			var light1script = light1.AddComponent<LightRotateScript>();
			light1script.RotationPoint = new Vector3(0.0f, 2.0f, 0.0f);
			light1script.RotationAxis = new Vector3(0.0f, 1.0f, 0.0f);
			light1script.RotationSpeed = 0.6f;
			light1script.Radius = 2.0f;
			light1script.InitialRotation = -2.0f;

			light1.Transform.Scale = new Vector3(0.4f);


			//Light2
		   var light2 = scene.CreateEntity(true, "Light2");

			var light2light = light2.AddComponent<Light>();

			var light2renderable = light2.AddComponent<Renderable>();
			light2renderable.UseDeferredShader(lightsDeferredShader2);
			light2renderable.DeferredShader.Material.Diffuse = 5.0f * new Vector3f(0.5f, 0.5f, 0.0f);
			light2renderable.Mesh = lightsMesh2;
			light2renderable.CastShadows = false;

			var light2script = light2.AddComponent<LightRotateScript>();
			light2script.RotationPoint = new Vector3(0.0f, 1.3f, 0.0f);
			light2script.RotationAxis = new Vector3(0.0f, 1.0f, 0.0f);
			light2script.RotationSpeed = 0.4f;
			light2script.Radius = 3.0f;
			light2script.InitialRotation = 0.3f;

			light2.Transform.Scale = new Vector3(0.4f);

			/*
			var ent1 = scene.CreateEntity(true, "Camera");
			var ent2 = scene.CreateEntity(true, "Skull1");
			var ent3 = scene.CreateEntity(true, "Skull2");
			var ent4 = scene.CreateEntity(true, "Cube");
			var ent5 = scene.CreateEntity(true, "Cube2");

			var renderable1 = ent2.AddComponent<Renderable>();
			var renderable2 = ent3.AddComponent<Renderable>();
			var renderable3 = ent4.AddComponent<Renderable>();
			var renderable4 = ent5.AddComponent<Renderable>();

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

			renderable4.Mesh = cubeMesh;
			renderable4.UseForwardShader(shader);
			renderable4.UseDeferredShader(deferredShader);
			renderable4.DeferredShader.Material.DiffuseTexture = texture;

			ent2.AddComponent<RotateTest>();

			ent2.Transform.Position = new Vector3(0.0f, 0.0f, 0.0f);
			ent3.Transform.Position = new Vector3(1.0f, 0.0f, 0.0f);
			ent4.Transform.Position = new Vector3(2.0f, 0.0f, 0.0f);
            */
		}

		private static void RegisterResources()
		{
			var resourceManager = ResourceManager.Instance;

			resourceManager.RegisterResource<Mesh>("Skull", "./Meshes/Skull.qres");
			resourceManager.RegisterResource<Texture>("Numbers", "./Textures/Numbers.qres");

			resourceManager.RegisterResource<Shader>("SkullDeferred", "./Shaders/Deferred/DeferredSimpleTexture.qres");
			resourceManager.RegisterResource<Shader>("LightDeferred", "./Shaders/Deferred/DeferredSimpleColor.qres");
			resourceManager.RegisterResource<Shader>("DeferredLighting", "./Shaders/Deferred/DeferredLightning.qres");

			resourceManager.RegisterResource<Shader>("BloomExtraction", "./Shaders/Bloom/BrightExtract.qres");
			resourceManager.RegisterResource<Shader>("BloomVerticalBlur", "./Shaders/Bloom/BlurVertical.qres");
			resourceManager.RegisterResource<Shader>("BloomHorizontalBlur", "./Shaders/Bloom/BlurHorizontal.qres");
			resourceManager.RegisterResource<Shader>("Combine", "./Shaders/Combine.qres");
			resourceManager.RegisterResource<Shader>("LightDepthRender","./Shaders/Shadows/DepthRender.qres");
			resourceManager.RegisterResource<Shader>("DeferredLightingShadows", "./Shaders/Deferred/DeferredLightningShadows.qres");

			/*
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

			resourceManager.RegisterResource<Texture>("Numbers", "./Textures/Numbers.qres");

			resourceManager.RegisterResource<Mesh>("Skull", "./Meshes/Skull.qres");
	        */
		}
	}
}
