#ifndef ENGINEQ_RESOURCES_RESOURCE_HPP
#define ENGINEQ_RESOURCES_RESOURCE_HPP

#include <memory>
#include <stdexcept>

namespace EngineQ
{
	namespace Resources
	{
		class ResourceDestroyedException : public std::runtime_error
		{
		public:
			using std::runtime_error::runtime_error;
		};


		class BaseResource
		{
		public:
			class BaseControlBlock
			{
			private:
				int nativeReferenceCount = 0;
				int allReferenceCount = 0;

			public:
				BaseControlBlock() = default;
				virtual ~BaseControlBlock() = default;

				int GetNativeReferenceCount() const;
				int GetAllReferenceCount() const;

				static void AddNativeReference(BaseControlBlock* controlBlock);
				static void AddManagedReference(BaseControlBlock* controlBlock);

				static void RemoveNativeReference(BaseControlBlock*& controlBlock);
				static void RemoveManagedReference(BaseControlBlock*& controlBlock);

				bool IsResourceDestroyed() const;

			protected:
				virtual void DestroyData() = 0;
				virtual bool IsDataDestroyed() const = 0;
			};

		protected:
			BaseControlBlock* controlBlock = nullptr;

			BaseResource(BaseControlBlock* controlBlock);

		public:
			BaseResource() = default;
			virtual ~BaseResource() = default;

			int GetAllReferenceCount() const;
			int GetNativeReferenceCount() const;
			int GetManagedReferenceCount() const;

			bool operator == (nullptr_t) const;
			bool operator != (nullptr_t) const;
		};





		template<typename TResourceType>
		class Resource : public BaseResource
		{
		public:
			class ControlBlock : public BaseControlBlock
			{
				friend class ResourceManager;

			private:
				std::unique_ptr<TResourceType> data;

			public:
				ControlBlock() = default;

				ControlBlock(std::unique_ptr<TResourceType> resource) :
					BaseControlBlock{}, data{ std::move(resource) }
				{
				}

				virtual void DestroyData() override
				{
					this->data = nullptr;
				}

				virtual bool IsDataDestroyed() const override
				{
					return this->data == nullptr;
				}

				TResourceType* Get() const
				{
					return this->data.get();
				}

				Resource<TResourceType> GetResource()
				{
					if (this->IsResourceDestroyed())
						throw ResourceDestroyedException{ "Resource is destroyed" };

					return Resource<TResourceType>{ this };
				}
			};

		private:
			Resource(ControlBlock* controlBlock) :
				BaseResource{ controlBlock }
			{
				BaseControlBlock::AddNativeReference(this->controlBlock);
			}

		public:
			explicit Resource(std::unique_ptr<TResourceType> resource) :
				BaseResource{ new ControlBlock{ std::move(resource) } }
			{
				BaseControlBlock::AddNativeReference(this->controlBlock);
			}

			Resource() :
				BaseResource{ nullptr }
			{
			}

			~Resource()
			{
				if (this->controlBlock != nullptr)
					BaseControlBlock::RemoveNativeReference(this->controlBlock);
			}

			Resource(nullptr_t) :
				BaseResource{ nullptr }
			{
			}

			Resource& operator = (nullptr_t)
			{
				if (this->controlBlock != nullptr)
				{
					BaseControlBlock::RemoveNativeReference(this->controlBlock);
					this->controlBlock = nullptr;
				}

				return *this;
			}

			Resource(const Resource& other) :
				BaseResource{ other.controlBlock }
			{
				if (this->controlBlock != nullptr)
					BaseControlBlock::AddNativeReference(this->controlBlock);
			}

			Resource& operator = (const Resource& other)
			{
				if (this->controlBlock == other.controlBlock)
					return *this;

				if (this->controlBlock != nullptr)
					BaseControlBlock::RemoveNativeReference(this->controlBlock);

				this->controlBlock = other.controlBlock;

				if (this->controlBlock != nullptr)
					BaseControlBlock::AddNativeReference(this->controlBlock);

				return *this;
			}

			Resource(Resource&& other) :
				BaseResource{ other.controlBlock }
			{
				other.controlBlock = nullptr;
			}

			Resource& operator = (Resource&& other)
			{
				auto tmp = this->controlBlock;
				this->controlBlock = other.controlBlock;
				other.controlBlock = tmp;
				
				return *this;
			}

			TResourceType* operator -> () const
			{
				return static_cast<ControlBlock*>(this->controlBlock)->Get();
			}

			TResourceType& operator * () const
			{
				return *static_cast<ControlBlock*>(this->controlBlock)->Get();
			}

			ControlBlock* GetControlBlock() const
			{
				return static_cast<ControlBlock*>(this->controlBlock);
			}

			operator TResourceType* () const
			{
				if (this->controlBlock == nullptr)
					return nullptr;

				return static_cast<ControlBlock*>(this->controlBlock)->Get();
			}
		};
	}
}

#endif // !ENGINEQ_RESOURCES_RESOURCE_HPP
