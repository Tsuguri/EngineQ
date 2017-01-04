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

			//	camera.Transform.Position = new Vector3(4, 2.0f, -6.0f);
		//	camera.Transform.Rotation = Quaternion.CreateLookAt(camera.Transform.Position, Vector3.Zero, Vector3.Up);
			camera.Transform.Position = new Vector3(0.0f, 1.5f, -3.0f);
			camera.Transform.Rotation = Quaternion.CreateLookAt(camera.Transform.Position, new Vector3(0.0f, 1.5f, 0.0f), Vector3.Up);
			var cameraMove = camera.AddComponent<CameraMoveClass>();
			cameraMove.MoveSpeed = 3.0f;

			var optionChanger = camera.AddComponent<OptionChanger>();
			var colliderPicker = camera.AddComponent<ColliderPicker>();
			colliderPicker.Initialize(cameraComponent);


			// Skull
			var skull = scene.CreateEntity(true, "Skull");
			skull.Transform.Position = new Vector3(0);
			var skullRenderable = skull.AddComponent<Renderable>();
			skullRenderable.UseDeferredShader(resourceManager.GetResource<Shader>("SkullDeferred"));
			//skullRenderable.Mesh = resourceManager.GetResource<Mesh>("Skull");
			skullRenderable.Mesh = resourceManager.GetResource<Mesh>("Horse");

			skullRenderable.DeferredShader.Material.DiffuseTexture = resourceManager.GetResource<Texture>("Numbers");
			skullRenderable.DeferredShader.Material.Specular = new Vector3f(15.0f);

			var skullCollider = skull.AddComponent<CapsuleCollider>();

		//	skullCollider.Height = 2.0f;
		//	skullCollider.Position = new Vector3(0.0f, 2.0f, 0.0f);
		//	skullCollider.Rotation = Quaternion.CreateFromEuler(1.3f, 0.1f, -2.2f);
		//
		//	skull.Transform.Rotation = Quaternion.CreateRotationX(Utils.DegToRad(29.0f));
		//	skull.Transform.Position -= new Vector3(0.0f, 0.07f, 0.0f);
		//	skull.Transform.Scale = new Vector3(0.2f, 1.2f, 2.0f);

			// Floor
			for (int i = 0; i < 5; ++i)
			{
				var floor = scene.CreateEntity(true, $"Floor{i}");

				var floorRenderable = floor.AddComponent<Renderable>();
				floorRenderable.Mesh = PrefabGenerator.GenerateQuad(7.0f);
				floorRenderable.UseDeferredShader(resourceManager.GetResource<Shader>("SkullDeferred"));

				floorRenderable.DeferredShader.Material.DiffuseTexture = resourceManager.GetResource<Texture>("Numbers");
				floorRenderable.DeferredShader.Material.Specular = new Vector3f(1.0f);
				
				switch (i)
				{
					case 0:
						floor.Transform.Rotation = Quaternion.CreateRotationX(Utils.DegToRad(90.0f));
						break;

					case 1:
						floor.Transform.Position = new Vector3(0.0f, 3.5f, 3.5f);
						break;

					case 2:
						floor.Transform.Rotation = Quaternion.CreateRotationY(Utils.DegToRad(90));
						floor.Transform.Position = new Vector3(3.5f, 3.5f, 0.0f);
						break;

					case 3:
						floor.Transform.Rotation = Quaternion.CreateRotationY(Utils.DegToRad(-90));
						floor.Transform.Position = new Vector3(-3.5f, 3.5f, 0.0f);
						break;

					case 4:
						floor.Transform.Rotation = Quaternion.CreateRotationY(Utils.DegToRad(180));
						floor.Transform.Position = new Vector3(0.0f, 3.5f, -3.5f);
						break;
				}
			}



			// Lights
			var lightsDeferredShader = resourceManager.GetResource<Shader>("LightDeferred");
			var lightsMesh = PrefabGenerator.GenerateCube(0.4f);


			// Light1
			var light1 = scene.CreateEntity(true, "Light1");
			
			var light1light = light1.AddComponent<Light>();
			light1light.Type = LightType.Sun;
			light1light.Range = 15.0f;
			light1light.TextureSize = new Vector2i(2048);
			light1light.AmbientColor = new Vector3(0.1f);
			light1light.DiffuseColor = new Vector3(2.0f);
			light1light.SpecularColor = new Vector3(1.0f);

			optionChanger.AddOption(new SimpleFloatOption("Light1 diffuse", light1light.DiffuseColor.X, 0.0f, 100.0f, 0.1f, (float value) => { light1light.DiffuseColor = new Vector3(value); }));


			light1.AddComponent<LightController>();
		
			var light1renderable = light1.AddComponent<Renderable>();
			light1renderable.UseDeferredShader(lightsDeferredShader);
			light1renderable.DeferredShader.Material.Diffuse = 5.0f * new Vector3f(1.0f, 0.0f, 0.0f);
			light1renderable.Mesh = lightsMesh;
			light1renderable.CastShadows = false;
		
			var light1script = light1.AddComponent<LightRotateScript>();
			light1script.RotationPoint = new Vector3(0.0f, 4.0f, 0.0f);
			light1script.RotationAxis = new Vector3(0.0f, 1.0f, 0.0f);
			light1script.RotationSpeed = 0.6f;
			light1script.Radius = 4.0f;
			light1script.InitialRotation = -2.0f;
			light1script.Update();
			

			//Light2
			var light2 = scene.CreateEntity(true, "Light2");
			var light2light = light2.AddComponent<Light>();
			light2light.Type = LightType.Point;
			light2light.TextureSize = new Vector2i(2048);
			light2light.AmbientColor = new Vector3(0.1f);
			light2light.DiffuseColor = new Vector3(0.4f);

			optionChanger.AddOption(new SimpleFloatOption("Light2 diffuse", light2light.DiffuseColor.X, 0.0f, 100.0f, 0.1f, (float value) => { light2light.DiffuseColor = new Vector3(value); }));


			var light2renderable = light2.AddComponent<Renderable>();
			light2renderable.UseDeferredShader(lightsDeferredShader);
			light2renderable.DeferredShader.Material.Diffuse = 5.0f * new Vector3f(1.0f, 0.0f, 0.0f);
			light2renderable.Mesh = lightsMesh;
			light2renderable.CastShadows = false;
			
			var light2script = light2.AddComponent<LightRotateScript>();
			light2script.RotationPoint = new Vector3(0.0f, 3.0f, 0.0f);
			light2script.RotationAxis = new Vector3(0.0f, 1.0f, 0.0f);
			light2script.RotationSpeed = 0.3f;
			light2script.Radius = 3.0f;
			light2script.InitialRotation = -4.0f;
			light2script.Update();
			
			optionChanger.AddOption(new SimpleBoolOption("Lights movement", false, (bool value) => { light1script.Enabled = value; light2script.Enabled = value; }));
			


			var arrows = scene.CreateEntity(true, "Arrows");
			arrows.AddComponent<ArrowsController>();

			arrows.Transform.Position = new Vector3(1.6f, 0.4f, -2.0f);
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
			resourceManager.RegisterResource<Shader>("LightDepthRenderPoint", "./Shaders/Shadows/DepthRenderPoint.qres");
			resourceManager.RegisterResource<Shader>("DeferredLightingShadows", "./Shaders/Deferred/DeferredLightningShadows.qres");

			resourceManager.RegisterResource<Shader>("SSAO", "./Shaders/SSAO/SSAO.qres");
			resourceManager.RegisterResource<Shader>("SSAOBlur", "./Shaders/SSAO/SSAOBlur.qres");

			resourceManager.RegisterResource<Shader>("Debug/ShadowmapDrawer", "./Shaders/Debug/ShadowmapDrawer.qres");
			
			resourceManager.RegisterResource<Mesh>("Arrow", "./Meshes/Arrow.qres");
			resourceManager.RegisterResource<Shader>("ArrowsDeferred", "./Shaders/Deferred/DeferredSimpleColor.qres");
		}
	}
}
