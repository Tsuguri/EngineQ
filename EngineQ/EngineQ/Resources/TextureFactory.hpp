#ifndef ENGINEQ_RESOURCES_TEXTURE_FACTORY_HPP
#define ENGINEQ_RESOURCES_TEXTURE_FACTORY_HPP

// Other projects
#include "EngineQRenderer/Graphics/Types.hpp"

// This project
#include "Types.hpp"
#include "ResourceFactory.hpp"


namespace EngineQ
{
	namespace Resources
	{
		template<>
		struct ResourceFactory<Graphics::Texture>
		{
			static std::unique_ptr<Graphics::Texture> CreateResource(ResourceManager& resourceManager, const char* filename);
		};
	}
}

#endif // !ENGINEQ_RESOURCES_TEXTURE_FACTORY_HPP
