#ifndef ENGINEQ_RESOURCES_MODEL_HPP
#define ENGINEQ_RESOURCES_MODEL_HPP
#include <memory>

#include "../Graphics/Mesh.hpp"
namespace EngineQ
{
	namespace Resources
	{
		class Model
		{
		public:
			class Mesh
			{
			private:
				std::vector <VertexPNC> vertices;
				std::vector <GLuint> indices;

			public:
				std::shared_ptr<Graphics::Mesh> GetMesh();
			};

			bool loadedToGPU=false;

			std::shared_ptr<Mesh> meshesRoot = nullptr;

		private:
			void LoadToGPU();
		};
	}
}

#endif