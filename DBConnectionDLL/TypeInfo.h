#pragma once
#include <vector>
#include <map>
#include <string>
#include <typeinfo>

class Property;


template <typename T>
struct TypeInfoInitializer
{
public:
	TypeInfoInitializer(const wchar_t* name)
		: m_name(name)
	{
	}

	const wchar_t* m_name = nullptr;
};

class TypeInfo
{
public:
	template <typename T>
	explicit TypeInfo(const TypeInfoInitializer<T>& initializer)
		: m_typeHash(typeid(T).hash_code()), m_name(initializer.m_name)//, m_fullName(typeid(T).name())
	{
	}

	const std::vector<const Property*>& GetProperties() const
	{
		return m_properties;
	}

	const Property* GetProperty(const wchar_t* name) const;

private:
	friend Property;

	void AddProperty(const Property* property);

	size_t m_typeHash;

	std::vector<const Property*> m_properties;
	std::map<std::wstring, const Property*> m_propertyMap;
	const wchar_t* m_name = nullptr;
};



#define GENERATE_CLASS_TYPE_INFO( TypeName )	\
private:	\
	friend TypeInfoInitializer<TypeName>; \
\
public:	\
	using ThisType = TypeName;	\
\
\
	static TypeInfo& StaticTypeInfo()	\
	{	\
		static TypeInfo typeInfo(TypeInfoInitializer<ThisType>{ L#TypeName }); \
		return typeInfo;\
	}	\
	virtual const TypeInfo& GetTypeInfo() const	\
	{	\
		return m_typeInfo;	\
	}	\
\
private: \
	inline static TypeInfo& m_typeInfo = StaticTypeInfo();	\
\

