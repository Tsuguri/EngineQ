#ifndef UTILITIES_OBJECT_DESTRUCTOR_HPP
#define UTILITIES_OBJECT_DESTRUCTOR_HPP


namespace Utilities
{
	template<typename TType, bool>
	struct ObjectDestructorHelper
	{
		inline static void Destruct(TType& object)
		{
		}
	};

	template<typename TType>
	struct ObjectDestructorHelper<TType, true>
	{
		inline static void Destruct(TType& object)
		{
			object.~TType();
		}
	};

	template<typename TType>
	struct ObjectDestructor
	{
		inline static void Destruct(TType& object)
		{
			ObjectDestructorHelper<TType, std::is_destructible<TType>::value>::Destruct(object);
		}
	};
}

#endif // !UTILITIES_OBJECT_DESTRUCTOR_HPP