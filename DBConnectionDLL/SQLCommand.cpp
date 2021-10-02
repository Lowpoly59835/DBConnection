#include "pch.h"
#include "SQLCommand.h"
#include "SQLReader.h"
#include <exception>
#include <utility>
#include <algorithm>

using std::exception;
using NetworkCommon::DBConnection::SQLReader;
using NetworkCommon::DBConnection::SQLParameter;
using NetworkCommon::DBConnection::SQLException;
using std::make_pair;
using std::string;
using std::vector;

NetworkCommon::DBConnection::SQLCommand::SQLCommand(SQLConnection* connection)
	:m_connection(connection)
{
}

NetworkCommon::DBConnection::SQLCommand::SQLCommand(SQLConnection* connection, const wchar_t* command)
	: m_connection(connection), m_command(command)
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


	for (int i = 0; i < m_pararmeters.size(); i++)
	{
		m_pararmeters[i].BindParmeter(hStmt, i + 1,  SQL_PARAM_INPUT);
	}

	for (int i = 0; i < m_pararmetersOutput.size(); i++)
	{
		m_pararmetersOutput[i].BindParmeter(hStmt, i + m_pararmeters.size() + 1, SQL_PARAM_OUTPUT);
	}
	
	retcode = SQLExecute(hStmt);

	return retcode;
}


SQLReader NetworkCommon::DBConnection::SQLCommand::Execute(const wchar_t* command)
{
	m_command = command;

	return Execute();
}


SQLParameter* NetworkCommon::DBConnection::SQLCommand::AddParameter(const char* parameterName, SQLSMALLINT type)
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


SQLParameter* NetworkCommon::DBConnection::SQLCommand::AddOutputParameter(const char* parameterName, SQLSMALLINT type)
{
	auto& result = m_pararmetersOutput.emplace_back(SQLParameter(parameterName, type));

	return &result;
}
/*

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
*/



template<>
int NetworkCommon::DBConnection::SQLCommand::GetParameterOutputValue(const char* colName)
{
	//std::wstring wColName = ToWString(colName);

	for (auto& it : m_pararmetersOutput)
	{
		//if(wColName.compare(it.first.c_wstr()) == 0)
		//if (wcscmp(it.first.c_wstr(), wColName.c_str()) == 0)
		if (strcmp(it.m_name.c_str(), colName) == 0)
		{
			return *static_cast<int*>(it.m_buffer.GetBuffer());
		}
	}

	throw SQLException("not exists colums");
}


template<>
float NetworkCommon::DBConnection::SQLCommand::GetParameterOutputValue(const char* colName)
{
	//std::wstring wColName = ToWString(colName);

	for (auto& it : m_pararmetersOutput)
	{
		if (strcmp(it.m_name.c_str(), colName) == 0)
		{
			return *static_cast<float*>(it.m_buffer.GetBuffer());
		}
	}

	throw SQLException("not exists colums");
}

template<>
std::string NetworkCommon::DBConnection::SQLCommand::GetParameterOutputValue(const char* colName)
{
	//std::wstring wColName = ToWString(colName);

	for (auto& it : m_pararmetersOutput)
	{
		if (strcmp(it.m_name.c_str(), colName) == 0)
		{			
			return static_cast<CustomString*>(it.m_buffer.GetBuffer())->c_str();
		}
	}

	throw SQLException("not exists colums");
}

template<>
TIMESTAMP_STRUCT NetworkCommon::DBConnection::SQLCommand::GetParameterOutputValue(const char* colName)
{
	//std::wstring wColName = ToWString(colName);

	for (auto& it : m_pararmetersOutput)
	{
		if (strcmp(it.m_name.c_str(), colName) == 0)
		{
			return *static_cast<TIMESTAMP_STRUCT*>(it.m_buffer.GetBuffer());
		}
	}

	throw SQLException("not exists colums");
}

/// 초단위까지만 지원
/// 밀리세컨드는 따로 변환해야함
template<>
tm NetworkCommon::DBConnection::SQLCommand::GetParameterOutputValue(const char* colName)
{
	TIMESTAMP_STRUCT timestamp = GetParameterOutputValue<TIMESTAMP_STRUCT>(colName);

	return TotmFromTimeStamp(timestamp);
}

