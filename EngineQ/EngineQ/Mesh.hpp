#ifndef MESHHPP
#define MESHHPP

#include "Math/Vector3.hpp"
#include "Vertex.hpp"
#include <vector>
#include <GL/glew.h>

namespace EngineQ
{
	class Mesh
	{
	private:
		GLuint vao=0;
		GLuint vbo[3]={0,0,0};
	public:
		Mesh(const std::vector <VertexPNC>& vertices,const std::vector <GLuint>& indices);
		~Mesh();
	};
}
#endif
