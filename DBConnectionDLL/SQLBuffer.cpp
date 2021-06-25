#include "pch.h"
#include "SQLBuffer.h"

NetworkCommon::DBConnection::SQLBuffer::SQLBuffer()
	:m_Type(EStorageType::None)
{
}

NetworkCommon::DBConnection::SQLBuffer::SQLBuffer(const SQLBuffer & other)
	:m_Data(other.m_Data), m_Type(other.m_Type), m_string(other.m_string)
{
}

NetworkCommon::DBConnection::SQLBuffer::SQLBuffer(EStorageType type)
	:m_Type(type)
{
	m_Data.Int = 0;
}

NetworkCommon::DBConnection::SQLBuffer::~SQLBuffer()
{
}

SQLRETURN NetworkCommon::DBConnection::SQLBuffer::Bind(SQLHSTMT& hstmt, int colpos, SQLLEN string_length)

{
	if (hstmt == NULL)
	{
		return;
	}

	SQLLEN cid;
	SQLRETURN result;

	switch (m_Type)
	{
	case EStorageType::Int:
		result = SQLBindCol(hstmt, colpos, SQL_INTEGER, &m_Data.Int, sizeof(m_Data.Int), &cid);
		break;
	case EStorageType::Float:
		result = SQLBindCol(hstmt, colpos, SQL_C_FLOAT, &m_Data.Float, sizeof(m_Data.Float), &cid);
		break;
	case EStorageType::String:
		result = SQLBindCol(hstmt, colpos, SQL_C_TCHAR, SQLPOINTER(m_string.data()), (string_length + 1) * sizeof(TCHAR), &cid)), & cid);
		break;
	case EStorageType::DateTime:
		result = SQLBindCol(hstmt, colpos, SQL_C_DATE, &m_Data.DateTime, sizeof(m_Data.DateTime), &cid);
		break;
	default:
		throw exception("unknown type");
	}

	return result;
}