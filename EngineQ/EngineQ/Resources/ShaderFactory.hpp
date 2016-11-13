#ifndef ENGINEQ_RESOURCES_SHADER_FACTORY_HPP
#define ENGINEQ_RESOURCES_SHADER_FACTORY_HPP

#include "ResourceFactory.hpp"

#include "Types.hpp"
#include <Graphics/Types.hpp>

namespace EngineQ
{
	namespace Resources
	{
		template<>
		struct ResourceFactory<Graphics::Shader>
		{
			static std::unique_ptr<Graphics::Shader> CreateResource(ResourceManager& resourceManager, const char* filename);
		};
	}
}

#endif // !ENGINEQ_RESOURCES_SHADER_FACTORY_HPP
