#pragma once
#include <unordered_map>
#include "CustomString.h"

namespace NetworkCommon
{
	namespace DBConnection
	{
		typedef DBCONNECTIONDLL_EXPORTS_DECLSPEC struct st_hash_custom_string
		{
			unsigned long long operator() (const CustomString& value) const;
		}HashCustomString;
	}
}