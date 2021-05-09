#pragma once
#include "SQLConnection.h"

namespace NetworkCommon
{
	namespace DBConnection
	{
		class SQLReader;

		class DBCONNECTIONDLL_EXPORTS SQLCommand
		{

		public:
			SQLCommand() = delete;
			SQLCommand(SQLConnection* connection, const wchar_t* strConnection);
			~SQLCommand();

		public:
			const SQLReader&& Execute();

		private:
			std::wstring m_comannd;
			SQLConnection* m_connection;
			SQLHSTMT m_hStmt;
		};
	}
}

