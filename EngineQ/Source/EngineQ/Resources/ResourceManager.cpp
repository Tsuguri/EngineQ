#include "ResourceManager.hpp"


namespace EngineQ
{
	namespace Resources
	{
		ResourceManager::ResourceManager(Scripting::ScriptEngine& scriptEngine) :
			Object{ scriptEngine, scriptEngine.GetClass(Scripting::ScriptEngine::Class::ResourceManager) }
		{
			// TMP
			this->scriptEngine.InvokeConstructor(this->GetManagedObject());
		}
				
		void ResourceManager::UpdateResources()
		{
			if (this->newActiveResources.size() > 0)
			{
				this->activeResources.insert(this->activeResources.end(), newActiveResources.begin(), newActiveResources.end());
				this->newActiveResources.clear();
			}

			for (auto resourceData : this->activeResources)
			{
				if (resourceData->resource->GetNativeReferenceCount() == 1 && resourceData->resource->GetAllReferenceCount() == 1)
				{
					resourceData->generation += 1;

					if (resourceData->generation == MaxGeneration)
						resourceData->destructor(*this, *resourceData);
				}
			}

			if (this->oldActiveResources.size() > 0)
			{
				for (auto oldResource : this->oldActiveResources)
					this->activeResources.erase(std::remove(this->activeResources.begin(), this->activeResources.end(), oldResource), this->activeResources.end());
				this->oldActiveResources.clear();
			}
		}
		
		void ResourceManager::Update()
		{
			this->frameCount += 1;
			if (this->frameCount >= MaxFrameCount)
			{
				this->UpdateResources();
				this->frameCount = 0;
			}
		}
	}
}