#include "pch.h"
#include "SQLCommand.h"
#include "SQLReader.h"
#include <exception>
#include <utility>

using std::exception;
using NetworkCommon::DBConnection::SQLReader;
using NetworkCommon::DBConnection::SQLParameter;
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

SQLReader NetworkCommon::DBConnection::SQLCommand::Execute()
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

	for (int i = 0 ; i < m_pararmeters.size() ; i++)
	{
		m_pararmeters[i].BindParmeter(hStmt, i + 1, SQL_PARAM_INPUT);
	}

	for (int i = 0; i < m_pararmetersOutput.size(); i++)
	{
		m_pararmetersOutput[i].BindParmeter(hStmt, i + m_pararmeters.size() + 1, SQL_PARAM_OUTPUT);
	}
	 retcode = SQLExecute(hStmt);

	 return retcode;
}


SQLReader NetworkCommon::DBConnection::SQLCommand::Execute(const wchar_t * command)
{
	m_command = command;

	return Execute();
}


SQLParameter* NetworkCommon::DBConnection::SQLCommand::AddParameter(const char * parameterName, SQLSMALLINT type)
{
	auto& result = m_pararmeters.emplace_back(SQLParameter(parameterName, type));

	return &result;
}

SQLParameter* NetworkCommon::DBConnection::SQLCommand::AddParameterWithValue(const char* parameterName, SQLSMALLINT type, int value)
{
	auto& result = m_pararmeters.emplace_back(SQLParameter(parameterName, type));

	result = value;

	return &result;
}

SQLParameter* NetworkCommon::DBConnection::SQLCommand::AddParameterWithValue(const char* parameterName, SQLSMALLINT type, float value)
{
	auto& result = m_pararmeters.emplace_back(SQLParameter(parameterName, type));

	result = value;

	return &result;
}

SQLParameter* NetworkCommon::DBConnection::SQLCommand::AddParameterWithValue(const char* parameterName, SQLSMALLINT type, std::string value)
{
	auto& result = m_pararmeters.emplace_back(SQLParameter(parameterName, type));

	result = value;

	return &result;
}

SQLParameter* NetworkCommon::DBConnection::SQLCommand::AddParameterWithValue(const char* parameterName, SQLSMALLINT type, TIMESTAMP_STRUCT value)
{
	auto& result = m_pararmeters.emplace_back(SQLParameter(parameterName, type));

	result = value;

	return &result;
}


SQLParameter* NetworkCommon::DBConnection::SQLCommand::AddOutputParameter(const char * parameterName, SQLSMALLINT type)
{
	auto& result = m_pararmetersOutput.emplace_back(SQLParameter(parameterName, type));

	return &result;
}

SQLParameter* NetworkCommon::DBConnection::SQLCommand::AddOutputParameterWithValue(const char* parameterName, SQLSMALLINT type, int value)
{
	auto& result = m_pararmetersOutput.emplace_back(SQLParameter(parameterName, type));

	result = value;

	return &result;
}

SQLParameter* NetworkCommon::DBConnection::SQLCommand::AddOutputParameterWithValue(const char* parameterName, SQLSMALLINT type, float value)
{
	auto& result = m_pararmetersOutput.emplace_back(SQLParameter(parameterName, type));

	result = value;

	return &result;
}

SQLParameter* NetworkCommon::DBConnection::SQLCommand::AddOutputParameterWithValue(const char* parameterName, SQLSMALLINT type, std::string value)
{
	auto& result = m_pararmetersOutput.emplace_back(SQLParameter(parameterName, type));

	result = value;

	return &result;
}

SQLParameter* NetworkCommon::DBConnection::SQLCommand::AddOutputParameterWithValue(const char* parameterName, SQLSMALLINT type, TIMESTAMP_STRUCT value)
{
	auto& result = m_pararmetersOutput.emplace_back(SQLParameter(parameterName, type));

	result = value;

	return &result;
}
