#ifndef ENGINEQ_RESOURCES_MODEL_LOADER_HPP
#define ENGINEQ_RESOURCES_MODEL_LOADER_HPP

#include <memory>

#include "Types.hpp"
#include "Model.hpp"
#include "../Math/Vector3.hpp"

#include "../Utilities/EnumHelpers.hpp"

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
		public:
			enum class Flags
			{
				FlipUVs = 1 << 0,
				Triangulate = 1 << 1,
			};
			
			struct Config
			{
				Flags flags = Utilities::MakeFlags(Flags::FlipUVs, Flags::Triangulate);

				Math::Vector3f positionDefault{ 0.0f };
				Math::Vector3f normalDefault{ 0.0f };
				Math::Vector3f colorDefault{ 0.5f };
				Math::Vector2f textureCoordinatesDefault{ 0.0f };
			};

		private:
			using VertexConverter = void(ModelLoader::*)(aiMesh* mesh, std::size_t index, char* data);

			std::unique_ptr<Model> currentModel = nullptr;
			const aiScene* scene = nullptr;

			Config config;
			VertexComponent vertexComponents;
			int vertexSize;

			std::vector<VertexConverter> converters;
			std::vector<Model::Mesh::ComponentData> componentData;

		public:
			std::unique_ptr<Model> LoadModel(const char* path, VertexComponent vertexComponents, Config config);
		
		private:
			void ProcessScene(aiNode* sceneNode, Model::Node& modelNode);
			Model::Mesh ProcessMesh(aiMesh* mesh);

			void SetConverters(aiMesh* mesh);

			void PositionConverter(aiMesh* mesh, std::size_t index, char* data);
			void PositionConverterDefault(aiMesh* mesh, std::size_t index, char* data);

			void NormalConverter(aiMesh* mesh, std::size_t index, char* data);
			void NormalConverterDefault(aiMesh* mesh, std::size_t index, char* data);

			void ColorConverter(aiMesh* mesh, std::size_t index, char* data);
			void ColorConverterDefault(aiMesh* mesh, std::size_t index, char* data);

			void TextureCoordinatesConverter(aiMesh* mesh, std::size_t index, char* data);
			void TextureCoordinatesConverterDefault(aiMesh* mesh, std::size_t index, char* data);
		};

		constexpr ModelLoader::Flags operator | (ModelLoader::Flags left, ModelLoader::Flags right)
		{
			using Type = std::underlying_type<ModelLoader::Flags>::type;

			return static_cast<ModelLoader::Flags>(static_cast<Type>(left) | static_cast<Type>(right));
		}

		constexpr ModelLoader::Flags operator & (ModelLoader::Flags left, ModelLoader::Flags right)
		{
			using Type = std::underlying_type<ModelLoader::Flags>::type;

			return static_cast<ModelLoader::Flags>(static_cast<Type>(left) & static_cast<Type>(right));
		}
	}
}

#endif