#pragma once
#include <unordered_map>
#include "CustomString.h"

namespace NetworkCommon
{
	namespace DBConnection
	{
		typedef DBCONNECTIONDLL_EXPORTS_DECLSPEC class HashCustomString
		{
		public:
			std::size_t operator() (const CustomString& value) const;
		};
	}
}