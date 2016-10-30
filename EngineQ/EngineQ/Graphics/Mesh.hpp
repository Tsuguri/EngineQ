#ifndef ENGINEQ_GRAPHICS_MESH_HPP
#define ENGINEQ_GRAPHICS_MESH_HPP

#include <vector>

#include "../Libraries/GL/glew.h"

#include "../Utilities/Immovable.hpp"
#include "../Vertex.hpp"
#include "../Resources/Model.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		class Mesh : private Utilities::Immovable
		{
		private:
			static constexpr std::size_t VboSize = 3;

			GLuint indicesCount = 0;
			GLuint vao = 0;
			GLuint vbo[VboSize] = { 0, 0, 0 };

		public:
			template<typename... TVertexConfiguration>
			Mesh(const std::vector<Vertex<TVertexConfiguration...>>& vertices, const std::vector<GLuint>& indices)
			{
				using TVertexType = Vertex<TVertexConfiguration...>;

				//Generating vertex array and buffers
				glGenVertexArrays(1, &this->vao);
				glGenBuffers(VboSize, &this->vbo[0]);

				glBindVertexArray(this->vao);


				//sending data of vertices
				glBindBuffer(GL_ARRAY_BUFFER, this->vbo[0]);
				glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(TVertexType), vertices.data(), GL_STATIC_DRAW);


				//setting components pointers
				TVertexType::Setup();


				//sending indices data
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->vbo[2]);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
				glBindBuffer(GL_ARRAY_BUFFER, NULL);
				indicesCount = static_cast<GLuint>(indices.size());
			}

			Mesh(const Resources::Model::Mesh& mesh);

			~Mesh();
			
			GLuint GetIndicesCount() const;
			GLuint GetVao() const;
		};
	}
}
#endif
