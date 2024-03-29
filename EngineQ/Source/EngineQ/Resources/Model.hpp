#ifndef ENGINEQ_RESOURCES_MODEL_HPP
#define ENGINEQ_RESOURCES_MODEL_HPP

// Standard includes
#include <memory>
#include <vector>
#include <type_traits>

// Libraries
#include <GL/glew.h>

// Other projects
#include "EngineQCommon/Utilities/PointerWrapper.hpp"
#include "EngineQRenderer/Graphics/Mesh.hpp"


namespace EngineQ
{
	namespace Resources
	{
		enum class VertexComponent
		{
			Position = 1 << 0,
			Normal = 1 << 1,
			Color = 1 << 2,
			TextureCoordinates = 1 << 3,
		};

		constexpr VertexComponent operator | (VertexComponent left, VertexComponent right)
		{
			using Type = std::underlying_type<VertexComponent>::type;

			return static_cast<VertexComponent>(static_cast<Type>(left) | static_cast<Type>(right));
		}

		constexpr VertexComponent operator & (VertexComponent left, VertexComponent right)
		{
			using Type = std::underlying_type<VertexComponent>::type;

			return static_cast<VertexComponent>(static_cast<Type>(left) & static_cast<Type>(right));
		}

		


		class Model
		{
			friend class ModelLoader;
			
		public:
			class Mesh
			{
				friend class ModelLoader;

			public:
				struct ComponentData
				{
					GLuint location;
					GLenum type;
					GLint size;
					GLboolean normalized;

					unsigned char bytesSize;

					ComponentData(GLuint location, GLenum type, GLint size, GLboolean normalized, unsigned char bytesSize);
				};

			private:
				unsigned int vertexSize;
				std::vector<ComponentData> data;

				VertexComponent vertexComponents;

				std::vector<char> verticesData;
				std::vector<GLuint> indices;
			
			public:
				unsigned int GetVertexSize() const;
				VertexComponent GetVertexComponents() const;

				const std::vector<char>& GetVerticesData() const;
				const std::vector<GLuint>& GetIndices() const;
				const std::vector<ComponentData>& GetComponentData() const;

				Graphics::Mesh::ConstructionData ToMeshContructionData() const;
			};
			
			class Node
			{
				friend class ModelLoader;

			private:
				Node* parent;
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
			std::vector<Utilities::PointerWrapper<Mesh>> meshes;

		public:
			Node& GetRootNode() const;
			const std::vector<Utilities::PointerWrapper<Mesh>>& GetMeshes() const;
		};
	}
}

#endif // !ENGINEQ_RESOURCES_MODEL_HPP