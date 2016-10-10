#include "Mesh.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		GLuint Mesh::Count()
		{
			return count;
		}

		GLuint Mesh::GetVao()
		{
			return vao;
		}

		Mesh::Mesh(const std::vector<VertexPNC>& vertices, const std::vector<GLuint>& indices)
		{

			//Generating vertex array and buffers
			glGenVertexArrays(1, &vao);
			glGenBuffers(3, &vbo[0]);

			glBindVertexArray(vao);



			//sending data of vertices
			glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexPNC), vertices.data(), GL_STATIC_DRAW);


			//setting components pointers
			GLuint positionAtt = 0;
			GLuint normalAtt = 3;
			GLuint colorAtt = 2;

			glVertexAttribPointer(positionAtt, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPNC), reinterpret_cast<const GLvoid*>(VertexPNC::positionOffset));
			glEnableVertexAttribArray(positionAtt);

			glVertexAttribPointer(normalAtt, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPNC), reinterpret_cast<const GLvoid*>(VertexPNC::normalOffset));
			glEnableVertexAttribArray(normalAtt);

			glVertexAttribPointer(colorAtt, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPNC), reinterpret_cast<const GLvoid*>(VertexPNC::colorOffset));
			glEnableVertexAttribArray(colorAtt);




			//sending indices data
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[2]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, NULL);
			count = indices.size();
		}

		Mesh::~Mesh()
		{
			glDeleteBuffers(3, vbo);
			glDeleteVertexArrays(1, &vao);
		}
	}
}