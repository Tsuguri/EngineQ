#include "Mesh.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		GLuint Mesh::GetIndicesCount() const
		{
			return indicesCount;
		}

		GLuint Mesh::GetVao() const
		{
			return vao;
		}

		Mesh::~Mesh()
		{
			glDeleteBuffers(VboSize, vbo);
			glDeleteVertexArrays(1, &vao);
		}
	}
}