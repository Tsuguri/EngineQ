#ifndef ENGINEQ_RESOURCES_CUBETEXTURE_FACTORY_HPP
#define ENGINEQ_RESOURCES_CUBETEXTURE_FACTORY_HPP

#include "ResourceFactory.hpp"

#include "Types.hpp"
#include <Graphics/Types.hpp>

namespace EngineQ
{
	namespace Resources
	{
		template<>
		struct ResourceFactory<Graphics::CubeTexture>
		{
			static std::unique_ptr<Graphics::CubeTexture> CreateResource(ResourceManager& resourceManager, const char* filename);
		};
	}
}

#endif // !ENGINEQ_RESOURCES_CUBETEXTURE_FACTORY_HPP
