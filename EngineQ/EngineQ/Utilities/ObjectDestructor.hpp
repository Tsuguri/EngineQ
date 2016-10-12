#ifndef UTILITIES_OBJECT_DESTRUCTOR_HPP
#define UTILITIES_OBJECT_DESTRUCTOR_HPP

namespace Utilities
{
	template<typename TType, bool>
	struct ObjectDestructorHelper
	{
		static void Destruct(TType& object)
		{
		}
	};

	template<typename TType>
	struct ObjectDestructorHelper<TType, true>
	{
		static void Destruct(TType& object)
		{
			object.~TType();
		}
	};

	template<typename TType>
	struct ObjectDestructor
	{
		static void Destruct(TType& object)
		{
			ObjectDestructorHelper<TType, std::is_destructible<TType>::value>::Destruct(object);
		}
	};
}

#endif // !UTILITIES_OBJECT_DESTRUCTOR_HPP