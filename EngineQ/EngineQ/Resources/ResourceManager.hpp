#ifndef ENGINEQ_RESOURCES_RESOURCE_MANAGER_HPP
#define ENGINEQ_RESOURCES_RESOURCE_MANAGER_HPP

#include <tuple>
#include <unordered_map>

#include "Types.hpp"
#include "../Graphics/Types.hpp"

#include "../Utilities/Metaprogramming.hpp"
#include "../Scripting/ScriptEngine.hpp"

#include "ShaderFactory.hpp"

#include "Resource.hpp"
#include "../Graphics/Shader.hpp"

#include "../Objects/Object.hpp"

// TMP
#include <iostream>

namespace EngineQ
{
	namespace Resources
	{
		class ResourceManagerException : std::logic_error
		{
		public:
			using std::logic_error::logic_error;
		};

		class ResourceManager : public Object
		{
		private:
			template<typename TResourceType>
			struct ResourceData
			{
				std::string path;
				Resource<TResourceType> resource;

				ResourceData(const char* path) :
					path{ path }
				{
				}
			};

			using ResourceId = std::string;

			template<typename... TTypes>
			struct TypesHelper
			{
				using ResourcesType = std::tuple<std::unordered_map<ResourceId, ResourceData<TTypes>>...>;

				template<typename TType>
				inline static constexpr std::size_t IndexOf()
				{
					return Meta::TypeIndex<TType, TTypes...>::value;
				}
			};

			using Types = TypesHelper<Graphics::Shader>;

			static constexpr int SkipFrames = 1000;

			Types::ResourcesType resources;
			int frameCount = 0;

			template<std::size_t TIt = 0, typename... TTypes>
			inline typename std::enable_if<(TIt == sizeof...(TTypes)), void>::type UpdateResources(std::tuple<TTypes...>& tuple)
			{ 
			}

			template<std::size_t TIt = 0, typename... TTypes>
			inline typename std::enable_if<(TIt < sizeof...(TTypes)), void>::type UpdateResources(std::tuple<TTypes...>& tuple)
			{
				this->UpdateResource(std::get<TIt>(tuple));
				this->UpdateResources<TIt + 1, TTypes...>(tuple);
			}

			template<typename TType>
			void UpdateResource(std::unordered_map<ResourceId, ResourceData<TType>>& resourceMap)
			{
				// TODO
				// List of active resources. If N times is unused during garbage colletion then it is removed and moved to inactive resources list
				for (auto& resourceDataPair : resourceMap)
				{
					if (resourceDataPair.second.resource.GetReferenceCount() == 1)
					{
						resourceDataPair.second.resource = nullptr;
						std::cout << "Disposed " << resourceDataPair.first << ": " << resourceDataPair.second.path << std::endl;
					}
				}
			}

		public:
			ResourceManager(Scripting::ScriptEngine& scriptEngine);

			template<typename TResourceType>
			void RegisterResource(const ResourceId& id, const char* filename)
			{
				auto& resourceMap = std::get<Types::IndexOf<TResourceType>()>(resources);

				auto inserted = resourceMap.insert({ id, {filename} });
				if (!inserted.second)
					throw ResourceManagerException{ "Resource already registered" };
			}

			template<typename TResourceType>
			Resource<TResourceType> GetResource(const ResourceId& resourceId)
			{
				auto& resourceMap = std::get<Types::IndexOf<TResourceType>()>(resources);

				auto& resource = resourceMap.at(resourceId);

				if (resource.resource == nullptr)
				{
					resource.resource = Resource<TResourceType>{ this->scriptEngine, ResourceFactory<TResourceType>::GetScriptClass(this->scriptEngine), ResourceFactory<TResourceType>::CreateResource(resource.path.c_str()) };
					std::cout << "Loaded " << resourceId << ": " << resource.path << std::endl;
 				}

				return resource.resource;
			}

			void Update();
		};
	}
}

#endif // !ENGINEQ_RESOURCES_RESOURCE_MANAGER_HPP
