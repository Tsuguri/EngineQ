#ifndef ENGINEQ_RESOURCES_RESOURCE_MANAGER_HPP
#define ENGINEQ_RESOURCES_RESOURCE_MANAGER_HPP

// Standard includes
#include <tuple>
#include <algorithm>
#include <unordered_map>
#include <typeindex>
#include <functional>

// Other projects
#include "EngineQCommon/Utilities/Metaprogramming.hpp"
#include "EngineQCommon/Resources/Resource.hpp"
#include "EngineQRenderer/Graphics/Types.hpp"
#include "EngineQRenderer/Graphics/Shader.hpp"

// This project
#include "Types.hpp"
#include "Model.hpp"
#include "ShaderFactory.hpp"
#include "TextureFactory.hpp"
#include "ModelFactory.hpp"
#include "MeshFactory.hpp"
#include "EngineQ/Scripting/ScriptEngine.hpp"
#include "EngineQ/Objects/Object.hpp"
#include "EngineQ/Logger.hpp"


namespace EngineQ
{
	namespace Resources
	{
		class ResourceManagerException : public std::logic_error
		{
		public:
			using std::logic_error::logic_error;
		};

		class ResourceNotFoundException : public std::logic_error
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

			void UpdateResources();

		public:
			ResourceManager(Scripting::ScriptEngine& scriptEngine);

			template<typename TType>
			bool IsResourceRegistered(const std::string& resourceId);

			template<typename TType>
			void RegisterResource(const std::string& resourceId, const char* path);

			template<typename TType>
			void RegisterResource(const std::string& resourceId, std::function<std::unique_ptr<TType>(ResourceManager&)> factory);

			template<typename TType>
			Resource<TType> TryGetResource(const std::string& resourceId);

			template<typename TType>
			Resource<TType> GetResource(const std::string& resourceId);
			
			void Update();
		};
	}
}

#include "ResourceManager.inl"

#endif // !ENGINEQ_RESOURCES_RESOURCE_MANAGER_HPP
