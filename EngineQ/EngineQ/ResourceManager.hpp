#ifndef ENGINEQ_RESOURCE_MANAGER_HPP
#define ENGINEQ_RESOURCE_MANAGER_HPP

#include <unordered_map>
namespace EngineQ
{
	class ResourceManager
	{
	private:
		std::unordered_map<std::string, void*> resources;
	public:
		ResourceManager();

		template<typename T>
		void AddResource(std::string id,T* object);

		template <typename T>
		T* GetResource(std::string id);

	};

	template <typename T>
	void ResourceManager::AddResource(std::string id, T* object)
	{
		if (resources.count(id) > 0)
			throw "exists";
		resources[id] = object;
	}

	template <typename T>
	T* ResourceManager::GetResource(std::string id)
	{
		if (resources.count(id) == 0)
			return nullptr;
		return static_cast<T*>(resources[id]);
	}
}

#endif