#ifndef ENGINEQ_RESOURCES_MODEL_LOADER_HPP
#define ENGINEQ_RESOURCES_MODEL_LOADER_HPP

#include <memory>

#include "Types.hpp"

#include "../Vertex.hpp"
#include "Model.hpp"

struct aiScene;
struct aiNode;
struct aiMesh;

namespace EngineQ
{
	namespace Resources
	{
		class ModelLoadingException : public std::runtime_error
		{
		public:
			using std::runtime_error::runtime_error;
		};

		class ModelLoader
		{
		private:
			std::unique_ptr<Model<VertexPNC>> currentModel = nullptr;
			const aiScene* scene = nullptr;

		public:
			std::unique_ptr<Model<VertexPNC>> LoadModel(const char* path);
		
		private:
			void ProcessScene(aiNode* sceneNode, Model<VertexPNC>::Node& modelNode);
			Model<VertexPNC>::Mesh ProcessMesh(aiMesh* mesh);

			bool CheckVertex(aiMesh* mesh);
			VertexPNC ConvertVertex(aiMesh* mesh, int index);
		};


		// TMP
		class ModelLoader2
		{
		private:
			std::unique_ptr<Model<VertexPNTC>> currentModel = nullptr;
			const aiScene* scene = nullptr;

		public:
			std::unique_ptr<Model<VertexPNTC>> LoadModel(const char* path);

		private:
			void ProcessScene(aiNode* sceneNode, Model<VertexPNTC>::Node& modelNode);
			Model<VertexPNTC>::Mesh ProcessMesh(aiMesh* mesh);

			bool CheckVertex(aiMesh* mesh);
			VertexPNTC ConvertVertex(aiMesh* mesh, int index);
		};
	}
}

#endif