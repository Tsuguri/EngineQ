#include "Resource.hpp"

namespace EngineQ
{
	namespace Resources
	{
		int BaseResource::BaseControlBlock::GetNativeReferenceCount() const
		{
			return this->nativeReferenceCount;
		}

		int BaseResource::BaseControlBlock::GetAllReferenceCount() const
		{
			return this->allReferenceCount;
		}

		void BaseResource::BaseControlBlock::AddNativeReference(BaseControlBlock* controlBlock)
		{
			controlBlock->nativeReferenceCount += 1;
			controlBlock->allReferenceCount += 1;
		}

		void BaseResource::BaseControlBlock::AddManagedReference(BaseControlBlock* controlBlock)
		{
			controlBlock->allReferenceCount += 1;
		}

		void BaseResource::BaseControlBlock::RemoveNativeReference(BaseControlBlock*& controlBlock)
		{
			controlBlock->nativeReferenceCount -= 1;
			controlBlock->allReferenceCount -= 1;

			if (controlBlock->nativeReferenceCount == 0)
				controlBlock->DestroyData();

			if (controlBlock->allReferenceCount == 0)
			{
				delete controlBlock;
				controlBlock = nullptr;
			}
		}

		void BaseResource::BaseControlBlock::RemoveManagedReference(BaseControlBlock*& controlBlock)
		{
			controlBlock->allReferenceCount -= 1;
			if (controlBlock->allReferenceCount == 0)
			{
				delete controlBlock;
				controlBlock = nullptr;
			}
		}

		bool BaseResource::BaseControlBlock::IsResourceDestroyed() const
		{
			return this->nativeReferenceCount == 0;
		}

		BaseResource::BaseResource(BaseControlBlock* controlBlock) :
			controlBlock{ controlBlock }
		{
		}

		int BaseResource::GetAllReferenceCount() const
		{
			return this->controlBlock->GetAllReferenceCount();
		}

		int BaseResource::GetNativeReferenceCount() const
		{
			return this->controlBlock->GetNativeReferenceCount();
		}

		int BaseResource::GetManagedReferenceCount() const
		{
			return this->controlBlock->GetAllReferenceCount() - this->controlBlock->GetNativeReferenceCount();
		}

		bool BaseResource::operator == (nullptr_t) const
		{
			return this->controlBlock == nullptr;
		}

		bool BaseResource::operator != (nullptr_t) const
		{
			return this->controlBlock != nullptr;
		}
	}
}