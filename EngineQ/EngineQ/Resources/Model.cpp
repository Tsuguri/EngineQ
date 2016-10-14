#include "Model.hpp"

namespace EngineQ
{
	namespace Resources
	{
		Model::Node& Model::GetRootNode() const
		{
			return *this->rootNode;
		}

		Model::Node& Model::Node::AddChild()
		{
			this->children.push_back(std::make_unique<Node>(this));
			return *this->children.back().get();
		}

		Model::Node::Node(Model::Node* parent) :
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
	}
}