#include "ResourceManager.hpp"

namespace EngineQ
{
	namespace Resources
	{
		ResourceManager::ResourceManager(Scripting::ScriptEngine& scriptEngine) :
			Object{ scriptEngine, scriptEngine.GetResourceManagerClass() }
		{
		}

		void ResourceManager::Update()
		{
			this->frameCount += 1;
			if (this->frameCount >= SkipFrames)
			{
				this->UpdateResources(this->resources);
				this->frameCount = 0;
			}
		}
	}
}