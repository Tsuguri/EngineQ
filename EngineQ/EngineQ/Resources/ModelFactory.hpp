#ifndef ENGINEQ_RESOURCES_MODEL_FACTORY_HPP
#define ENGINEQ_RESOURCES_MODEL_FACTORY_HPP

// Standard includes
#include <memory>

// This project
#include "Types.hpp"


namespace EngineQ
{
	namespace Resources
	{
		template<>
		struct ResourceFactory<Model>
		{
			static std::unique_ptr<Model> CreateResource(ResourceManager& resourceManager, const char* filename);
		};
	}
}

#endif // !ENGINEQ_RESOURCES_MODEL_FACTORY_HPP