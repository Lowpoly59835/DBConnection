#include "pch.h"
#include "SQLReader.h"
#include <cassert>
#include <time.h>
#include <algorithm>

using std::vector;
using namespace NetworkCommon::DBConnection;


SQLReader::SQLReader(SQLCommand& command, SQLHSTMT hStmt)
	:m_command(command), m_hStmt(hStmt)
{
	assert(!(m_hStmt == NULL));
}


SQLReader::SQLReader(const SQLReader&& other)
	:m_command(other.m_command), m_hStmt(other.m_hStmt)
{
	assert(!(m_hStmt == NULL));
}

SQLReader::~SQLReader()
{
	if (m_hStmt)
	{
		SQLFreeHandle(SQL_HANDLE_STMT, m_hStmt);
		m_hStmt = NULL;
	}
}

bool NetworkCommon::DBConnection::SQLReader::Next() noexcept
{


	return false;
}

//https://gist.github.com/bombless/6a71da1ed3e6b0b7d404 148 ∂Û¿Œ
void NetworkCommon::DBConnection::SQLReader::bind()
{
	if (m_hStmt == NULL)
	{
		throw std::exception("Handle is null");
	}

	SQLSMALLINT cCols;

	if (!success(SQLNumResultCols(m_hStmt, &cCols))
	{

	}

	for (auto& it : m_command.ParameterWithValues)
	{


		SQLBuffer buffer((SQLBuffer::EStorageType)it.m_type);
		buffer.Bind()
	}
}
