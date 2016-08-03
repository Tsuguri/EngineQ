#ifndef PROPERTY_H
#define PROPERTY_H

template<typename TType, typename TParent>
class BaseProperty
{
protected:
	TParent& parent;

public:
	using Type = TType;

	BaseProperty(TParent& parent)
		: parent{ parent }
	{
	}

	BaseProperty* operator&() = delete;
};


template<
	typename TType,
	typename TFun1,
	TFun1 Fun1,
	typename TFun2 = void*,
	TFun2 Fun2 = nullptr
>
class Property;


#pragma region Getter

// Fun1: val Getter
template<
	typename TType,
	typename TParent,
	TType(TParent::*Getter)()
>
class Property<TType, TType(TParent::*)(), Getter> : public BaseProperty<TType, TParent>
{
	using BaseProperty::BaseProperty;

public:
	inline operator TType()
	{
		return (parent.*Getter)();
	}
};

// Fun1: val Getter const
template<
	typename TParent,
	typename TType,
	TType(TParent::*Getter)() const
>
class Property<TType, TType(TParent::*)() const, Getter> : public BaseProperty<TType, TParent>
{
	using BaseProperty::BaseProperty;

public:
	inline operator TType() const
	{
		return (parent.*Getter)();
	}
};

#pragma endregion

#pragma region Setter

// Fun1: val Setter
template<
	typename TParent,
	typename TType,
	void(TParent::*Setter)(TType)
>
class Property<TType, void(TParent::*)(TType), Setter> : public BaseProperty<TType, TParent>
{
	using BaseProperty::BaseProperty;

public:
	inline void operator = (TType value)
	{
		(parent.*Setter)(value);
	}
};

// Fun1: const ref Setter
template<
	typename TParent,
	typename TType,
	void(TParent::*Setter)(const TType&)
>
class Property<TType, void(TParent::*)(const TType&), Setter> : public BaseProperty<TType, TParent>
{
	using BaseProperty::BaseProperty;

public:
	inline void operator = (const TType& value)
	{
		(parent.*Setter)(value);
	}
};

#pragma endregion

#pragma region Getter & Setter

// Fun1: val Getter
// Fun2: const ref Setter
template<
	typename TParent,
	typename TType,
	TType(TParent::*Getter)(),
	void(TParent::*Setter)(const TType&)
>
class Property<TType, TType(TParent::*)(), Getter, void(TParent::*)(const TType&), Setter> : public BaseProperty<TType, TParent>
{
	using BaseProperty::BaseProperty;

public:
	inline operator TType()
	{
		return (parent.*Getter)();
	}

	inline TType operator = (const TType& value)
	{
		(parent.*Setter)(value);
		return value;
	}
};

// Fun1: val Getter const
// Fun2: const ref Setter
template<
	typename TParent,
	typename TType,
	TType(TParent::*Getter)() const,
	void(TParent::*Setter)(const TType&)
>
class Property<TType, TType(TParent::*)() const, Getter, void(TParent::*)(const TType&), Setter> : public BaseProperty<TType, TParent>
{
	using BaseProperty::BaseProperty;

public:
	inline operator TType() const
	{
		return (parent.*Getter)();
	}

	inline TType operator = (const TType& value)
	{
		(parent.*Setter)(value);
		return value;
	}
};

// Fun1: const ref Setter
// Fun2: val Getter const
template<
	typename TParent,
	typename TType,
	void(TParent::*Setter)(const TType&),
	TType(TParent::*Getter)() const
>
class Property<TType, void(TParent::*)(const TType&), Setter, TType(TParent::*)() const, Getter> : public BaseProperty<TType, TParent>
{
	using BaseProperty::BaseProperty;

public:
	inline operator TType() const
	{
		return (parent.*Getter)();
	}

	inline TType operator = (const TType& value)
	{
		(parent.*Setter)(value);
		return value;
	}
};

// Fun1: const ref Setter
// Fun2: val Getter
template<
	typename TParent,
	typename TType,
	void(TParent::*Setter)(const TType&),
	TType(TParent::*Getter)()
>
class Property<TType, void(TParent::*)(const TType&), Setter, TType(TParent::*)(), Getter> : public BaseProperty<TType, TParent>
{
	using BaseProperty::BaseProperty;

public:
	inline operator TType()
	{
		return (parent.*Getter)();
	}

	inline TType operator = (const TType& value)
	{
		(parent.*Setter)(value);
		return value;
	}
};

// Fun1: val Getter
// Fun2: val Setter
template<
	typename TParent,
	typename TType,
	TType(TParent::*Getter)(),
	void(TParent::*Setter)(TType)
>
class Property<TType, TType(TParent::*)(), Getter, void(TParent::*)(TType), Setter> : public BaseProperty<TType, TParent>
{
	using BaseProperty::BaseProperty;

public:
	inline operator TType()
	{
		return (parent.*Getter)();
	}

	inline TType operator = (TType value)
	{
		(parent.*Setter)(value);
		return value;
	}
};

// Fun1: val Getter const
// Fun2: val Setter
template<
	typename TParent,
	typename TType,
	TType(TParent::*Getter)() const,
	void(TParent::*Setter)(TType)
>
class Property<TType, TType(TParent::*)() const, Getter, void(TParent::*)(TType), Setter> : public BaseProperty<TType, TParent>
{
	using BaseProperty::BaseProperty;

public:
	inline operator TType() const
	{
		return (parent.*Getter)();
	}

	inline TType operator = (TType value)
	{
		(parent.*Setter)(value);
		return value;
	}
};

// Fun1: val Setter
// Fun2: val Getter const
template<
	typename TParent,
	typename TType,
	void(TParent::*Setter)(TType),
	TType(TParent::*Getter)() const
>
class Property<TType, void(TParent::*)(TType), Setter, TType(TParent::*)() const, Getter> : public BaseProperty<TType, TParent>
{
	using BaseProperty::BaseProperty;

public:
	inline operator TType() const
	{
		return (parent.*Getter)();
	}

	inline TType operator = (TType value)
	{
		(parent.*Setter)(value);
		return value;
	}
};

// Fun1: val Setter
// Fun2: val Getter
template<
	typename TParent,
	typename TType,
	void(TParent::*Setter)(TType),
	TType(TParent::*Getter)()
>
class Property<TType, void(TParent::*)(TType), Setter, TType(TParent::*)(), Getter> : public BaseProperty<TType, TParent>
{
	using BaseProperty::BaseProperty;

public:
	inline operator TType()
	{
		return (parent.*Getter)();
	}

	inline TType operator = (TType value)
	{
		(parent.*Setter)(value);
		return value;
	}
};

#pragma endregion

#endif // !PROPERTY_H