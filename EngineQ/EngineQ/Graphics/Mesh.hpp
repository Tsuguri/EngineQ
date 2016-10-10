#ifndef ENGINEQ_GRAPHICS_MESH_HPP
#define ENGINEQ_GRAPHICS_MESH_HPP

#include <vector>

#include "../Libraries/GL/glew.h"

#include "../Utilities/Immovable.hpp"
#include "../Vertex.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		class Mesh : public Utilities::Uncopyable
		{
		private:
			GLuint count = 0;
			GLuint vao = 0;
			GLuint vbo[3] = { 0,0,0 };
		public:


			GLuint Count() const;
			GLuint GetVao() const;
			Mesh(const std::vector <VertexPNC>& vertices, const std::vector <GLuint>& indices);
			~Mesh();
		};
	}
}
#endif
