#pragma once
#include "TypeInfo.h"


class PropertyHandlerBase
{
	GENERATE_CLASS_TYPE_INFO(PropertyHandlerBase)
public:
	virtual ~PropertyHandlerBase() = default;
};

template <typename T>
class IPropertyHandler : public PropertyHandlerBase
{
	GENERATE_CLASS_TYPE_INFO(IPropertyHandler)
		using ElementType = std::remove_all_extents_t<T>;

public:
	virtual ElementType& Get(void* object, size_t index = 0) const = 0;
	virtual void Set(void* object, const ElementType& value, size_t index = 0) const = 0;
};

template <typename TClass, typename T>
class PropertyHandler : public IPropertyHandler<T>
{
	GENERATE_CLASS_TYPE_INFO(PropertyHandler)
		using ElementType = std::remove_all_extents_t<T>;
	using MemberPtr = T TClass::*;

public:
	virtual ElementType& Get(void* object, size_t index = 0) const override
	{
		if constexpr (std::is_array_v<T>)
		{
			return (static_cast<TClass*>(object)->*m_ptr)[index];
		}
		else
		{
			return static_cast<TClass*>(object)->*m_ptr;
		}
	}

	virtual void Set(void* object, const ElementType& value, size_t index = 0) const override
	{
		if constexpr (std::is_array_v<T>)
		{
			(static_cast<TClass*>(object)->*m_ptr)[index] = value;
		}
		else
		{
			static_cast<TClass*>(object)->*m_ptr = value;
		}
	}

	void Set(void* object, const T* value, size_t length) const
	{
		memcpy(&(static_cast<TClass*>(object)->*m_ptr), value, length);
	}

	explicit PropertyHandler(MemberPtr ptr)
		: m_ptr(ptr)
	{
	}

private:
	MemberPtr m_ptr = nullptr;
};


struct PropertyInitializer
{
	const wchar_t* m_name = nullptr;
	const TypeInfo& m_type;
	const PropertyHandlerBase& m_handler;

	PropertyInitializer(const wchar_t* name, TypeInfo& type, PropertyHandlerBase& handler)
		:m_name(name), m_type(type), m_handler(handler)
	{

	}
};

class Property
{
public:
	const wchar_t* GetName() const
	{
		return m_name;
	}

	template <typename T>
	struct ReturnValueWrapper
	{
	public:
		explicit ReturnValueWrapper(T& value) :
			m_value(&value)
		{

		}
		ReturnValueWrapper() = default;

		ReturnValueWrapper& operator=(const T& value)
		{
			*m_value = value;
			return *this;
		}

		operator T& ()
		{
			return *m_value;
		}

	private:
		T* m_value = nullptr;
	};

	template <typename TClass, typename T>
	ReturnValueWrapper<T> Get(void* object) const
	{
		auto concreteHandler = static_cast<const PropertyHandler<TClass, T>&>(m_handler);
		return ReturnValueWrapper(concreteHandler.Get(object));
	}

	template <typename T>
	ReturnValueWrapper<T> Get(void* object) const
	{
		auto concreteHandler = static_cast<const IPropertyHandler<T>*>(&m_handler);
		return ReturnValueWrapper(concreteHandler->Get(object));
	}

	template <typename TClass, typename T>
	void Set(void* object, const T& value) const
	{
		auto concreteHandler = static_cast<const PropertyHandler<TClass, T>&>(m_handler);
		concreteHandler.Set(object, value);
	}

	template <typename TClass, typename T>
	void Set(void* object, const T& value, size_t length) const
	{
		auto concreteHandler = static_cast<const PropertyHandler<TClass, T>&>(m_handler);
		concreteHandler.Set(object, &value, length);
	}

	Property(TypeInfo& owner, const PropertyInitializer& initializer, const type_info& info)
		: m_name(initializer.m_name),
		m_type(initializer.m_type),
		m_handler(initializer.m_handler),
		value_typeInfo(info.hash_code())
	{
		owner.AddProperty(this);
	}

private:
	const wchar_t* m_name = nullptr;
	const TypeInfo& m_type;
	const PropertyHandlerBase& m_handler;
	const size_t value_typeInfo;
};


template <typename TClass, typename T, typename TPtr, TPtr ptr>
class PropertyRegister
{
public:
	PropertyRegister(const wchar_t* name, TypeInfo& typeInfo)
	{
		static PropertyHandler<TClass, T> handler(ptr);
		static PropertyInitializer intializer(name, typeInfo, handler);
		static Property property(typeInfo, intializer, typeid(T));
	}
};

#define PROPERTYEX( Value, PropertyName, ... )	\
	inline static struct RegistPropertyExecutor_##Value	\
	{	\
		RegistPropertyExecutor_##Value()	\
		{	\
			static PropertyRegister<ThisType, decltype(##Value), decltype(&ThisType::##Value), &ThisType::##Value> property_register_##Value{ L#PropertyName, ThisType::StaticTypeInfo(), __VA_ARGS__ }; \
		}	\
		\
	} regist_##Value;



