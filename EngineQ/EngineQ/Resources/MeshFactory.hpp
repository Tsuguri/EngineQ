#ifndef ENGINEQ_RESOURCES_MESH_FACTORY_HPP
#define ENGINEQ_RESOURCES_MESH_FACTORY_HPP

// Standard includes
#include <memory>

// Other projects
#include "EngineQRenderer/Graphics/Mesh.hpp"

// This project
#include "Types.hpp"


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