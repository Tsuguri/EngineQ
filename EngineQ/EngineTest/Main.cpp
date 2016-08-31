#include <iostream>

#include "Math/Vector4.hpp"
#include "Math/Matrix4.hpp"

#include "Scene.hpp"
#include "Entity.hpp"
#include "Scripting/ScriptEngine.hpp"
#include "Light.hpp"

#include "Graphics/Shader.hpp"

#include "GLFW/glfw3.h"

void Init()
{

	std::cout << "Creating  EngineQ" << std::endl;


	glfwInit();

	// Set all the required options for GLFW 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	// Creating glfw window. 
	GLFWwindow* window = glfwCreateWindow(800, 600, "Dupa", nullptr, nullptr);//glfwGetPrimaryMonitor() 

	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);

	//glfwSwapInterval(0); 
	// Set the required callback functions

	//Uncomment below if want to register call on window resizing 
	//glfwSetFramebufferSizeCallback(window, WindowResized); 


	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions 
	glewExperimental = GL_TRUE;

	// Initialize GLEW to setup the OpenGL Function pointers 
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		glfwSetWindowShouldClose(window, GL_TRUE);
		window = nullptr;
		return;
	}

	// Define the viewport dimensions 
	glViewport(0, 0, 800, 600);
}

using namespace EngineQ;
using namespace ::EngineQ::Graphics;

#include "Serialization/XMLFormatter.hpp"

int main(int argc, char** argv)
{
	// Shaders test
	Init();

	//{
	//	VertexShader vs = VertexShader::CreateFromFile("Shaders/Test/Simple.vert");

	//	Shader shader{ VertexShader::CreateFromFile("Shaders/Test/Simple.vert"), FragmentShader::CreateFromFile("Shaders/Test/Simple.frag") };
	//}


	// Scripting test
	::EngineQ::Math::Vector4 vec{ 1, 2, 3, 4 };
	EngineQ::Math::Matrix4 mat = EngineQ::Math::Matrix4::GetIdentity();

	std::cout << "Vector4: " << vec.ToString() << std::endl;
	std::cout << "Matrix4: " << mat.ToString() << std::endl;

	std::cout << "mat * vec = " << (mat * vec).ToString() << std::endl;

	std::string monoPath = "./";
	if (argc > 1)
	{
		monoPath = argv[1];
	}

	std::string engineAssemblyPath = "./";
	if (argc > 2)
	{
		engineAssemblyPath = argv[2];
	}

	std::string scriptsAssembliesPath = "./Scripts/";
	if (argc > 3)
	{
		scriptsAssembliesPath = argv[3];
	}
	std::cout << argv[0] << std::endl << engineAssemblyPath << std::endl << monoPath << std::endl;


	EngineQ::Scripting::ScriptEngine se{ argv[0], (engineAssemblyPath + "EngineQ.dll").c_str(), (monoPath + "libraries").c_str(), (monoPath + "config").c_str() };

	se.LoadAssembly((scriptsAssembliesPath + "ScriptTest.dll").c_str());


	EngineQ::Serialization::SerializationEngine::Register<EngineQ::Scene>("Scene");
	EngineQ::Serialization::SerializationEngine::Register<EngineQ::Entity>("Entity");
	EngineQ::Serialization::SerializationEngine::Register<EngineQ::Transform>("Transform");
	EngineQ::Serialization::SerializationEngine::Register<EngineQ::Camera>("Camera");
	EngineQ::Serialization::SerializationEngine::Register<EngineQ::Script>("Script");
	EngineQ::Serialization::SerializationEngine::Register<EngineQ::Light>("Light");

//#define SERIALIZE
#ifdef SERIALIZE
	EngineQ::Scene scene{ se };

	EngineQ::Entity* entity1 = scene.CreateEntity();
	EngineQ::Entity* entity2 = scene.CreateEntity();

	entity1->GetTransform().SetParent(&entity2->GetTransform());

	EngineQ::Scripting::ScriptClass scriptClass = se.GetScriptClass("ScriptTest", "ScriptTest", "MyScript");

	entity1->AddComponent<EngineQ::Light>();
	entity1->AddScript(scriptClass);

	scene.Update();
	scene.Update();

	

	EngineQ::Serialization::Serializer serialzier;

	auto serialized = serialzier.Serialize(scene);

	EngineQ::Serialization::XMLFormatter formatter;

	formatter.Save("Scene.xml", *serialized);
#else

	EngineQ::Serialization::XMLFormatter formatter;
	auto serialized = formatter.Load("Scene.xml");

	EngineQ::Serialization::Deserializer deserializer{ serialized };
	deserializer.AddStorage("scriptEngine", &se);

	EngineQ::Scene* scene2 = deserializer.Deserialize<EngineQ::Scene>();

	scene2->Update();
	scene2->Update();

#endif

	getchar();
	return 0;
}
