#ifndef ENGINEQ_RESOURCES_TEXTURE_FACTORY_HPP
#define ENGINEQ_RESOURCES_TEXTURE_FACTORY_HPP

#include "ResourceFactory.hpp"

#include "../Graphics/Types.hpp"

namespace EngineQ
{
	namespace Resources
	{
		template<>
		struct ResourceFactory<Graphics::Texture>
		{
			static std::unique_ptr<Graphics::Texture> CreateResource(const char* filename);
		};
	}
}

#endif // !ENGINEQ_RESOURCES_TEXTURE_FACTORY_HPP
