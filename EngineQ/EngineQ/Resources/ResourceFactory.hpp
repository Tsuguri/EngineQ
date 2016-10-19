#ifndef ENGINEQ_RESOURCES_RESOURCE_FACTORY_HPP
#define ENGINEQ_RESOURCES_RESOURCE_FACTORY_HPP

#include <memory>
#include <stdexcept>

namespace EngineQ
{
	namespace Resources
	{
		class ResourceLoadingException : std::runtime_error
		{
		public:
			using std::runtime_error::runtime_error;
		};

		template<typename TResourceType>
		struct ResourceFactory
		{
			static std::unique_ptr<ResourceFactory> CreateResource(const char* filename);
		};
	}
}

#endif // !ENGINEQ_RESOURCES_RESOURCE_FACTORY_HPP
