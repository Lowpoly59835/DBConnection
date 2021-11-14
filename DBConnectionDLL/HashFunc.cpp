#include "pch.h"
#include "HashFunc.h"

std::size_t NetworkCommon::DBConnection::HashCustomString::operator()(const CustomString& value) const
{
	CustomString& nonconst_value = const_cast<CustomString&>(value);
	return std::hash<std::string>()(nonconst_value.c_str());
}
