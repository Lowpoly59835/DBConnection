#include "pch.h"
#include "HashFunc.h"

std::size_t NetworkCommon::DBConnection::st_hash_custom_string::operator()(const CustomString& value) const
{
	CustomString& nonconst_value = const_cast<CustomString&>(value);
	return std::hash<std::string>()(nonconst_value.c_str());
}
