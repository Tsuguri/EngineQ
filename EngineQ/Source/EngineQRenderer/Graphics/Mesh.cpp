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

		//Mesh::Mesh(const Resources::Model::Mesh& mesh)
		//{
		//	//Generating vertex array and buffers
		//	glGenVertexArrays(1, &this->vao);
		//	glGenBuffers(VboSize, &this->vbo[0]);

		//	glBindVertexArray(this->vao);


		//	//sending data of vertices
		//	const auto& vertices = mesh.GetVerticesData();
		//	
		//	glBindBuffer(GL_ARRAY_BUFFER, this->vbo[0]);
		//	glBufferData(GL_ARRAY_BUFFER, vertices.size(), vertices.data(), GL_STATIC_DRAW);


		//	//setting components pointers
		//	std::size_t offset = 0;
		//	for (const auto& data : mesh.GetComponentData())
		//	{
		//		glEnableVertexAttribArray(data.location);
		//		glVertexAttribPointer(data.location, data.size, data.type, data.normalized, mesh.GetVertexSize(), reinterpret_cast<const GLvoid*>(offset));
		//	
		//		offset += data.bytesSize;
		//	}


		//	//sending indices data
		//	const auto& indices = mesh.GetIndices();
		//
		//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->vbo[2]);
		//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
		//	glBindBuffer(GL_ARRAY_BUFFER, NULL);
		//	indicesCount = static_cast<GLuint>(indices.size());
		//}

		Mesh::Mesh(ConstructionData data)
		{
			indicesCount = data.indicesCount;
			vao = data.vao;
			for (int i = 0; i < VboSize; i++)
				vbo[i] = data.vbo[i];
		}

		Mesh::~Mesh()
		{
			glDeleteBuffers(VboSize, vbo);
			glDeleteVertexArrays(1, &vao);
		}
	}
}