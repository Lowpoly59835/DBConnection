#include "pch.h"
#include "SQLReader.h"
#include <cassert>

using std::list;
using namespace NetworkCommon::DBConnection;

SQLReader::SQLReader(SQLHSTMT& hStmt, std::list<SQLParameter>& pararmetersWithValue, std::list<SQLParameter>& pararmetersWithOutput)
	:m_hStmt(hStmt), m_pararmetersWithValue(pararmetersWithValue), m_pararmetersWithOutput(pararmetersWithOutput)
{
	assert(!(m_hStmt == NULL), "hStmt is null");
}

SQLReader::SQLReader(const SQLReader&& other)
	:m_hStmt(other.m_hStmt), m_pararmetersWithValue(other.m_pararmetersWithValue), m_pararmetersWithOutput(other.m_pararmetersWithOutput)
{
	assert(!(m_hStmt == NULL), "hStmt is null");
}

SQLReader::~SQLReader()
{
	if (m_hStmt)
	{
		SQLFreeHandle(SQL_HANDLE_STMT, m_hStmt);
		m_hStmt = NULL;
	}
}

bool SQLReader::Next()
{

	for (std::list<SQLParameter>::iterator it = m_pararmetersWithValue.begin(), int count = 1 ; it != m_pararmetersWithValue.end(); it++, count++)
	{
		switch (it->m_type)
		{

		}
	}

	return false;
}
