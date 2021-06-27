#include "pch.h"
#include "SQLReader.h"
#include <cassert>
#include <time.h>
#include <algorithm>

using std::vector;
using namespace NetworkCommon::DBConnection;


SQLReader::SQLReader(SQLCommand& command, SQLHSTMT hStmt) noexcept
	:m_command(command), m_hStmt(hStmt), m_rowCount(0), m_hasValue(false)
{
	assert(!(m_hStmt == NULL));
	bind();
}


SQLReader::SQLReader(const SQLReader&& other) noexcept
	:m_command(other.m_command), m_hStmt(other.m_hStmt), m_rowCount(0), m_hasValue(false)
{
	assert(!(m_hStmt == NULL));
	bind();
}

SQLReader::~SQLReader()
{
	m_resultBuffer.clear();

	if (m_hStmt)
	{
		SQLFreeHandle(SQL_HANDLE_STMT, m_hStmt);
		m_hStmt = NULL;
	}
}

bool NetworkCommon::DBConnection::SQLReader::Next()
{
	SQLRETURN result = SQLFetch(m_hStmt);

	if (result != SQL_SUCCESS && result != SQL_NO_DATA)
	{
		throw SQLException("");
	}	

	m_hasValue = (result == SQL_SUCCESS ? true : false);

	return HasValue();
}

bool NetworkCommon::DBConnection::SQLReader::HasValue() noexcept
{
	return m_hasValue;
}

int NetworkCommon::DBConnection::SQLReader::RowCount() noexcept
{
	return m_rowCount;
}

//https://gist.github.com/bombless/6a71da1ed3e6b0b7d404 148 ∂Û¿Œ
void NetworkCommon::DBConnection::SQLReader::bind()
{
	m_resultBuffer.clear();

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
	else if (cCols != m_command.ParameterWithValues.size())
	{
		throw SQLException(Format("colums count not equles %d", m_command.ParameterWithValues.size()), ESQLErrorCode::COLUMNS_ERROR, result);
	}

	SQLLEN rowCount = 0;
	result = SQLRowCount(m_hStmt, &rowCount);

	if (!IsSuccess(result))
	{
		throw SQLException("get row count fail");
	}

	m_rowCount = rowCount;

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
			m_resultBuffer.clear();
			throw SQLException("", ESQLErrorCode::UNKNOWN, result);
		}

		m_resultBuffer.push_back({m_command.ParameterWithValues[i].m_name, buffer});
	}
}


template<>
int NetworkCommon::DBConnection::SQLReader::GetValue(const char* colName)
{
	for (auto& it : m_resultBuffer)
	{
		if (strcmp(it.first.c_str(), colName) == 0)
		{
			return it.second.GetValue<int>();
		}
	}

	throw SQLException("not exists colums", ESQLErrorCode::NOT_EXISTIS_COLUM);
}

template<>
float NetworkCommon::DBConnection::SQLReader::GetValue(const char* colName)
{
	for (auto& it : m_resultBuffer)
	{
		if (strcmp(it.first.c_str(), colName) == 0)
		{
			return it.second.GetValue<float>();
		}
	}

	throw SQLException("not exists colums", ESQLErrorCode::NOT_EXISTIS_COLUM);
}

template<>
std::string NetworkCommon::DBConnection::SQLReader::GetValue(const char* colName)
{
	for (auto& it : m_resultBuffer)
	{
		if (strcmp(it.first.c_str(), colName) == 0)
		{
			return it.second.GetValue<std::string>();
		}
	}

	throw SQLException("not exists colums", ESQLErrorCode::NOT_EXISTIS_COLUM);
}

template<>
time_t NetworkCommon::DBConnection::SQLReader::GetValue(const char* colName)
{
	for (auto& it : m_resultBuffer)
	{
		if (strcmp(it.first.c_str(), colName) == 0)
		{
			return it.second.GetValue<time_t>();
		}
	}

	throw SQLException("not exists colums", ESQLErrorCode::NOT_EXISTIS_COLUM);

}
