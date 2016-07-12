#ifndef MESHHPP
#define MESHHPP

#include "Math/Vector3.hpp"
#include "Vertex.hpp"
#include <vector>
#include <GL/glew.h>
#include "Utilities/Uncopyable.hpp"

namespace EngineQ
{
	class Mesh : public Utilities::Uncopyable
	{
	private:
		GLuint count;
	public:
		
		GLuint vao=0;
		GLuint vbo[3]={0,0,0};
		
		GLuint Count();

		Mesh(const std::vector <VertexPNC>& vertices,const std::vector <GLuint>& indices);
		~Mesh();
	};
}
#endif
