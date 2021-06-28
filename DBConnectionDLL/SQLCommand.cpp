#include "pch.h"
#include "SQLCommand.h"
#include "SQLReader.h"
#include <exception>
#include <utility>

using std::exception;
using NetworkCommon::DBConnection::SQLReader;
using std::make_pair;
using std::string;

NetworkCommon::DBConnection::SQLCommand::SQLCommand(SQLConnection * connection)
	:m_connection(connection)
{
}

NetworkCommon::DBConnection::SQLCommand::SQLCommand(SQLConnection* connection, const wchar_t* command)
	:m_connection(connection), m_command(command)
{
}

NetworkCommon::DBConnection::SQLCommand::~SQLCommand()
{
}

const SQLReader NetworkCommon::DBConnection::SQLCommand::Execute()
{
	if (m_connection == nullptr)
	{
		throw SQLException("conntion is null");
	}
	else if (m_command.empty())
	{
		throw SQLException("command is empty", ESQLErrorCode::INVALID);
	}


	SQLHSTMT hStmt = NULL;

	SQLRETURN retCode = SQLAllocHandle(SQL_HANDLE_STMT, m_connection->m_connHanlde, &hStmt);

	if (retCode != SQL_SUCCESS)
	{
		throw SQLException("execute error", ESQLErrorCode::ALLOC_HANDDLE_FAIL, retCode);
	}
	
	retCode = ExecuteStatement(hStmt);

	if (retCode != SQL_SUCCESS)
	{
		throw SQLException("execute error", ESQLErrorCode::EXECUTE_FAIL, retCode);
	}

		
	SQLSMALLINT cCols;

	retCode = SQLNumResultCols(hStmt, &cCols);

	if (!IsSuccess(retCode))
	{
		throw SQLException("execute error", ESQLErrorCode::EXECUTE_FAIL, retCode);
	}

	return SQLReader(*this, hStmt);
}

SQLRETURN NetworkCommon::DBConnection::SQLCommand::ExecuteStatement(SQLHSTMT& hStmt)
{
	WCHAR* command = const_cast<WCHAR*>(m_command.c_str());

	SQLRETURN retcode = SQLPrepare(hStmt, command, SQL_NTS);

	if (retcode != SQL_SUCCESS) 
	{
		return retcode;
	}

	 retcode = SQLExecute(hStmt);

	 return retcode;
}

const SQLReader NetworkCommon::DBConnection::SQLCommand::Execute(const wchar_t * command)
{
	m_command = command;

	return Execute();
}


void NetworkCommon::DBConnection::SQLCommand::AddParameterWithValue(const char * parameterName, char type)
{
	m_pararmetersWithValue.push_back(SQLParameter(parameterName, type));
}

void NetworkCommon::DBConnection::SQLCommand::AddParameterWithOutput(const char * parameterName, char type)
{
	m_pararmetersOutput.push_back(SQLParameter(parameterName, type));
}

NetworkCommon::DBConnection::SQLParameter::SQLParameter() 
	:m_name(), m_type()
{
}

NetworkCommon::DBConnection::SQLParameter::SQLParameter(const char * name, char type)
	:m_name(name), m_type(type)
{
	switch (m_type)
	{
	case SQL_C_CHAR:
		break;
	case SQL_C_LONG:
		break;
	case SQL_C_DOUBLE:
		break;
	case SQL_C_DATE:
		break;
	default:
		static_assert(true, "none support type");
		break;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

NetworkCommon::DBConnection::SQLParameter::SQLParameter(const SQLParameter& other)
	:m_name(other.m_name), m_type(other.m_type)
{
}

NetworkCommon::DBConnection::SQLParameter::~SQLParameter()
{
}
