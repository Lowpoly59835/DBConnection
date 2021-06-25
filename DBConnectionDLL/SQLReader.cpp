#include "pch.h"
#include "SQLReader.h"
#include <cassert>
#include <time.h>

using std::list;
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
