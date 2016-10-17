#include "ResourceManager.hpp"

namespace EngineQ
{
	namespace Resources
	{
		ResourceManager::ResourceManager(Scripting::ScriptEngine& scriptEngine) :
			scriptEngine{ scriptEngine }
		{

		}

		void ResourceManager::Update()
		{
			this->UpdateResources(this->resources);
		}
	}
}