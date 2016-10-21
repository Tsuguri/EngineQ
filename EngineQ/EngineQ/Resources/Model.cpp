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