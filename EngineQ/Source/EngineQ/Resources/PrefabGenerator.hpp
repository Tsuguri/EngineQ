#ifndef ENGINEQ_RESOURCES_PREFAB_GENERATOR_HPP
#define ENGINEQ_RESOURCES_PREFAB_GENERATOR_HPP

// Other projects
#include "EngineQCommon/Math/Types.hpp"
#include "EngineQRenderer/Graphics/Types.hpp"

// This project
#include "Types.hpp"


namespace EngineQ
{
	namespace Resources
	{
		class PrefabGenerator
		{
		private:
			ResourceManager& resourceManager;

		public:
			PrefabGenerator(ResourceManager& resourceManager);

			Resource<Graphics::Mesh> GenerateCapsule(Math::Real height, Math::Real radius);
		};
	}
}

#endif // !ENGINEQ_RESOURCES_PREFAB_GENERATOR_HPP
