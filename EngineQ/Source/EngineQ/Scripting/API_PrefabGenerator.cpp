#include "API_PrefabGenerator.hpp"

// This project
#include "ScriptEngine.hpp"
#include "EngineQ/Engine.hpp"
#include "EngineQ/Resources/PrefabGenerator.hpp"


namespace EngineQ
{
	namespace Scripting
	{
		void API_PrefabGenerator::API_GenerateCapsule(Math::Real height, Math::Real radius, MonoObject*& mesh)
		{
			auto& resourceManager = Engine::Get().GetResourceManager();
			auto& scriptEngine = resourceManager.GetScriptEngine();

			Resources::PrefabGenerator generator{ resourceManager };

			auto resource = generator.GenerateCapsule(height, radius);
			void* controlBlock = resource.GetControlBlock();

			mesh = scriptEngine.CreateUnhandledObject(scriptEngine.GetClass(ScriptEngine::Class::Mesh), controlBlock);
		}

		void API_PrefabGenerator::API_GenerateCube(Math::Real side, MonoObject*& mesh)
		{
			auto& resourceManager = Engine::Get().GetResourceManager();
			auto& scriptEngine = resourceManager.GetScriptEngine();

			Resources::PrefabGenerator generator{ resourceManager };

			auto resource = generator.GenerateCube(side);
			void* controlBlock = resource.GetControlBlock();

			mesh = scriptEngine.CreateUnhandledObject(scriptEngine.GetClass(ScriptEngine::Class::Mesh), controlBlock);
		}

		void API_PrefabGenerator::API_GenerateQuad(Math::Real side, MonoObject*& mesh)
		{
			auto& resourceManager = Engine::Get().GetResourceManager();
			auto& scriptEngine = resourceManager.GetScriptEngine();

			Resources::PrefabGenerator generator{ resourceManager };

			auto resource = generator.GenerateQuad(side);
			void* controlBlock = resource.GetControlBlock();

			mesh = scriptEngine.CreateUnhandledObject(scriptEngine.GetClass(ScriptEngine::Class::Mesh), controlBlock);
		}

		void API_PrefabGenerator::API_GenerateNoiseTexture(int width, int height, MonoObject*& texture)
		{
			auto& resourceManager = Engine::Get().GetResourceManager();
			auto& scriptEngine = resourceManager.GetScriptEngine();

			Resources::PrefabGenerator generator{ resourceManager };

			auto resource = generator.GenerateNoiseTexture(width, height);
			void* controlBlock = resource.GetControlBlock();

			texture = scriptEngine.CreateUnhandledObject(scriptEngine.GetClass(ScriptEngine::Class::Texture), controlBlock);
		}

		void API_PrefabGenerator::API_Register(ScriptEngine& scriptEngine)
		{
			scriptEngine.API_Register("EngineQ.PrefabGenerator::API_GenerateCapsule", API_GenerateCapsule);
			scriptEngine.API_Register("EngineQ.PrefabGenerator::API_GenerateCube", API_GenerateCube);
			scriptEngine.API_Register("EngineQ.PrefabGenerator::API_GenerateQuad", API_GenerateQuad);
			scriptEngine.API_Register("EngineQ.PrefabGenerator::API_GenerateNoiseTexture", API_GenerateNoiseTexture);
		}
	}
}
