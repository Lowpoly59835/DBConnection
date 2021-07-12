#pragma once
#include "SQLBuffer.h"
namespace NetworkCommon
{
	namespace DBConnection
	{
#pragma warning (disable : 4231)
#pragma warning( disable : 4251)
		EXPORT_STL_STRING(char);
#pragma warning (default : 4231) 
#pragma warning (default : 4251)

		class DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLParameter
		{
		public:
			SQLParameter() = default;
			SQLParameter& operator=(const SQLParameter&) = default;
			SQLParameter(const SQLParameter&) = default;

			SQLParameter(SQLSMALLINT type);
			SQLParameter(const char* name, SQLSMALLINT type);
			~SQLParameter();

		private:
			friend class SQLCommand;

			RETCODE BindParmeter(SQLHSTMT& hstmt, int colpos, SQLSMALLINT bindType);

		private:
			SQLBuffer m_buffer;
			std::string m_name;
		};
	}
}