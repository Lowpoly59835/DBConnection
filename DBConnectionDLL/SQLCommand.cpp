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
	else if (m_command.Empty())
	{
		throw SQLException("command is empty");
	}


	SQLHSTMT hStmt = NULL;

	SQLRETURN retCode = SQLAllocHandle(SQL_HANDLE_STMT, m_connection->m_connHanlde, &hStmt);

	if (retCode != SQL_SUCCESS)
	{
		throw SQLException(m_connection->m_connHanlde, SQL_HANDLE_STMT, retCode);
	}
	
	retCode = ExecuteStatement(hStmt);
	
	if (!IsSuccess(retCode))
	{
		throw SQLException(hStmt, SQL_HANDLE_STMT, retCode);
	}

	return SQLReader(*this, hStmt);
}

SQLRETURN NetworkCommon::DBConnection::SQLCommand::ExecuteStatement(SQLHSTMT& hStmt)
{
	std::wstring wstrCommand = ToWString(m_command.c_str());

	SQLRETURN retcode = SQLPrepare(hStmt, wstrCommand.data(), SQL_NTS);

	if (retcode != SQL_SUCCESS)
	{
		throw SQLException(m_connection->m_connHanlde, SQL_HANDLE_STMT, retcode);
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

SQLParameter* NetworkCommon::DBConnection::SQLCommand::AddParameterWithValue(const char* parameterName, SQLSMALLINT type, long long value)
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

SQLParameter* NetworkCommon::DBConnection::SQLCommand::AddParameterWithValue(const char* parameterName, SQLSMALLINT type, std::string& value)
{
	auto& result = m_pararmeters.emplace_back(SQLParameter(parameterName, type));

	result = value;

	return &result;
}

SQLParameter* NetworkCommon::DBConnection::SQLCommand::AddParameterWithValue(const char* parameterName, SQLSMALLINT type, TIMESTAMP_STRUCT& value)
{
	auto& result = m_pararmeters.emplace_back(SQLParameter(parameterName, type));

	result = value;

	return &result;
}

SQLParameter* NetworkCommon::DBConnection::SQLCommand::AddParameterWithValue(const char* parameterName, SQLSMALLINT type, tm& value)
{
	auto& result = m_pararmeters.emplace_back(SQLParameter(parameterName, type));

	TIMESTAMP_STRUCT st_tm = ToTimeStampFromtime_tm(value);

	result = st_tm;

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

SQLParameter* NetworkCommon::DBConnection::SQLCommand::AddOutputParameterWithValue(const char* parameterName, SQLSMALLINT type, long long value)
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

SQLParameter* NetworkCommon::DBConnection::SQLCommand::AddOutputParameterWithValue(const char* parameterName, SQLSMALLINT type, std::string& value)
{
	auto& result = m_pararmetersOutput.emplace_back(SQLParameter(parameterName, type));

	result = value;

	return &result;
}

SQLParameter* NetworkCommon::DBConnection::SQLCommand::AddOutputParameterWithValue(const char* parameterName, SQLSMALLINT type, TIMESTAMP_STRUCT& value)
{
	auto& result = m_pararmetersOutput.emplace_back(SQLParameter(parameterName, type));

	result = value;

	return &result;
}

SQLParameter* NetworkCommon::DBConnection::SQLCommand::AddOutputParameterWithValue(const char* parameterName, SQLSMALLINT type, tm& value)
{
	auto& result = m_pararmetersOutput.emplace_back(SQLParameter(parameterName, type));

	TIMESTAMP_STRUCT st_tm = ToTimeStampFromtime_tm(value);

	result = st_tm;

	return &result;
}
