#ifndef ENGINEQ_RESOURCES_RESOURCE_HPP
#define ENGINEQ_RESOURCES_RESOURCE_HPP

#include <memory>

#include "../Objects/Object.hpp"

namespace EngineQ
{
	namespace Resources
	{
		class BaseResource
		{
		protected:
			struct ControlBlock
			{
				int referenceCount = 1;
				int managedReferenceCount = 0;
			};

		public:
			class BaseContainer : public Object
			{
			protected:
				ControlBlock* const controlBlock;

			public:
				BaseContainer(Scripting::ScriptEngine& scriptEngine, Scripting::ScriptClass resourceClass, ControlBlock* controlBlock);
				int GetReferenceCount() const;
				int GetManagedReferenceCount() const;
			};

		protected:
			ControlBlock* controlBlock = nullptr;
			BaseContainer* container = nullptr;

			void Remove();
			void Add();

			BaseResource(ControlBlock* controlBlock, BaseContainer* container);

		public:
			BaseResource() = default;

			bool operator == (nullptr_t) const;
			bool operator != (nullptr_t) const;

			int GetReferenceCount() const;
			int GetManagedReferenceCount() const;
		};





		template<typename TResourceType>
		class Resource : public BaseResource
		{
		public:
			class Container : public BaseContainer
			{
			private:
				std::unique_ptr<TResourceType> resource;

			public:
				Container(Scripting::ScriptEngine& scriptEngine, Scripting::ScriptClass resourceClass, ControlBlock* controlBlock, std::unique_ptr<TResourceType> resource) :
					BaseContainer{ scriptEngine, resourceClass, controlBlock }, resource{ std::move(resource) }
				{
				}

				TResourceType& Get()
				{
					return *this->resource.get();
				}

				Resource ToResource()
				{
					return Resource{ this->controlBlock, this };
				}
			};

			Resource(ControlBlock* controlBlock, BaseContainer* container) :
				BaseResource{ controlBlock, container }
			{
				this->Add();
			}

		public:
			Resource() = default;

			Resource(Scripting::ScriptEngine& scriptEngine, Scripting::ScriptClass resourceClass, std::unique_ptr<TResourceType> resource) :
				BaseResource{ new ControlBlock{}, new Container{ scriptEngine, resourceClass, this->controlBlock, std::move(resource) } }
			{
			}

			~Resource()
			{
				this->Remove();
			}

			Resource(const Resource& other) :
				BaseResource{ other.controlBlock, other.container }
			{
				this->Add();
			}

			Resource(Resource&& other) :
				BaseResource{ other.controlBlock, other.container }
			{
				other.controlBlock = nullptr;
			}

			Resource& operator = (nullptr_t)
			{
				this->Remove();

				this->controlBlock = nullptr;

				return *this;
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

			TResourceType* operator -> () const
			{
				return &static_cast<Container*>(this->container)->Get();
			}

			TResourceType& operator * () const
			{
				return static_cast<Container*>(this->container)->Get();
			}
		};



		/*
		template<typename TResourceType>
		class Resource
		{
		private:
			struct ControlBlock
			{
				int referenceCount = 1;
				int managedReferenceCount = 0;
			};

		public:
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

		private:
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

			Resource& operator = (nullptr_t)
			{
				this->Remove();

				this->controlBlock = nullptr;

				return *this;
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

			int GetReferenceCount() const
			{
				if (this->controlBlock == nullptr)
					return 0;

				return this->controlBlock->referenceCount;
			}

			int GetManagedReferenceCount() const
			{
				if (this->controlBlock == nullptr)
					return 0;

				return this->controlBlock->managedReferenceCount;
			}
		};
		*/
	}
}

#endif // !ENGINEQ_RESOURCES_RESOURCE_HPP
