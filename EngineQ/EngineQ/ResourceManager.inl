namespace EngineQ
{
	template<typename TResource>
	ResourceManager::Resource<TResource>::Resource(const std::string& path) :
		BaseResource{ path }
	{
	}

	template<typename TResource>
	void ResourceManager::Resource<TResource>::Update()
	{
		if (this->resource == nullptr)
			return;

		if (this->resource.unique())
		{
			this->garbageCount += 1;

			if (this->garbageCount >= GarbageUpdates)
				this->Unload();
		}
		else
		{
			this->garbageCount = 0;
		}
	}

	template<typename TResource>
	std::shared_ptr<TResource> ResourceManager::Resource<TResource>::GetResource()
	{
		if (this->resource == nullptr)
			this->Load();

		return this->resource;
	}

	template<typename TResource>
	void ResourceManager::Resource<TResource>::Unload()
	{
		std::cout << "Unloaded resource " << this->path << std::endl;

		this->resource = nullptr;
		this->garbageCount = 0;
	}

	template<typename TResource>
	void ResourceManager::Resource<TResource>::Load()
	{
		this->resource = std::make_shared<TResource>(this->path.c_str());
	}

	template<typename TResource>
	void ResourceManager::AddResource(int id, const std::string& path)
	{
		int resourceIndex = static_cast<int>(Resource<TResource>::GetType());
		auto& resourcesOfType = this->resources[resourceIndex];

		resourcesOfType.insert({ id, std::make_unique<Resource<TResource>>(path) });
	}

	template<typename TResource>
	void ResourceManager::RemoveResource(int id)
	{
		int resourceIndex = static_cast<int>(Resource<TResource>::GetType());
		auto& resourcesOfType = this->resources[resourceIndex];

		resourcesOfType.erase(id);
	}

	template<typename TResource>
	std::shared_ptr<TResource> ResourceManager::GetResource(int id)
	{
		int resourceIndex = static_cast<int>(Resource<TResource>::GetType());
		auto res = static_cast<Resource<TResource>*>(this->resources[resourceIndex].at(id).get());

		return res->GetResource();
	}
}