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
			camera.Transform.Rotation = Quaternion.CreateLookAt(camera.Transform.Position, Vector3.Zero, Vector3.Up);
			var cameraMove = camera.AddComponent<CameraMoveClass>();
			cameraMove.MoveSpeed = 3.0f;

			camera.AddComponent<TesterScript>();


			// Skull
			var skull = scene.CreateEntity(true, "Skull");
			var skullRenderable = skull.AddComponent<Renderable>();
			skullRenderable.UseDeferredShader(resourceManager.GetResource<Shader>("SkullDeferred"));
			//	skullRenderable.Mesh = resourceManager.GetResource<Mesh>("Skull");
			skullRenderable.Mesh = resourceManager.GetResource<Mesh>("Horse");

			skullRenderable.DeferredShader.Material.DiffuseTexture = resourceManager.GetResource<Texture>("Numbers");
			skullRenderable.DeferredShader.Material.Specular = new Vector3f(5.0f);

			//	skull.Transform.Rotation = Quaternion.CreateRotationX(Utils.DegToRad(29.0f));
			//	skull.Transform.Position -= new Vector3(0.0f, 0.07f, 0.0f);


			// Floor
			var floor = scene.CreateEntity(true, "Floor");

			var floorRenderable = floor.AddComponent<Renderable>();
			floorRenderable.Mesh = resourceManager.GetResource<Mesh>("EngineQ/Quad");
			floorRenderable.UseDeferredShader(resourceManager.GetResource<Shader>("SkullDeferred"));

			floorRenderable.DeferredShader.Material.DiffuseTexture = resourceManager.GetResource<Texture>("Numbers");
			floorRenderable.DeferredShader.Material.Specular = new Vector3f(1.0f);

			floor.Transform.Rotation = Quaternion.CreateRotationX(Utils.DegToRad(90.0f));
			floor.Transform.Scale = new Vector3(7.0f);


			for (int i = 0; i < 4; ++i)
			{
				var floor2 = scene.CreateEntity(true, "Floor");

				var floor2Renderable = floor2.AddComponent<Renderable>();
				floor2Renderable.Mesh = resourceManager.GetResource<Mesh>("EngineQ/Quad");
				floor2Renderable.UseDeferredShader(resourceManager.GetResource<Shader>("SkullDeferred"));

				floor2Renderable.DeferredShader.Material.DiffuseTexture = resourceManager.GetResource<Texture>("Numbers");
				floor2Renderable.DeferredShader.Material.Specular = new Vector3f(1.0f);

				//	floor2.Transform.Rotation = Quaternion.CreateRotationX(Utils.DegToRad(90.0f));
				floor2.Transform.Scale = new Vector3(7.0f);

				switch (i)
				{
					case 0:
						floor2.Transform.Position = new Vector3(0.0f, 3.5f, 3.5f);
						break;

					case 1:
						floor2.Transform.Rotation = Quaternion.CreateRotationY(Utils.DegToRad(90));
						floor2.Transform.Position = new Vector3(3.5f, 3.5f, 0.0f);
						break;

					case 2:
						floor2.Transform.Rotation = Quaternion.CreateRotationY(Utils.DegToRad(-90));
						floor2.Transform.Position = new Vector3(-3.5f, 3.5f, 0.0f);
						break;

					case 3:
						floor2.Transform.Rotation = Quaternion.CreateRotationY(Utils.DegToRad(180));
						floor2.Transform.Position = new Vector3(0.0f, 3.5f, -3.5f);
						break;
				}
			}



			// Lights
			var lightsDeferredShader = resourceManager.GetResource<Shader>("LightDeferred");
			var lightsDeferredShader2 = resourceManager.GetResource<Shader>("LightDeferred");
			var lightsMesh = resourceManager.GetResource<Mesh>("EngineQ/Cube");
			var lightsMesh2 = resourceManager.GetResource<Mesh>("EngineQ/Cube");

			// Light1
			var light1 = scene.CreateEntity(true, "Light1");


			var light1light = light1.AddComponent<Light>();
			//light1light.Range = 15.0f;
			//light1light.TextureSize = new Vector2i(2048);

			//light1.AddComponent<LightController>();

			//var light1renderable = light1.AddComponent<Renderable>();
			//light1renderable.UseDeferredShader(lightsDeferredShader);
			//light1renderable.DeferredShader.Material.Diffuse = 5.0f * new Vector3f(1.0f, 0.0f, 0.0f);
			//light1renderable.Mesh = lightsMesh;
			//light1renderable.CastShadows = false;

			//var light1script = light1.AddComponent<LightRotateScript>();
			//light1script.RotationPoint = new Vector3(0.0f, 4.0f, 0.0f);
			//light1script.RotationAxis = new Vector3(0.0f, 1.0f, 0.0f);
			//light1script.RotationSpeed = 0.6f;
			//light1script.Radius = 4.0f;
			//light1script.InitialRotation = -2.0f;

			//light1.Transform.Scale = new Vector3(0.4f);

			/*
			//Light2
			var light2 = scene.CreateEntity(true, "Light2");

			var light2light = light2.AddComponent<Light>();

			var light2renderable = light2.AddComponent<Renderable>();
			light2renderable.UseDeferredShader(lightsDeferredShader2);
			light2renderable.DeferredShader.Material.Diffuse = 5.0f * new Vector3f(0.5f, 0.5f, 0.0f);
			light2renderable.Mesh = lightsMesh2;
			light2renderable.CastShadows = false;

			var light2script = light2.AddComponent<LightRotateScript>();
			light2script.RotationPoint = new Vector3(0.0f, 1.8f, 0.0f);
			light2script.RotationAxis = new Vector3(0.0f, 1.0f, 0.0f);
			light2script.RotationSpeed = 0.4f;
			light2script.Radius = 4.0f;
			light2script.InitialRotation = 0.3f;

			light2.Transform.Scale = new Vector3(0.4f);
			*/

			/*
			var capsule = scene.CreateEntity(true, "Capsule");
			var capsuleRenderable = capsule.AddComponent<Renderable>();
			capsuleRenderable.UseDeferredShader(resourceManager.GetResource<Shader>("SkullDeferred"));
			capsuleRenderable.Mesh = resourceManager.GetResource<Mesh>("Capsule");
			capsuleRenderable.DeferredShader.Material.DiffuseTexture = resourceManager.GetResource<Texture>("Numbers");

			capsule.Transform.Scale = new Vector3(0.5f);
			capsule.Transform.Position = new Vector3(-2.0f, 1.0f, 0.0f);
			capsule.Transform.Rotation = Quaternion.CreateFromEuler(0.35f, 2.54f, -1.3f);

			var arrow = scene.CreateEntity(true, "Arrow");
			var arrowRenderable = arrow.AddComponent<Renderable>();
			arrowRenderable.UseDeferredShader(resourceManager.GetResource<Shader>("SkullDeferred"));
			arrowRenderable.Mesh = resourceManager.GetResource<Mesh>("Arrow");
			arrowRenderable.DeferredShader.Material.DiffuseTexture = resourceManager.GetResource<Texture>("Numbers");
			arrow.AddComponent<HittestScript>();
			*/

			var arrows = scene.CreateEntity(true, "Arrows");
			arrows.AddComponent<ArrowsController>();

			arrows.Transform.Position = new Vector3(1.6f, 0.4f, -2.0f);


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
			resourceManager.RegisterResource<Mesh>("Horse", "./Meshes/Horse.qres");
			resourceManager.RegisterResource<Texture>("Numbers", "./Textures/Numbers.qres");

			resourceManager.RegisterResource<Shader>("SkullDeferred", "./Shaders/Deferred/DeferredSimpleTexture.qres");
			resourceManager.RegisterResource<Shader>("LightDeferred", "./Shaders/Deferred/DeferredSimpleColor.qres");
			resourceManager.RegisterResource<Shader>("DeferredLighting", "./Shaders/Deferred/DeferredLightning.qres");

			resourceManager.RegisterResource<Shader>("BloomExtraction", "./Shaders/Bloom/BrightExtract.qres");
			resourceManager.RegisterResource<Shader>("BloomVerticalBlur", "./Shaders/Bloom/BlurVertical.qres");
			resourceManager.RegisterResource<Shader>("BloomHorizontalBlur", "./Shaders/Bloom/BlurHorizontal.qres");
			resourceManager.RegisterResource<Shader>("Combine", "./Shaders/Combine.qres");
			resourceManager.RegisterResource<Shader>("LightDepthRender", "./Shaders/Shadows/DepthRender.qres");
			resourceManager.RegisterResource<Shader>("DeferredLightingShadows", "./Shaders/Deferred/DeferredLightningShadows.qres");

			resourceManager.RegisterResource<Shader>("SSAO", "./Shaders/SSAO/SSAO.qres");
			resourceManager.RegisterResource<Shader>("SSAOBlur", "./Shaders/SSAO/SSAOBlur.qres");

			resourceManager.RegisterResource<Shader>("Debug/ShadowmapDrawer", "./Shaders/Debug/ShadowmapDrawer.qres");

			//	resourceManager.RegisterResource<Mesh>("Capsule", "./Meshes/Capsule.qres");

			resourceManager.RegisterResource<Mesh>("Arrow", "./Meshes/Arrow.qres");
			resourceManager.RegisterResource<Shader>("ArrowsDeferred", "./Shaders/Deferred/DeferredSimpleColor.qres");

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
