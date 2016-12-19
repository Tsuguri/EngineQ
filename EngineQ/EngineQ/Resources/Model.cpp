#include "Model.hpp"


namespace EngineQ
{
	namespace Resources
	{
		Model::Mesh::ComponentData::ComponentData(GLuint location, GLenum type, GLint size, GLboolean normalized, unsigned char bytesSize) :
			location{ location }, type{ type }, size{ size }, normalized{ normalized }, bytesSize{ bytesSize }
		{
		}





		unsigned int Model::Mesh::GetVertexSize() const
		{
			return this->vertexSize;
		}

		VertexComponent Model::Mesh::GetVertexComponents() const
		{
			return this->vertexComponents;
		}

		const std::vector<char>& Model::Mesh::GetVerticesData() const
		{
			return this->verticesData;
		}

		const std::vector<GLuint>& Model::Mesh::GetIndices() const
		{
			return this->indices;
		}

		const std::vector<Model::Mesh::ComponentData>& Model::Mesh::GetComponentData() const
		{
			return this->data;
		}

		Graphics::Mesh::ConstructionData Model::Mesh::ToMeshContructionData() const
		{
			auto constructionData = Graphics::Mesh::ConstructionData();

					//Generating vertex array and buffers
					glGenVertexArrays(1, &constructionData.vao);
					glGenBuffers(Graphics::Mesh::VboSize, &constructionData.vbo[0]);

					glBindVertexArray(constructionData.vao);


					//sending data of vertices
					const auto& vertices = GetVerticesData();
					
					glBindBuffer(GL_ARRAY_BUFFER, constructionData.vbo[0]);
					glBufferData(GL_ARRAY_BUFFER, vertices.size(), vertices.data(), GL_STATIC_DRAW);


					//setting components pointers
					std::size_t offset = 0;
					for (const auto& data : GetComponentData())
					{
						glEnableVertexAttribArray(data.location);
						glVertexAttribPointer(data.location, data.size, data.type, data.normalized, GetVertexSize(), reinterpret_cast<const GLvoid*>(offset));
					
						offset += data.bytesSize;
					}


					//sending indices data
					const auto& indices = GetIndices();
				
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, constructionData.vbo[2]);
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
					glBindBuffer(GL_ARRAY_BUFFER, NULL);
					constructionData.indicesCount = static_cast<GLuint>(indices.size());
				
			return constructionData;
		}




		Model::Node& Model::Node::AddChild()
		{
			this->children.push_back(std::make_unique<Node>(this));
			return *this->children.back();
		}

		Model::Node::Node(Node* parent) :
			parent{ parent }
		{
		}

		Model::Node* Model::Node::GetParent() const
		{
			return this->parent;
		}

		const std::vector<std::unique_ptr<Model::Node>>& Model::Node::GetChildren() const
		{
			return this->children;
		}

		const std::vector<Model::Mesh>& Model::Node::GetMeshes() const
		{
			return this->meshes;
		}




		Model::Node& Model::GetRootNode() const
		{
			return *this->rootNode;
		}

		const std::vector<Utilities::PointerWrapper<Model::Mesh>>& Model::GetMeshes() const
		{
			return this->meshes;
		}
	}
}