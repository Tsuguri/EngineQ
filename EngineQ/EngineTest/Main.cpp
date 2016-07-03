#include <iostream>

#include "Math/Vector4.hpp"
#include "Math/Matrix4.hpp"

#include "Entity.hpp"
#include "Scripting/ScriptEngine.hpp"

int main(int argc, char** argv)
{
	EngineQ::Math::Vector4 vec{ 1, 2, 3, 4 };
	EngineQ::Math::Matrix4 mat = EngineQ::Math::Matrix4::GetIdentity();

	std::cout << "Vector4: " << vec.ToString() << std::endl;
	std::cout << "Matrix4: " << mat.ToString() << std::endl;

	std::cout << "mat * vec = " << (mat * vec).ToString() << std::endl;

	std::string assembliesPath = "./";
	if (argc > 1)
	{
		assembliesPath = argv[1];
	}

	std::string monoPath = "./";
	if (argc > 2)
	{
		monoPath = argv[2];
	}

	EngineQ::Scripting::ScriptEngine se{ argv[0], (assembliesPath + "EngineQ.dll").c_str(), (monoPath + "libraries").c_str(), (monoPath + "config").c_str() };

	EngineQ::Entity entity1{ se };
	EngineQ::Entity entity2{ se };

	entity1.GetTransform().SetParent(&entity2.GetTransform());

	se.LoadAssembly((assembliesPath + "ScriptTest.dll").c_str());
	EngineQ::Scripting::ScriptClass scriptClass = se.GetScriptClass("ScriptTest", "ScriptTest", "MyScript");

	entity1.AddScript(scriptClass);
	entity1.Update();

	return 0;
}
