#include "pch.h"
#include "SQLReader.h"
#include <cassert>
#include <time.h>

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
		case SQL_C_CHAR:
			SQLResult<std::string> strResult();
			this->m_sqlResult.insert(strResult);
			break;
		case SQL_C_LONG:
			SQLResult<int> intResult();
			this->m_sqlResult.insert(intResult);
			break;
		case SQL_C_DOUBLE:
			SQLResult<float> floatResult();
			this->m_sqlResult.insert(floatResult);
			break;
		case SQL_C_DATE:
			SQLResult<time_t> timeResult();
			this->m_sqlResult.insert(timeResult);
			break;
		default:
			static_assert(true, "none support type");
		}
	}

	return false;
}
