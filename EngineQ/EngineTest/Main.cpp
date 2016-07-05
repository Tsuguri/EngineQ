#include <iostream>

#include "Math/Vector4.hpp"
#include "Math/Matrix4.hpp"

#include "Scene.hpp"
#include "Entity.hpp"
#include "Scripting/ScriptEngine.hpp"
#include "Light.hpp"

int main(int argc, char** argv)
{
	EngineQ::Math::Vector4 vec{ 1, 2, 3, 4 };
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
	
	EngineQ::Scripting::ScriptEngine se{ argv[0], (engineAssemblyPath + "EngineQ.dll").c_str(), (monoPath + "libraries").c_str(), (monoPath + "config").c_str() };

	EngineQ::Scene scene{ se };

	EngineQ::Entity* entity1 = scene.CreateEntity();
	EngineQ::Entity* entity2 = scene.CreateEntity();

	entity1->GetTransform().SetParent(&entity2->GetTransform());

	se.LoadAssembly((scriptsAssembliesPath + "ScriptTest.dll").c_str());
	EngineQ::Scripting::ScriptClass scriptClass = se.GetScriptClass("ScriptTest", "ScriptTest", "MyScript");

	entity1->AddComponent<EngineQ::Light>();
	entity1->AddScript(scriptClass);
	
	scene.Update();
	scene.Update();

	return 0;
}
