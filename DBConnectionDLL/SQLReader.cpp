#include "pch.h"
#include "SQLReader.h"
#include <cassert>
#include <time.h>
#include <algorithm>

using std::vector;
using namespace NetworkCommon::DBConnection;


SQLReader::SQLReader(SQLCommand& command, SQLHSTMT hStmt) noexcept
	:m_command(command), m_hStmt(hStmt)
{
	assert(!(m_hStmt == NULL));
	bind();
}


SQLReader::SQLReader(const SQLReader&& other) noexcept
	:m_command(other.m_command), m_hStmt(other.m_hStmt)
{
	assert(!(m_hStmt == NULL));
	bind();
}

SQLReader::~SQLReader()
{
	m_sqlResult.clear();

	if (m_hStmt)
	{
		SQLFreeHandle(SQL_HANDLE_STMT, m_hStmt);
		m_hStmt = NULL;
	}
}

bool NetworkCommon::DBConnection::SQLReader::Next() noexcept
{
	SQLRETURN result = SQLFetch(m_hStmt);

	if (result != SQL_SUCCESS && result != SQL_NO_DATA)
	{
		throw SQLException("");
	}	

	return result == SQL_SUCCESS ? true : false;
}

void NetworkCommon::DBConnection::SQLReader::GetValue(const char* colName) noexcept
{
	//m_sqlResult.
	for (auto& it : m_command.ParameterWithValues)
	{
		if (strcmp(it.m_name.c_str(), colName) == 0)
		{

		}
	}
}

//https://gist.github.com/bombless/6a71da1ed3e6b0b7d404 148 ∂Û¿Œ
void NetworkCommon::DBConnection::SQLReader::bind()
{
	m_sqlResult.clear();

	if (m_hStmt == NULL)
	{
		throw SQLException();
	}

	SQLSMALLINT cCols;
	SQLRETURN result = SQLNumResultCols(m_hStmt, &cCols);

	if (!IsSuccess(result))
	{
		throw SQLException("", ESQLErrorCode::UNKNOWN, result);
	}

	if (cCols != m_command.ParameterWithValues.size())
	{
		throw SQLException(Format("colums count not equles %d", m_command.ParameterWithValues.size()), ESQLErrorCode::COLUMNS_ERROR, result);
	}

	//for (auto& it : m_command.ParameterWithValues)
	for(int i = 0 ; i < cCols ; i++)
	{
		if (m_command.ParameterWithValues.size() > i)
		{
			break;
		}
		
		SQLBuffer buffer((SQLBuffer::EStorageType)m_command.ParameterWithValues[i].m_type);
		
		SQLRETURN result = buffer.Bind(m_hStmt, i);

		if (!IsSuccess(result))
		{
			m_sqlResult.clear();
			throw SQLException("", ESQLErrorCode::UNKNOWN, result);
		}

		m_sqlResult.push_back(buffer);
	}
}
