#ifndef ENGINEQ_RESOURCES_MESH_FACTORY_HPP
#define ENGINEQ_RESOURCES_MESH_FACTORY_HPP

#include <memory>

#include "Types.hpp"
#include <Graphics/Mesh.hpp>

namespace EngineQ
{
	namespace Resources
	{
		template<>
		struct ResourceFactory<Graphics::Mesh>
		{
			static std::unique_ptr<Graphics::Mesh> CreateResource(ResourceManager& resourceManager, const char* filename);
		};
	}
}

#endif // !ENGINEQ_RESOURCES_MESH_FACTORY_HPP