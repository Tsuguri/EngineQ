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
			for (auto it = this->activeResources.begin(); it != this->activeResources.end();)
			{
				auto& resourceData = **it;

				if (resourceData.resource->GetAllReferenceCount() == 1)
				{
					resourceData.generation += 1;

					if (resourceData.generation >= MaxGeneration)
					{
						resourceData.destructor(*this, resourceData);
						it = this->activeResources.erase(it);
					}
					else
					{
						++it;
					}
				}
				else
				{
					++it;
				}
			}

			for (auto it = this->unnamedResources.begin(); it != this->unnamedResources.end();)
			{
				auto& resourceData = *it;

				if (resourceData.resource->GetAllReferenceCount() == 1)
				{
					resourceData.generation += 1;
					
					if (resourceData.generation >= MaxGeneration)
					{
						it = this->unnamedResources.erase(it);
					}
					else
					{
						++it;
					}
				}
				else
				{
					++it;
				}
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