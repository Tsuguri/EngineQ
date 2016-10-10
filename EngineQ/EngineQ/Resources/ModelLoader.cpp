#include "ModelLoader.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
namespace EngineQ
{
	namespace Resources
	{
		ModelLoader::ModelLoader()
			{
				Assimp::Importer importer;
				char* path = nullptr;
				//const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
			}
	}
}