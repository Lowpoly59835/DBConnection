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
	BufferClear();

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

//https://gist.github.com/bombless/6a71da1ed3e6b0b7d404 148 라인
void NetworkCommon::DBConnection::SQLReader::bind()
{
	if (!m_resultBuffer.empty())
	{
		BufferClear();
	}

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

	for (int i = 1; i <= cCols; i++)
	{
		SQLWCHAR      ColumnName[255] = L"";
		SQLSMALLINT   BufferLength = 0;
		SQLSMALLINT  NameLength = 0;
		SQLSMALLINT  DataType = 0;
		SQLULEN      ColumnSize = 0;
		SQLSMALLINT  DecimalDigits = 0;
		SQLSMALLINT   NullablePtr = SQL_NULLABLE_UNKNOWN;

		SQLRETURN describeColResult = SQLDescribeCol(m_hStmt, i, ColumnName, sizeof(ColumnName), &NameLength, &DataType, &ColumnSize, &DecimalDigits, &NullablePtr);

		if (!IsSuccess(describeColResult))
		{
			continue;
		}

		if (wcslen(ColumnName) == 0)
		{
			//문자열 길이가 0이라면, 다른 이름으로 치환해줘야할듯?
			//검색할떈 어떻하지?
		}

		m_resultBuffer.emplace_back(ColumnName, new SQLBuffer(DataType));


		SQLRETURN result = m_resultBuffer[i - 1].second->Bind(m_hStmt, i);

		if (!IsSuccess(result))
		{
			m_resultBuffer.clear();
			throw SQLException("", ESQLErrorCode::UNKNOWN, result);
		}
	}
}

void NetworkCommon::DBConnection::SQLReader::BufferClear()
{
	for (auto& it : m_resultBuffer)
	{
		delete it.second;
	}

	m_resultBuffer.clear();
}



template<>
int NetworkCommon::DBConnection::SQLReader::GetValue(const wchar_t* colName)
{
	for (auto& it : m_resultBuffer)
	{
		if (wcscmp(it.first.c_str(), colName) == 0)
		{
			return it.second->GetValue<int>();
		}
	}

	throw SQLException("not exists colums", ESQLErrorCode::NOT_EXISTIS_COLUM);
}

template<>
float NetworkCommon::DBConnection::SQLReader::GetValue(const wchar_t* colName)
{
	for (auto& it : m_resultBuffer)
	{
		if (wcscmp(it.first.c_str(), colName) == 0)
		{
			return it.second->GetValue<float>();
		}
	}

	throw SQLException("not exists colums", ESQLErrorCode::NOT_EXISTIS_COLUM);
}

template<>
std::string NetworkCommon::DBConnection::SQLReader::GetValue(const wchar_t* colName)
{
	for (auto& it : m_resultBuffer)
	{
		if (wcscmp(it.first.c_str(), colName) == 0)
		{
			return it.second->GetValue<std::string>();
		}
	}

	throw SQLException("not exists colums", ESQLErrorCode::NOT_EXISTIS_COLUM);
}

template<>
TIMESTAMP_STRUCT NetworkCommon::DBConnection::SQLReader::GetValue(const wchar_t* colName)
{
	for (auto& it : m_resultBuffer)
	{
		if (wcscmp(it.first.c_str(), colName) == 0)
		{
			return it.second->GetValue<TIMESTAMP_STRUCT>();
		}
	}

	throw SQLException("not exists colums", ESQLErrorCode::NOT_EXISTIS_COLUM);

}
