#include "pch.h"
#include "SQLReader.h"

NetworkCommon::DBConnection::SQLReader::SQLReader(SQLHSTMT& hStmt)
	:m_resultStmt(hStmt)
{
}

NetworkCommon::DBConnection::SQLReader::SQLReader(const SQLReader&& other)
{
	m_resultStmt = other.m_resultStmt;
}

NetworkCommon::DBConnection::SQLReader::~SQLReader()
{
}
