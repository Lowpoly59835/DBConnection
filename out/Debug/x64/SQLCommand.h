#pragma once
#include "SQLConnection.h"
#include "SQLParameter.h"
#include <vector>

namespace NetworkCommon
{
	namespace DBConnection
	{
		class SQLReader;
		using std::vector; 
		
#pragma warning (disable : 4231)
#pragma warning( disable : 4251)
		EXPORT_INTERFACE_CLASS(vector<SQLParameter>);
#pragma warning (default : 4231) 
#pragma warning (default : 4251)

		class DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLCommand
		{

		public:
			SQLCommand() = delete;
			SQLCommand(SQLConnection* connection);
			SQLCommand(SQLConnection* connection, const wchar_t* strCommand);
			~SQLCommand();

		public:
			SQLReader Execute();
			SQLReader Execute(const wchar_t * command);

			void AddParameterWithValue(const char* parameterName, SQLSMALLINT type);
			void AddParameterWithOutput(const char* parameterName, SQLSMALLINT type);

		private:
			RETCODE ExecuteStatement(SQLHSTMT& hStmt);

		private:
			std::wstring m_command;
			SQLConnection* m_connection;
			
			vector<SQLParameter> m_pararmetersOutput;
			vector<SQLParameter> m_pararmeters;
		};
	}
}

