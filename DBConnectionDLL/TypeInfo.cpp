#include "pch.h"
#include "TypeInfo.h"
#include "Property.h"


const Property* TypeInfo::GetProperty(const wchar_t* name) const
{
	auto iter = m_propertyMap.find(name);
	return (iter != std::end(m_propertyMap)) ? iter->second : nullptr;
}

void TypeInfo::AddProperty(const Property* property)
{
	m_properties.emplace_back(property);
	m_propertyMap.emplace(property->GetName(), property);
}
