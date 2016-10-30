#ifndef ENGINEQ_RESOURCES_RESOURCE_FACTORY_HPP
#define ENGINEQ_RESOURCES_RESOURCE_FACTORY_HPP

#include <memory>
#include <stdexcept>

#include "Types.hpp"

namespace EngineQ
{
	namespace Resources
	{
		class ResourceLoadingException : public std::runtime_error
		{
		public:
			using std::runtime_error::runtime_error;
		};

		template<typename TResourceType>
		struct ResourceFactory
		{
			static std::unique_ptr<ResourceFactory> CreateResource(ResourceManager& resourceManager, const char* filename);
		};
	}
}

#endif // !ENGINEQ_RESOURCES_RESOURCE_FACTORY_HPP
