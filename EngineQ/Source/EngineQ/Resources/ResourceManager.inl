namespace EngineQ
{
	namespace Resources
	{
		template<typename TType>
		bool ResourceManager::IsResourceRegistered(const std::string & resourceId)
		{
			return this->resourceMap.find({ typeid(TType), resourceId }) != this->resourceMap.end();
		}

		template<typename TType>
		void ResourceManager::RegisterResource(const std::string & resourceId, const char * path)
		{
			std::string pathString = path;
			RegisterResource<TType>(resourceId, [pathString](ResourceManager& resourceManager)
			{
				return ResourceFactory<TType>::CreateResource(resourceManager, pathString.c_str());
			});
		}

		template<typename TType>
		void ResourceManager::RegisterResource(const std::string & resourceId, std::function<std::unique_ptr<TType>(ResourceManager&)> factory)
		{
			std::type_index index = typeid(TType);

			ResourceData resourceData;

			resourceData.constructor = [factory, /*TMP*/ resourceId](ResourceManager& resourceManager, ResourceData& resourceData)
			{
				auto controlBlock = static_cast<const Resource<TType>&>(*resourceData.resource).GetControlBlock();

				controlBlock->data = factory(resourceManager);

				resourceManager.newActiveResources.push_back(&resourceData);

				Logger::LogMessage("RM: Created resource ", resourceId, "\n");
			};

			resourceData.destructor = [ /*TMP*/ resourceId](ResourceManager& resourceManager, ResourceData& resourceData)
			{
				auto controlBlock = static_cast<const Resource<TType>&>(*resourceData.resource).GetControlBlock();

				controlBlock->data = nullptr;

				resourceManager.oldActiveResources.push_back(&resourceData);

				Logger::LogMessage("RM: Destructed resource ", resourceId, "\n");
			};

			resourceData.resource = std::make_unique<Resource<TType>>(std::unique_ptr<TType>(nullptr));

			auto insertPair = this->resourceMap.insert(MapKeyValue{ MapKeyValue::first_type{ index, resourceId }, MapKeyValue::second_type{ std::move(resourceData) } });
			if (!insertPair.second)
				throw ResourceManagerException{ "Resource " + resourceId + " already registered" };
		}

		template<typename TType>
		Resource<TType> ResourceManager::TryGetResource(const std::string & resourceId)
		{
			std::type_index index = typeid(TType);

			auto resourceDataIt = this->resourceMap.find({ index, resourceId });
			if (resourceDataIt == this->resourceMap.end())
				return nullptr;

			auto& resourceData = resourceDataIt->second;
			auto& resource = static_cast<Resource<TType>&>(*resourceData.resource);

			if (resource.GetControlBlock()->data == nullptr)
				resourceData.constructor(*this, resourceData);

			return resource;
		}

		template<typename TType>
		Resource<TType> ResourceManager::GetResource(const std::string & resourceId)
		{
			Resource<TType> resource = this->TryGetResource<TType>(resourceId);
			if (resource == nullptr)
				throw ResourceNotFoundException{ "Resource " + resourceId + " not found" };

			return resource;
		}
	}
}