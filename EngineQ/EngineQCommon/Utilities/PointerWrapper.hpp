#ifndef UTILITIES_POINTER_WRAPPER_HPP
#define UTILITIES_POINTER_WRAPPER_HPP

namespace Utilities
{
	template<typename TType>
	class PointerWrapper
	{
	private:
		TType* pointer = nullptr;

	public:
		PointerWrapper() = default;
		PointerWrapper(TType* pointer) :
			pointer{ pointer }
		{
		}

		TType& operator* ()
		{
			return *this->pointer;
		}

		const TType& operator* () const
		{
			return *this->pointer;
		}

		TType* operator -> ()
		{
			return this->pointer;
		}

		const TType* operator -> () const
		{
			return this->pointer;
		}

		operator TType* ()
		{
			return this->pointer;
		}

		operator const TType* () const
		{
			return this->pointer;
		}
	};
}

#endif // !UTILITIES_POINTER_WRAPPER_HPP
