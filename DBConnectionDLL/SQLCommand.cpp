#include "pch.h"
#include "SQLCommand.h"
#include "SQLReader.h"
#include <exception>

using std::exception;
using NetworkCommon::DBConnection::SQLReader;

NetworkCommon::DBConnection::SQLCommand::SQLCommand(SQLConnection* connection, const wchar_t* command)
	:m_connection(connection), m_comannd(command), m_hStmt(NULL)
{
}

NetworkCommon::DBConnection::SQLCommand::~SQLCommand()
{
	if (m_hStmt) 
	{
		SQLFreeHandle(SQL_HANDLE_STMT, m_hStmt);
		m_hStmt = NULL;
	}
}

const SQLReader&& NetworkCommon::DBConnection::SQLCommand::Execute()
{
	{
		if (m_connection == nullptr)
		{
			throw exception("conntion is null");
		}
		else if (m_comannd.empty())
		{
			throw exception("command is empty");
		}


		RETCODE retCode = SQLAllocHandle(SQL_HANDLE_STMT, m_connection->m_connHanlde, &m_hStmt);

		if (retCode != SQL_SUCCESS)
		{
			throw exception(Format("Invalid stmt errorCode :  %d \n", retCode));
		}

		WCHAR* command = const_cast<WCHAR*>(m_comannd.c_str());

		retCode = SQLExecDirect(m_hStmt, command, SQL_NTS);

		if (retCode != SQL_SUCCESS)
		{
			throw exception(Format("Excute fail :  %d \n", retCode));
		}

	}

	return SQLReader(m_hStmt);
}
