#ifndef ENGINEQ_RESOURCES_MODEL_HPP
#define ENGINEQ_RESOURCES_MODEL_HPP
#include <memory>

#include "../Graphics/Mesh.hpp"
namespace EngineQ
{
	namespace Resources
	{
		class Model
		{
		public:
			class Mesh
			{
				friend class ModelLoader;

			private:
				std::vector <VertexPNC> vertices;
				std::vector <GLuint> indices;
			
			public:
			};
			
			class Node
			{
				friend class ModelLoader;

			private:
				Node* parent = nullptr;
				std::vector<std::unique_ptr<Node>> children;

				std::vector<Mesh> meshes;
			
				Node& AddChild();

			public:
				Node(Node* parent);

				Node* GetParent() const;
				const std::vector<std::unique_ptr<Node>>& GetChildren() const;
			};
			
		private:
			std::unique_ptr<Node> rootNode = std::make_unique<Node>(nullptr);
			
		public:
			Node& GetRootNode() const;
		};
	}
}

#endif