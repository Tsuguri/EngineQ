#include "ModelLoader.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Model.hpp"

#include "../Utilities/EnumHelpers.hpp"
#include "../Vertex.hpp"

namespace EngineQ
{
	namespace Resources
	{
		template<typename TType>
		void AddComponentData(std::vector<Model::Mesh::ComponentData>& data, int& vertexSize)
		{
			data.emplace_back(
				TType::Location,
				VertexTypeMap<typename TType::UnderlyingType>::value,
				sizeof(typename TType::Type) / sizeof(typename TType::UnderlyingType),
				GL_FALSE,
				sizeof(typename TType::Type)
			);

			vertexSize += sizeof(typename TType::Type);
		}

		std::unique_ptr<Model> ModelLoader::LoadModel(const char* path, VertexComponent vertexComponents, Config config)
		{
			this->vertexComponents = vertexComponents;
			this->config = config;
			this->vertexSize = 0;

			unsigned int flags = 0;
			if (Utilities::IsFlagSet(this->config.flags, Flags::FlipUVs))
				flags |= aiProcess_FlipUVs;

			if (Utilities::IsFlagSet(this->config.flags, Flags::Triangulate))
				flags |= aiProcess_Triangulate;

			Assimp::Importer importer;
			this->scene = importer.ReadFile(path, flags);

			if (this->scene == nullptr || this->scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || this->scene->mRootNode == nullptr)
				throw ModelLoadingException(importer.GetErrorString());

			this->currentModel = std::make_unique<Model>();

			if (Utilities::IsFlagSet(vertexComponents, VertexComponent::Position))
				AddComponentData<VPos>(this->componentData, this->vertexSize);

			if (Utilities::IsFlagSet(vertexComponents, VertexComponent::Color))
				AddComponentData<VCol>(this->componentData, this->vertexSize);

			if (Utilities::IsFlagSet(vertexComponents, VertexComponent::Normal))
				AddComponentData<VNorm>(this->componentData, this->vertexSize);

			if (Utilities::IsFlagSet(vertexComponents, VertexComponent::TextureCoordinates))
				AddComponentData<VTex>(this->componentData, this->vertexSize);
			
			ProcessScene(this->scene->mRootNode, this->currentModel->GetRootNode());

			return std::move(this->currentModel);
		}

		void ModelLoader::ProcessScene(aiNode* sceneNode, Model::Node& modelNode)
		{
			for (int i = 0; i < sceneNode->mNumMeshes; ++i)
			{
				modelNode.meshes.push_back(this->ProcessMesh(this->scene->mMeshes[sceneNode->mMeshes[i]]));
			}

			for (int i = 0; i < sceneNode->mNumChildren; ++i)
			{
				Model::Node& child = modelNode.AddChild();
				this->ProcessScene(sceneNode->mChildren[i], child);
			}
		}

		Model::Mesh ModelLoader::ProcessMesh(aiMesh* mesh)
		{
			SetConverters(mesh);

			Model::Mesh modelMesh;

			modelMesh.data = this->componentData;
			modelMesh.vertexSize = this->vertexSize;
			modelMesh.vertexComponents = this->vertexComponents;
			modelMesh.verticesData.resize(mesh->mNumVertices * this->vertexSize);
			char* dataPointer = modelMesh.verticesData.data();
			
			for (int vertexIndex = 0; vertexIndex < mesh->mNumVertices; ++vertexIndex)
			{
				for (int converterIndex = 0; converterIndex < this->converters.size(); ++converterIndex)
				{
					auto converter = this->converters[converterIndex];

					(this->*converter)(mesh, vertexIndex, dataPointer);
					dataPointer += this->componentData[converterIndex].bytesSize;
				}
			}

			modelMesh.indices.reserve(mesh->mNumFaces * 3);
			for (int faceIndex = 0; faceIndex < mesh->mNumFaces; ++faceIndex)
			{
				aiFace face = mesh->mFaces[faceIndex];
				for (int indexIndex = 0; indexIndex < face.mNumIndices; ++indexIndex)
					modelMesh.indices.push_back(face.mIndices[indexIndex]);
			}

			return modelMesh;
		}

