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

			var singleUpdateRunner = camera.AddComponent<SingleUpdateRunner>();
			singleUpdateRunner.RunEvent += () =>
			{
				Console.WriteLine();
				Console.WriteLine("============================================");
				Console.WriteLine("===               Controls               ===");

				Console.WriteLine();
				Console.WriteLine("Movement:");
				Console.WriteLine("\tW - Move Forward");
				Console.WriteLine("\tS - Move Backward");
				Console.WriteLine("\tA - Move Right");
				Console.WriteLine("\tD - Move Left");
				Console.WriteLine();
				Console.WriteLine("\tSpace   - Move Up");
				Console.WriteLine("\tL Ctrl  - Move Down");
				Console.WriteLine("\tL Shift - Move Faster");
				Console.WriteLine();
				Console.WriteLine("\tRight Mouse - Move camera");

				Console.WriteLine();
				Console.WriteLine("Options:");
				Console.WriteLine("\tKeypad 6 - Next option");
				Console.WriteLine("\tKeypad 4 - Previous option");
				Console.WriteLine("\tKeypad 5 - Show current option");
				Console.WriteLine("\tKeypad 8 - Increase option");
				Console.WriteLine("\tKeypad 2 - Decrease option");

				Console.WriteLine();
				Console.WriteLine("Misc:");
				Console.WriteLine("\tLeft Mouse - Select items");
				Console.WriteLine();

				Console.WriteLine("============================================");
				Console.WriteLine();
			};

			var cameraComponent = camera.AddComponent<Camera>();
			scene.ActiveCamera = cameraComponent;
			cameraComponent.FieldOfView = 70.0f;

			camera.Transform.Position = new Vector3(2.2f, 3.7f, -2.7f);
			camera.Transform.Rotation = Quaternion.CreateLookAt(camera.Transform.Position, new Vector3(0.0f, 2.5f, 0.0f), Vector3.Up);
			var cameraMove = camera.AddComponent<CameraMoveClass>();
			cameraMove.MoveSpeed = 3.0f;

			var optionChanger = camera.AddComponent<OptionChanger>();
			var colliderPicker = camera.AddComponent<ColliderPicker>();
			colliderPicker.Initialize(cameraComponent);

			Input.RegisterKeyEvent(Input.Key.T, (Input.Key key, Input.KeyAction action) => { Console.WriteLine(camera.Transform.Position); });
			
			// Horse
			var horse = scene.CreateEntity(true, "Horse");

			horse.Transform.Position = new Vector3(0);
			horse.Transform.Scale = new Vector3(0.8f);

			var horseRenderable = horse.AddComponent<Renderable>();
			horseRenderable.UseDeferredShader(resourceManager.GetResource<Shader>("DeferredSimpleTexture"));
			horseRenderable.Mesh = resourceManager.GetResource<Mesh>("Horse");

			horseRenderable.DeferredShader.Material.DiffuseTexture = resourceManager.GetResource<Texture>("Marble");
			horseRenderable.DeferredShader.Material.Specular = new Vector3f(0.5f);

			var horseCollider = horse.AddComponent<CapsuleCollider>();
			
			// Floor
			Renderable[] floorRenderables = new Renderable[5];
			for (int i = 0; i < 5; ++i)
			{
				const float QuadSize = 7.0f;

				var floor = scene.CreateEntity(true, $"Floor{i}");

				var floorRenderable = floor.AddComponent<Renderable>();
				floorRenderable.Mesh = PrefabGenerator.GenerateQuad(QuadSize);
				floorRenderable.UseDeferredShader(resourceManager.GetResource<Shader>("DeferredSimpleTexture"));

				floorRenderable.DeferredShader.Material.DiffuseTexture = resourceManager.GetResource<Texture>("Marble");
				floorRenderable.DeferredShader.Material.Specular = new Vector3f(1.0f);

				floorRenderables[i] = floorRenderable;
				
				// Square walls
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
			light1light.TextureSize = new Vector2i(4096);
			light1light.AmbientColor = new Vector3(0.1f);
			light1light.DiffuseColor = new Vector3(2.0f);
			light1light.SpecularColor = new Vector3(1.0f);



			light1.AddComponent<LightController>();
		
			var light1renderable = light1.AddComponent<Renderable>();
			light1renderable.UseDeferredShader(lightsDeferredShader);
			light1renderable.DeferredShader.Material.Diffuse = 15.0f * new Vector3f(1.0f);
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


			var light2renderable = light2.AddComponent<Renderable>();
			light2renderable.UseDeferredShader(lightsDeferredShader);
			light2renderable.DeferredShader.Material.Diffuse = 15.0f * new Vector3f(1.0f);
			light2renderable.Mesh = lightsMesh;
			light2renderable.CastShadows = false;
			
			var light2script = light2.AddComponent<LightRotateScript>();
			light2script.RotationPoint = new Vector3(0.0f, 3.0f, 0.0f);
			light2script.RotationAxis = new Vector3(0.0f, 1.0f, 0.0f);
			light2script.RotationSpeed = 0.3f;
			light2script.Radius = 3.0f;
			light2script.InitialRotation = -4.0f;
			light2script.Update();
			
			
			optionChanger.AddOption(new SimpleFloatOption("Horse specular", 2f, 0.0f, 100.0f, 0.05f, (float value) => { horseRenderable.DeferredShader.Material.Specular = new Vector3f(value); }));
			optionChanger.AddOption(new SimpleFloatOption("Floor specular", 1.0f, 0.0f, 100.0f, 0.05f, (float value) => { foreach(var renderable in floorRenderables) renderable.DeferredShader.Material.Specular = new Vector3f(value); }));

			optionChanger.AddOption(new SimpleFloatOption("Light1 light diffuse", light1light.DiffuseColor.X, 0.0f, 100.0f, 0.1f, (float value) => { light1light.DiffuseColor = new Vector3(value); }));
			optionChanger.AddOption(new SimpleFloatOption("Light2 light diffuse", light2light.DiffuseColor.X, 0.0f, 100.0f, 0.1f, (float value) => { light2light.DiffuseColor = new Vector3(value); }));

			optionChanger.AddOption(new SimpleFloatOption("Light1 cube diffuse", light1renderable.DeferredShader.Material.Diffuse.X, 0.0f, 100.0f, 0.1f, (float value) => { light1renderable.DeferredShader.Material.Diffuse = new Vector3f(value); }));
			optionChanger.AddOption(new SimpleFloatOption("Light2 cube diffuse", light2renderable.DeferredShader.Material.Diffuse.X, 0.0f, 100.0f, 0.1f, (float value) => { light2renderable.DeferredShader.Material.Diffuse = new Vector3f(value); }));


			optionChanger.AddOption(new SimpleBoolOption("Lights movement", true, (bool value) => { light1script.Enabled = value; light2script.Enabled = value; }));

			optionChanger.AddOption(new SimpleBoolOption("Light1 Enable", true, (bool value) => { light1.Enabled = value; }));
			optionChanger.AddOption(new SimpleBoolOption("Light2 Enable", true, (bool value) => { light2.Enabled = value; }));

			optionChanger.AddOption(new SimpleBoolOption("Light1 Cast shadows", true, (bool value) => { light1light.CastShadows = value; }));
			optionChanger.AddOption(new SimpleBoolOption("Light2 Cast shadows", true, (bool value) => { light2light.CastShadows = value; }));

			optionChanger.AddOption(new SimpleBoolOption("Profiler print info", false, (bool value) => { Profiler.PrintInfo = value; }));

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
			resourceManager.RegisterResource<Texture>("Marble", "./Textures/Marble.qres");
			resourceManager.RegisterResource<Texture>("Metal", "./Textures/Metal.qres");

			resourceManager.RegisterResource<Shader>("DeferredSimpleTexture", "./Shaders/Deferred/DeferredSimpleTexture.qres");
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

			resourceManager.RegisterResource<Shader>("SSR", "./Shaders/SSR/SSR.qres");

			resourceManager.RegisterResource<Shader>("Debug/ShadowmapDrawer", "./Shaders/Debug/ShadowmapDrawer.qres");
			
			resourceManager.RegisterResource<Mesh>("Arrow", "./Meshes/Arrow.qres");
			resourceManager.RegisterResource<Shader>("ArrowsDeferred", "./Shaders/Deferred/DeferredSimpleColor.qres");
		}
	}
}
