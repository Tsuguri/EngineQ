#include "Resource.hpp"

namespace EngineQ
{
	namespace Resources
	{
		BaseResource::BaseContainer::BaseContainer(Scripting::ScriptEngine& scriptEngine, Scripting::ScriptClass resourceClass, ControlBlock* controlBlock) :
			Object{ scriptEngine, resourceClass }, controlBlock{ controlBlock }
		{
		}

		int BaseResource::BaseContainer::GetReferenceCount() const
		{
			return this->controlBlock->referenceCount;
		}

		int BaseResource::BaseContainer::GetManagedReferenceCount() const
		{
			return this->controlBlock->managedReferenceCount;
		}

		void BaseResource::Remove()
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

		void BaseResource::Add()
		{
			if (this->controlBlock == nullptr)
				return;

			this->controlBlock->referenceCount += 1;
		}

		BaseResource::BaseResource(ControlBlock* controlBlock, BaseContainer* container) :
			controlBlock{ controlBlock }, container{ container }
		{
		}

		bool BaseResource::operator == (nullptr_t) const
		{
			return this->controlBlock == nullptr;
		}

		bool BaseResource::operator != (nullptr_t) const
		{
			return this->controlBlock != nullptr;
		}

		int BaseResource::GetReferenceCount() const
		{
			if (this->controlBlock == nullptr)
				return 0;

			return this->controlBlock->referenceCount;
		}

		int BaseResource::GetManagedReferenceCount() const
		{
			if (this->controlBlock == nullptr)
				return 0;

			return this->controlBlock->managedReferenceCount;
		}
	}
}