#ifndef ENGINEQ_GRAPHICS_MESH_HPP
#define ENGINEQ_GRAPHICS_MESH_HPP

#include <vector>

#include "../Libraries/GL/glew.h"

#include "../Utilities/Uncopyable.hpp"
#include "../Vertex.hpp"

namespace EngineQ
{
	class Mesh : public Utilities::Uncopyable
	{
	private:
		GLuint count;
		GLuint vao=0;
		GLuint vbo[3]={0,0,0};
	public:
		
		
		GLuint Count();
		GLuint GetVao();
		Mesh(const std::vector <VertexPNC>& vertices,const std::vector <GLuint>& indices);
		~Mesh();
	};
}
#endif
