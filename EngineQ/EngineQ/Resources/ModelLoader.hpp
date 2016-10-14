#ifndef ENGINEQ_RESOURCES_MODEL_LOADER_HPP
#define ENGINEQ_RESOURCES_MODEL_LOADER_HPP

#include <memory>

#include "Types.hpp"

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
			std::unique_ptr<Model> currentModel = nullptr;
			const aiScene* scene = nullptr;

		public:
			std::unique_ptr<Model> LoadModel(const char* path);
		
		private:
			void ProcessScene(aiNode* sceneNode, Model::Node& modelNode);
			Model::Mesh ProcessMesh(aiMesh* mesh);

			bool CheckVertex(aiMesh* mesh);
			VertexPNC ConvertVertex(aiMesh* mesh, int index);
		};
	}
}

#endif