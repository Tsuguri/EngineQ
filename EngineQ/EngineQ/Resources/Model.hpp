#ifndef ENGINEQ_RESOURCES_MODEL_HPP
#define ENGINEQ_RESOURCES_MODEL_HPP

#include <memory>
#include <vector>

#include "../Libraries/GL/glew.h"

namespace EngineQ
{
	namespace Resources
	{
		template<typename TVertexType>
		class Model
		{
		public:
			class Mesh
			{
				friend class ModelLoader;
				friend class ModelLoader2;

			private:
				std::vector<TVertexType> vertices;
				std::vector<GLuint> indices;
			
			public:
				const std::vector<TVertexType>& GetVertices() const;
				const std::vector<GLuint>& GetIndices() const;
			};
			
			class Node
			{
				friend class ModelLoader;
				friend class ModelLoader2;

			private:
				Node* parent = nullptr;
				std::vector<std::unique_ptr<Node>> children;

				std::vector<Mesh> meshes;
			
				Node& AddChild();

			public:
				Node(Node* parent);

				Node* GetParent() const;
				const std::vector<std::unique_ptr<Node>>& GetChildren() const;
				const std::vector<Mesh>& GetMeshes() const;
			};
			
		private:
			std::unique_ptr<Node> rootNode = std::make_unique<Node>(nullptr);
			
		public:
			Node& GetRootNode() const;
		};
	}
}

#include "Model.inl"

#endif // !ENGINEQ_RESOURCES_MODEL_HPP