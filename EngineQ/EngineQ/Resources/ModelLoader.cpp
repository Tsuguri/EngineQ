#include "ModelLoader.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Model.hpp"

namespace EngineQ
{
	namespace Resources
	{
		std::unique_ptr<Model<VertexPNC>> ModelLoader::LoadModel(const char* path)
		{
			Assimp::Importer importer;

			this->scene = importer.ReadFile(path, aiProcess_FlipUVs | aiProcess_Triangulate);

			if (this->scene == nullptr || this->scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || this->scene->mRootNode == nullptr)
				throw ModelLoadingException(importer.GetErrorString());

			this->currentModel = std::make_unique<Model<VertexPNC>>();

			ProcessScene(this->scene->mRootNode, this->currentModel->GetRootNode());

			return std::move(this->currentModel);
		}

		void ModelLoader::ProcessScene(aiNode* sceneNode, Model<VertexPNC>::Node& modelNode)
		{
			for (int i = 0; i < sceneNode->mNumMeshes; ++i)
			{
				modelNode.meshes.push_back(this->ProcessMesh(this->scene->mMeshes[sceneNode->mMeshes[i]]));
			}

			for (int i = 0; i < sceneNode->mNumChildren; ++i)
			{
				Model<VertexPNC>::Node& child = modelNode.AddChild();
				this->ProcessScene(sceneNode->mChildren[i], child);
			}
		}

		Model<VertexPNC>::Mesh ModelLoader::ProcessMesh(aiMesh* mesh)
		{
			if (!this->CheckVertex(mesh))
				throw ModelLoadingException{ "Model does not support vertex type" };

			Model<VertexPNC>::Mesh modelMesh;

			modelMesh.vertices.resize(mesh->mNumVertices);
			for (int i = 0; i < mesh->mNumVertices; ++i)
				modelMesh.vertices[i] = ConvertVertex(mesh, i);

			modelMesh.indices.reserve(mesh->mNumFaces * 3);
			for (int faceIndex = 0; faceIndex < mesh->mNumFaces; ++faceIndex)
			{
				aiFace face = mesh->mFaces[faceIndex];
				for (int indexIndex = 0; indexIndex < face.mNumIndices; ++indexIndex)
					modelMesh.indices.push_back(face.mIndices[indexIndex]);
			}

			return modelMesh;
		}

		bool ModelLoader::CheckVertex(aiMesh* mesh)
		{
			return mesh->HasPositions() && mesh->HasNormals();// && mesh->HasVertexColors(0);
		}

		VertexPNC ModelLoader::ConvertVertex(aiMesh* mesh, int index)
		{
			aiVector3D position = mesh->mVertices[index];
			aiVector3D normal = mesh->mNormals[index];
			aiColor4D color = { 1, 1, 1, 1 };// = mesh->mColors[index][0];

			return VertexPNC{
				Math::Vector3f{ position.x, position.y, position.z } * 0.1f,
				Math::Vector3f{ normal.x, normal.y, normal.z },
				Math::Vector3f{ color.r, color.g, color.b }
			};
		}







		std::unique_ptr<Model<VertexPNTC>> ModelLoader2::LoadModel(const char* path)
		{
			Assimp::Importer importer;

			this->scene = importer.ReadFile(path, aiProcess_FlipUVs | aiProcess_Triangulate);

			if (this->scene == nullptr || this->scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || this->scene->mRootNode == nullptr)
				throw ModelLoadingException(importer.GetErrorString());

			this->currentModel = std::make_unique<Model<VertexPNTC>>();

			ProcessScene(this->scene->mRootNode, this->currentModel->GetRootNode());

			return std::move(this->currentModel);
		}

		void ModelLoader2::ProcessScene(aiNode* sceneNode, Model<VertexPNTC>::Node& modelNode)
		{
			for (int i = 0; i < sceneNode->mNumMeshes; ++i)
			{
				modelNode.meshes.push_back(this->ProcessMesh(this->scene->mMeshes[sceneNode->mMeshes[i]]));
			}

			for (int i = 0; i < sceneNode->mNumChildren; ++i)
			{
				Model<VertexPNTC>::Node& child = modelNode.AddChild();
				this->ProcessScene(sceneNode->mChildren[i], child);
			}
		}

		Model<VertexPNTC>::Mesh ModelLoader2::ProcessMesh(aiMesh* mesh)
		{
			if (!this->CheckVertex(mesh))
				throw ModelLoadingException{ "Model does not support vertex type" };

			Model<VertexPNTC>::Mesh modelMesh;

			modelMesh.vertices.resize(mesh->mNumVertices);
			for (int i = 0; i < mesh->mNumVertices; ++i)
				modelMesh.vertices[i] = ConvertVertex(mesh, i);

			modelMesh.indices.reserve(mesh->mNumFaces * 3);
			for (int faceIndex = 0; faceIndex < mesh->mNumFaces; ++faceIndex)
			{
				aiFace face = mesh->mFaces[faceIndex];
				for (int indexIndex = 0; indexIndex < face.mNumIndices; ++indexIndex)
					modelMesh.indices.push_back(face.mIndices[indexIndex]);
			}

			return modelMesh;
		}

		bool ModelLoader2::CheckVertex(aiMesh* mesh)
		{
			return mesh->HasPositions() && mesh->HasNormals();// && mesh->HasVertexColors(0);
		}

		VertexPNTC ModelLoader2::ConvertVertex(aiMesh* mesh, int index)
		{
			aiVector3D position = mesh->mVertices[index];
			aiVector3D normal = mesh->mNormals[index];
			aiColor4D color = { 1, 1, 1, 1 };// = mesh->mColors[index][0];
			aiVector3D tex = mesh->mTextureCoords[0][index];

			return VertexPNTC{
				Math::Vector3f{ position.x, position.y, position.z } *0.1f,
				Math::Vector3f{ normal.x, normal.y, normal.z },
				Math::Vector2f{ tex.x, tex.y },
				Math::Vector3f{ color.r, color.g, color.b }
			};
		}
	}
}