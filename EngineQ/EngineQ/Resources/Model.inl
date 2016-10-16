namespace EngineQ
{
	namespace Resources
	{
		template<typename TVertexType>
		const std::vector<TVertexType>& Model<TVertexType>::Mesh::GetVertices() const
		{
			return this->vertices;
		}

		template<typename TVertexType>
		const std::vector<GLuint>& Model<TVertexType>::Mesh::GetIndices() const
		{
			return this->indices;
		}

		template<typename TVertexType>
		typename Model<TVertexType>::Node& Model<TVertexType>::GetRootNode() const
		{
			return *this->rootNode;
		}

		template<typename TVertexType>
		typename Model<TVertexType>::Node& Model<TVertexType>::Node::AddChild()
		{
			this->children.push_back(std::make_unique<Node>(this));
			return *this->children.back().get();
		}

		template<typename TVertexType>
		Model<TVertexType>::Node::Node(typename Model<TVertexType>::Node* parent) :
			parent{ parent }
		{
		}

		template<typename TVertexType>
		typename Model<TVertexType>::Node* Model<TVertexType>::Node::GetParent() const
		{
			return this->parent;
		}

		template<typename TVertexType>
		const std::vector<std::unique_ptr<typename Model<TVertexType>::Node>>& Model<TVertexType>::Node::GetChildren() const
		{
			return this->children;
		}

		template<typename TVertexType>
		const std::vector<typename Model<TVertexType>::Mesh>& Model<TVertexType>::Node::GetMeshes() const
		{
			return this->meshes;
		}
	}
}