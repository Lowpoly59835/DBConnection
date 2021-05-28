#pragma once
#include "type.h"

namespace NetworkCommon
{
	namespace DBConnection
	{
		template<typename T>
		class DBCONNECTIONDLL_EXPORTS DBRecord
		{
		public:
			DBRecord()
			{
				static_assert(check_type<T>::value, "DB Record type error!!");
			}

			friend class SQLReader;

		private:
			T _value;
		public:
			PROPERT_GETEX(_value, T, value)
		};

		class DBCONNECTIONDLL_EXPORTS DBTable
		{

		};
	}
}