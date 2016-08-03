#ifndef PROPERTY_H
#define PROPERTY_H

template<typename TParent>
class InstanceProperty : EngineQ::Utilities::Immovable
{
protected:
	TParent& parent;

public:
	InstanceProperty(TParent& parent)
		: parent{ parent }
	{
	}

	InstanceProperty* operator&() = delete;
};


template<
	typename TType,
	typename TFun1,
	TFun1 Fun1,
	typename TFun2 = void*,
	TFun2 Fun2 = nullptr
>
class Property;

#pragma region Static

#pragma region Getter

// Fun1: static val Getter
template<
	typename TType,
	TType(*Getter)()
>
class Property<TType, TType(*)(), Getter>
{
public:
	inline operator TType() const
	{
		return Getter();
	}
	
	inline const TType operator ()() const
	{
		return *this;
	}
};

#pragma endregion

#pragma endregion

#pragma region Instance

#pragma region Getter

// Fun1: val Getter
template<
	typename TType,
	typename TParent,
	TType(TParent::*Getter)()
>
class Property<TType, TType(TParent::*)(), Getter> : public InstanceProperty<TParent>
{
	using InstanceProperty::InstanceProperty;

public:
	inline operator TType()
	{
		return (parent.*Getter)();
	}

	inline const TType operator ()()
	{
		return *this;
	}
};

// Fun1: val Getter const
template<
	typename TParent,
	typename TType,
	TType(TParent::*Getter)() const
>
class Property<TType, TType(TParent::*)() const, Getter> : public InstanceProperty<TParent>
{
	using InstanceProperty::InstanceProperty;

public:
	inline operator TType() const
	{
		return (parent.*Getter)();
	}

	inline const TType operator ()() const
	{
		return *this;
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
class Property<TType, void(TParent::*)(TType), Setter> : public InstanceProperty<TParent>
{
	using InstanceProperty::InstanceProperty;

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
class Property<TType, void(TParent::*)(const TType&), Setter> : public InstanceProperty<TParent>
{
	using InstanceProperty::InstanceProperty;

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
class Property<TType, TType(TParent::*)(), Getter, void(TParent::*)(const TType&), Setter> : public InstanceProperty<TParent>
{
	using InstanceProperty::InstanceProperty;

public:
	inline operator TType()
	{
		return (parent.*Getter)();
	}

	inline const TType operator ()()
	{
		return *this;
	}

	inline const TType operator = (const TType& value)
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
class Property<TType, TType(TParent::*)() const, Getter, void(TParent::*)(const TType&), Setter> : public InstanceProperty<TParent>
{
	using InstanceProperty::InstanceProperty;

public:
	inline operator TType() const
	{
		return (parent.*Getter)();
	}

	inline const TType operator ()() const
	{
		return *this;
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
class Property<TType, void(TParent::*)(const TType&), Setter, TType(TParent::*)() const, Getter> : public InstanceProperty<TParent>
{
	using InstanceProperty::InstanceProperty;

public:
	inline operator TType() const
	{
		return (parent.*Getter)();
	}

	inline const TType operator ()() const
	{
		return *this;
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
class Property<TType, void(TParent::*)(const TType&), Setter, TType(TParent::*)(), Getter> : public InstanceProperty<TParent>
{
	using InstanceProperty::InstanceProperty;

public:
	inline operator TType()
	{
		return (parent.*Getter)();
	}

	inline const TType operator ()()
	{
		return *this;
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
class Property<TType, TType(TParent::*)(), Getter, void(TParent::*)(TType), Setter> : public InstanceProperty<TParent>
{
	using InstanceProperty::InstanceProperty;

public:
	inline operator TType()
	{
		return (parent.*Getter)();
	}

	inline const TType operator ()()
	{
		return *this;
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
class Property<TType, TType(TParent::*)() const, Getter, void(TParent::*)(TType), Setter> : public InstanceProperty<TParent>
{
	using InstanceProperty::InstanceProperty;

public:
	inline operator TType() const
	{
		return (parent.*Getter)();
	}

	inline const TType operator ()() const
	{
		return *this;
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
class Property<TType, void(TParent::*)(TType), Setter, TType(TParent::*)() const, Getter> : public InstanceProperty<TParent>
{
	using InstanceProperty::InstanceProperty;

public:
	inline operator TType() const
	{
		return (parent.*Getter)();
	}

	inline const TType operator ()() const
	{
		return *this;
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
class Property<TType, void(TParent::*)(TType), Setter, TType(TParent::*)(), Getter> : public InstanceProperty<TParent>
{
	using InstanceProperty::InstanceProperty;

public:
	inline operator TType()
	{
		return (parent.*Getter)();
	}

	inline const TType operator ()()
	{
		return *this;
	}

	inline TType operator = (TType value)
	{
		(parent.*Setter)(value);
		return value;
	}
};

#pragma endregion

#pragma endregion

#endif // !PROPERTY_H