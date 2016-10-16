#ifndef ENGINEQ_RESOURCE_MANAGER_HPP
#define ENGINEQ_RESOURCE_MANAGER_HPP

#include <unordered_map>
#include <vector>
#include <string>
#include <memory>

#include "Libraries/TinyXML/tinyxml2.h"

#include "Graphics/Shader.hpp"
#include "Resources/Model.hpp"

namespace EngineQ
{
	class ResourceFileLoadingException : std::runtime_error
	{
	public:
		using std::runtime_error::runtime_error;
	};

	class ResourceManager
	{
	private:
		enum class ResourceType
		{
			Shader,
			Model,

			Count,
		};

		class BaseResource
		{
		protected:
			std::string path = "";
			int garbageCount = 0;

		public:
			BaseResource(const std::string& path);
			virtual ~BaseResource() = default;

			virtual void Update() = 0;
		};

		template<typename TResource>
		class Resource : public BaseResource
		{
		public:
			static ResourceType GetType();
		
		private:
			std::shared_ptr<TResource> resource = nullptr;

			void Load();

		public:
			Resource(const std::string& path);

			void Unload();
			virtual void Update() override;
			std::shared_ptr<TResource> GetResource();
		};

		static constexpr int GarbageUpdates = 10;
		
		std::vector<std::unordered_map<int, std::unique_ptr<BaseResource>>> resources{ static_cast<int>(ResourceType::Count) };

	public:
		void Update();

		template<typename TResource>
		void AddResource(int id, const std::string& path);

		template<typename TResource>
		void RemoveResource(int id);

		template<typename TResource>
		std::shared_ptr<TResource> GetResource(int id);
	};
	
	template<>
	ResourceManager::ResourceType ResourceManager::Resource<Graphics::Shader>::GetType();

//	template<>
//	ResourceManager::ResourceType ResourceManager::Resource<Resources::Model>::GetType();

	template<>
	void ResourceManager::Resource<Graphics::Shader>::Load();

//	template<>
//	void ResourceManager::Resource<Resources::Model>::Load();
}

#include "ResourceManager.inl"

#endif // !ENGINEQ_RESOURCE_MANAGER_HPP