		void ModelLoader::SetConverters(aiMesh* mesh)
		{
			this->converters.clear();

			if (Utilities::IsFlagSet(this->vertexComponents, VertexComponent::Position))
			{
				if (mesh->HasPositions())
					this->converters.push_back(&ModelLoader::PositionConverter);
				else
					this->converters.push_back(&ModelLoader::PositionConverterDefault);
			}

			if (Utilities::IsFlagSet(this->vertexComponents, VertexComponent::Color))
			{
				if (mesh->HasVertexColors(0))
					this->converters.push_back(&ModelLoader::ColorConverter);
				else
					this->converters.push_back(&ModelLoader::ColorConverterDefault);
			}

			if (Utilities::IsFlagSet(this->vertexComponents, VertexComponent::Normal))
			{
				if (mesh->HasNormals())
					this->converters.push_back(&ModelLoader::NormalConverter);
				else
					this->converters.push_back(&ModelLoader::NormalConverterDefault);
			}

			if (Utilities::IsFlagSet(this->vertexComponents, VertexComponent::TextureCoordinates))
			{
				if (mesh->HasTextureCoords(0))
					this->converters.push_back(&ModelLoader::TextureCoordinatesConverter);
				else
					this->converters.push_back(&ModelLoader::TextureCoordinatesConverterDefault);
			}
		}

		void ModelLoader::PositionConverter(aiMesh* mesh, int index, char* data)
		{
			aiVector3D position = mesh->mVertices[index];

			Math::Vector3f* positionData = reinterpret_cast<Math::Vector3f*>(data);
			positionData->X = position.x;
			positionData->Y = position.y;
			positionData->Z = position.z;
		}

		void ModelLoader::PositionConverterDefault(aiMesh* mesh, int index, char* data)
		{
			Math::Vector3f* positionData = reinterpret_cast<Math::Vector3f*>(data);
			*positionData = this->config.positionDefault;
		}
		
		void ModelLoader::NormalConverter(aiMesh* mesh, int index, char* data)
		{
			aiVector3D normal = mesh->mNormals[index];

			Math::Vector3f* normalData = reinterpret_cast<Math::Vector3f*>(data);
			normalData->X = normal.x;
			normalData->Y = normal.y;
			normalData->Z = normal.z;
		}
		
		void ModelLoader::NormalConverterDefault(aiMesh* mesh, int index, char* data)
		{
			Math::Vector3f* normalData = reinterpret_cast<Math::Vector3f*>(data);
			*normalData = this->config.normalDefault;
		}
	
		void ModelLoader::ColorConverter(aiMesh* mesh, int index, char* data)
		{
			aiColor4D color = mesh->mColors[0][index];

			Math::Vector3f* colorData = reinterpret_cast<Math::Vector3f*>(data);
			colorData->X = color.r;
			colorData->Y = color.g;
			colorData->Z = color.b;
		}

		void ModelLoader::ColorConverterDefault(aiMesh* mesh, int index, char* data)
		{
			Math::Vector3f* colorData = reinterpret_cast<Math::Vector3f*>(data);
			*colorData = this->config.colorDefault;
		}
		
		void ModelLoader::TextureCoordinatesConverter(aiMesh* mesh, int index, char* data)
		{
			aiVector3D textureCoordinates = mesh->mTextureCoords[0][index];

			Math::Vector2f* textureCoordinatesData = reinterpret_cast<Math::Vector2f*>(data);
			textureCoordinatesData->X = textureCoordinates.x;
			textureCoordinatesData->Y = textureCoordinates.y;
		}

		void ModelLoader::TextureCoordinatesConverterDefault(aiMesh* mesh, int index, char* data)
		{
			Math::Vector2f* textureCoordinatesData = reinterpret_cast<Math::Vector2f*>(data);
			*textureCoordinatesData = this->config.textureCoordinatesDefault;
		}
	}
}