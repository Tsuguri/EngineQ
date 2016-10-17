#ifndef ENGINEQ_RESOURCES_RESOURCE_HPP
#define ENGINEQ_RESOURCES_RESOURCE_HPP

#include <memory>

#include "../Objects/Object.hpp"

namespace EngineQ
{
	namespace Resources
	{
		template<typename TResourceType>
		class Resource
		{
		private:
			struct ControlBlock
			{
				int referenceCount = 1;
			};

			class Container : public Object
			{
			private:
				ControlBlock* const controlBlock;
				std::unique_ptr<TResourceType> resource;

			public:
				Container(Scripting::ScriptEngine& scriptEngine, Scripting::ScriptClass resourceClass, ControlBlock* controlBlock, std::unique_ptr<TResourceType> resource) :
					Object{ scriptEngine, resourceClass }, controlBlock{ controlBlock }, resource{ std::move(resource) }
				{
				}

				TResourceType& Get()
				{
					return *this->resource.get();
				}

				int GetReferenceCount() const
				{
					return this->controlBlock->referenceCount;
				}
			};

			ControlBlock* controlBlock = nullptr;
			Container* container = nullptr;

			void Remove()
			{
				if (this->controlBlock == nullptr)
					return;

				this->controlBlock->referenceCount -= 1;
				if (this->controlBlock->referenceCount == 0)
				{
					delete this->controlBlock;
					delete this->container;
				}
			}

			void Add()
			{
				if (this->controlBlock == nullptr)
					return;

				this->controlBlock->referenceCount += 1;
			}

		public:
			Resource() = default;

			Resource(Scripting::ScriptEngine& scriptEngine, Scripting::ScriptClass resourceClass, std::unique_ptr<TResourceType> resource)
			{
				this->controlBlock = new ControlBlock{};
				this->container = new Container{ scriptEngine, resourceClass, this->controlBlock, std::move(resource) };
			}
			
			~Resource()
			{
				this->Remove();
			}

			Resource(const Resource& other) :
				controlBlock{ other.controlBlock }, container{ other.container }
			{
				this->Add();
			}

			Resource(Resource&& other) :
				controlBlock{ other.controlBlock }, container{ other.container }
			{
				other.controlBlock = nullptr;
			}

			Resource& operator = (const Resource& other)
			{
				if (this == &other)
					return *this;

				this->Remove();

				this->controlBlock = other.controlBlock;
				this->container = other.container;

				this->Add();

				return *this;
			}

			Resource& operator = (Resource&& other)
			{
				this->Remove();

				this->controlBlock = other.controlBlock;
				this->container = other.container;

				other.controlBlock = nullptr;

				return *this;
			}

			bool operator == (nullptr_t) const
			{
				return this->controlBlock == nullptr;
			}

			bool operator != (nullptr_t) const
			{
				return this->controlBlock != nullptr;
			}

			TResourceType* operator -> () const
			{
				return &this->container->Get();
			}

			TResourceType& operator * () const
			{
				return this->container->Get();
			}
		};
	}
}

#endif // !ENGINEQ_RESOURCES_RESOURCE_HPP
