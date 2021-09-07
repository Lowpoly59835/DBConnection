#pragma once
#include "SQLBuffer.h"
#include "CustomString.h"

namespace NetworkCommon
{
	namespace DBConnection
	{
		class DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLParameter
		{
		public:
			SQLParameter() = default;
			SQLParameter(const SQLParameter&) = default;

			SQLParameter(SQLSMALLINT type);
			SQLParameter(const char* name, SQLSMALLINT type);
			~SQLParameter();

			void operator=(int value);
			void operator=(long long value);
			void operator=(float value);
			void operator=(const char* value);
			void operator=(std::string& value);
			void operator=(TIMESTAMP_STRUCT& value);

		private:
			friend class SQLCommand;

			RETCODE BindParmeter(SQLHSTMT& hstmt, int colpos, SQLSMALLINT bindType);

		private:
			SQLBuffer m_buffer;
			CustomString m_name;
		};
	}
}