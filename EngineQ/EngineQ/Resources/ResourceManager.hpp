#ifndef ENGINEQ_RESOURCES_RESOURCE_MANAGER_HPP
#define ENGINEQ_RESOURCES_RESOURCE_MANAGER_HPP

#include <tuple>
#include <unordered_map>

#include "Types.hpp"
#include "../Graphics/Types.hpp"

#include "../Utilities/Metaprogramming.hpp"
#include "../Scripting/ScriptEngine.hpp"

#include "ShaderFactory.hpp"
#include "TextureFactory.hpp"
#include "ModelFactory.hpp"

#include "Resource.hpp"
#include "../Graphics/Shader.hpp"

#include "../Objects/Object.hpp"

// TMP
#include <iostream>

#include <typeindex>
#include <functional>




namespace EngineQ
{
	namespace Resources
	{
		class ResourceManagerException : std::logic_error
		{
		public:
			using std::logic_error::logic_error;
		};

		class ResourceNotFoundException : std::logic_error
		{
		public:
			using std::logic_error::logic_error;
		};

		class ResourceManager : public Object
		{
		private:
			struct ResourceData
			{
				std::function<void(ResourceManager&, ResourceData&)> constructor;
				std::function<void(ResourceManager&, ResourceData&)> destructor;

				std::unique_ptr<BaseResource> resource;

				int generation = 0;
			};

		private:
			using MapKeyValue = std::pair<std::pair<std::type_index, std::string>, ResourceData>;
			
			std::map<MapKeyValue::first_type, MapKeyValue::second_type> resourceMap;

			static constexpr int MaxFrameCount = 600;
			static constexpr int MaxGeneration = 3;
			int frameCount = 0;

			std::vector<ResourceData*> activeResources;
			std::vector<ResourceData*> newActiveResources;
			std::vector<ResourceData*> oldActiveResources;

			void UpdateResources()
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

		public:
			ResourceManager(Scripting::ScriptEngine& scriptEngine) :
				Object{ scriptEngine, scriptEngine.GetClass(Scripting::ScriptEngine::Class::ResourceManager) }
			{
			}

			template<typename TType>
			void RegisterResource(const std::string& resourceId, const char* path)
			{
				RegisterResource<TType>(resourceId, [path](ResourceManager&)
				{
					return ResourceFactory<TType>::CreateResource(path);
				});
			}

			template<typename TType>
			void RegisterResource(const std::string& resourceId, std::function<std::unique_ptr<TType>(ResourceManager&)> factory)
			{
				std::type_index index = typeid(TType);

				ResourceData resourceData;

				resourceData.constructor = [factory, /*TMP*/ resourceId](ResourceManager& resourceManager, ResourceData& resourceData)
				{
					auto controlBlock = static_cast<const Resource<TType>&>(*resourceData.resource).GetControlBlock();

					controlBlock->data = factory(resourceManager);

					resourceManager.newActiveResources.push_back(&resourceData);

					std::cout << "RM: Created resource " << resourceId << std::endl;
				};

				resourceData.destructor = [ /*TMP*/ resourceId](ResourceManager& resourceManager, ResourceData& resourceData)
				{
					auto controlBlock = static_cast<const Resource<TType>&>(*resourceData.resource).GetControlBlock();

					controlBlock->data = nullptr;

					resourceManager.oldActiveResources.push_back(&resourceData);

					std::cout << "RM: Destructed resource " << resourceId << std::endl;

				};

				resourceData.resource = std::make_unique<Resource<TType>>(std::unique_ptr<TType>(nullptr));

				auto insertPair = this->resourceMap.insert(MapKeyValue{ MapKeyValue::first_type{ index, resourceId }, MapKeyValue::second_type{ std::move(resourceData) } });
			}

			template<typename TType>
			Resource<TType> GetResource(const std::string& resourceId)
			{
				std::type_index index = typeid(TType);

				auto resourceDataIt = this->resourceMap.find({ index, resourceId });
				if (resourceDataIt == this->resourceMap.end())
					throw ResourceNotFoundException{ "Resource " + resourceId + " not found" };

				auto& resourceData = resourceDataIt->second;
				auto& resource = static_cast<Resource<TType>&>(*resourceData.resource);

				if (resource.GetControlBlock()->data == nullptr)
					resourceData.constructor(*this, resourceData);
			
				return resource;
			}

			void Update()
			{
				this->frameCount += 1;
				if (this->frameCount >= MaxFrameCount)
				{
					this->UpdateResources();
					this->frameCount = 0;
				}
			}
		};
	}
}

#endif // !ENGINEQ_RESOURCES_RESOURCE_MANAGER_HPP
