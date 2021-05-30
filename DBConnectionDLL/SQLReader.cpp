#include "pch.h"
#include "SQLReader.h"
#include <cassert>
#include <time.h>

using std::list;
using namespace NetworkCommon::DBConnection;

SQLReader::SQLReader(SQLHSTMT& hStmt, std::list<SQLParameter>& pararmetersWithValue, std::list<SQLParameter>& pararmetersWithOutput)
	:m_hStmt(hStmt), m_pararmetersWithValue(pararmetersWithValue), m_pararmetersWithOutput(pararmetersWithOutput)
{
	assert(!(m_hStmt == NULL));
	SetResult();
}

SQLReader::SQLReader(const SQLReader&& other)
	:m_hStmt(other.m_hStmt), m_pararmetersWithValue(other.m_pararmetersWithValue), m_pararmetersWithOutput(other.m_pararmetersWithOutput)
{
	assert(!(m_hStmt == NULL));
	SetResult();
}

SQLReader::~SQLReader()
{
	if (m_hStmt)
	{
		SQLFreeHandle(SQL_HANDLE_STMT, m_hStmt);
		m_hStmt = NULL;
	}
}

void NetworkCommon::DBConnection::SQLReader::SetResult()
{
	for (list<SQLParameter>::iterator it = m_pararmetersWithValue.begin(); it != m_pararmetersWithValue.end(); it++)
	{
		ISQLResult* sqlResult = nullptr;

		switch (it->m_type)
		{
		case SQL_C_CHAR:
			sqlResult = new SQLResult<std::string>();
			//m_sqlResult.push_back(ISQLResult());
			break;
		case SQL_C_LONG:
			sqlResult = new SQLResult<int>();
			break;
		case SQL_C_DOUBLE:
			sqlResult = new SQLResult<float>();
			break;
		case SQL_C_DATE:
			sqlResult = new SQLResult<time_t>();
			break;
		default:
			assert(true);
		}

		m_sqlResult.push_back(sqlResult);
	}
}
