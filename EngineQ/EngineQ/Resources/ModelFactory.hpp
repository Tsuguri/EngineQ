#ifndef ENGINEQ_RESOURCES_MODEL_FACTORY_HPP
#define ENGINEQ_RESOURCES_MODEL_FACTORY_HPP

#include <memory>

#include "Types.hpp"

namespace EngineQ
{
	namespace Resources
	{
		template<>
		struct ResourceFactory<Model>
		{
			static std::unique_ptr<Model> CreateResource(const char* filename);
		};
	}
}

#endif // !ENGINEQ_RESOURCES_MODEL_FACTORY_HPP