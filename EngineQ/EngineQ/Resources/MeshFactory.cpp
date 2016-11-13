#include "MeshFactory.hpp"

#include <unordered_map>

#include <Libraries/TinyXML/tinyxml2.h>

#include "ResourceManager.hpp"
#include "ResourceFactory.hpp"
#include <Graphics/Mesh.hpp>
#include "Model.hpp"

namespace EngineQ
{
	namespace Resources
	{
		std::unique_ptr<Graphics::Mesh> ResourceFactory<Graphics::Mesh>::CreateResource(ResourceManager& resourceManager, const char* filename)
		{
			tinyxml2::XMLDocument doc{};
			doc.LoadFile(filename);

			if (doc.Error())
				throw ResourceLoadingException{ doc.GetErrorStr1() };

			auto rootElement = doc.RootElement();

			auto modelElement = rootElement->FirstChildElement("Model");
			const char* modelPath = modelElement->Attribute("Path");
			std::string modelResourceName = modelElement->Attribute("ResourceName");


			auto currentElement = rootElement;

			std::vector<int> nodeIndices;

			auto meshElement = rootElement->FirstChildElement("ModelMesh");
			while (meshElement == nullptr)
			{
				auto nodeElement = currentElement->FirstChildElement("ModelNode");

				int index = nodeElement->IntAttribute("Index");
				nodeIndices.push_back(index);

				currentElement = nodeElement;
				meshElement = currentElement->FirstChildElement("ModelMesh");
			}

			int meshIndex = meshElement->IntAttribute("Index");


			Resource<Model> model = resourceManager.TryGetResource<Model>(modelResourceName);
			if (model == nullptr)
			{
				resourceManager.RegisterResource<Model>(modelResourceName, modelPath);
				model = resourceManager.GetResource<Model>(modelResourceName);
			}

			const Model::Mesh* mesh;

			if (nodeIndices.empty())
			{
				mesh = model->GetMeshes()[0];
			}
			else
			{
				Model::Node* modelCurrentNode = &model->GetRootNode();
				for (int index : nodeIndices)
					modelCurrentNode = modelCurrentNode->GetChildren()[index].get();

				mesh = &modelCurrentNode->GetMeshes()[meshIndex];
			}

			return std::make_unique<Graphics::Mesh>(mesh->ToMeshContructionData());
		}
	}
}