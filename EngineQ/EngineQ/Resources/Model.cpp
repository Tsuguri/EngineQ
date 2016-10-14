#include "Model.hpp"

namespace EngineQ
{
	namespace Resources
	{
		std::shared_ptr<Graphics::Mesh> Model::Mesh::GetMesh()
		{
			throw std::logic_error{ "Not implemented" };
		}

		void Model::LoadToGPU()
		{

		}
	}
}