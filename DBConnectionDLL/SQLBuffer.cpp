#include "pch.h"
#include "SQLBuffer.h"
#include "IConnection.h"

NetworkCommon::DBConnection::SQLBuffer::SQLBuffer()
	:m_Type(EStorageType::None)
{
}

NetworkCommon::DBConnection::SQLBuffer::SQLBuffer(const SQLBuffer & other)
	:m_Data(other.m_Data), m_Type(other.m_Type), m_string(other.m_string)
{
}

NetworkCommon::DBConnection::SQLBuffer::SQLBuffer(SQLSMALLINT sqlType)
	:m_Type((EStorageType)sqlType)
{
	m_Data.Int = 0;
}


NetworkCommon::DBConnection::SQLBuffer::~SQLBuffer()
{
}

SQLRETURN NetworkCommon::DBConnection::SQLBuffer::Bind(SQLHSTMT& hstmt, int colpos)
{
	SQLLEN cid = 0;
	SQLRETURN result = 0;
	SQLLEN string_length = 0;

	switch (m_Type)
	{
	case EStorageType::Int:
		result = SQLBindCol(hstmt, colpos, SQL_INTEGER, &m_Data.Int, sizeof(m_Data.Int), &cid);
		break;
	case EStorageType::Float:
		result = SQLBindCol(hstmt, colpos, SQL_C_FLOAT, &m_Data.Float, sizeof(m_Data.Float), &cid);
		break;
	case EStorageType::String:
		if (!(result = IsSuccess(SQLColAttribute(hstmt, colpos, SQL_DESC_DISPLAY_SIZE, NULL, 0, NULL, &string_length))))
		{
			break;
		}
		result = SQLBindCol(hstmt, colpos, SQL_C_CHAR, SQLPOINTER(m_string.data()), (string_length + 1) * sizeof(WCHAR), &cid);
		break;
	case EStorageType::DateTime:
		result = SQLBindCol(hstmt, colpos, SQL_C_DATE, &m_Data.DateTime, sizeof(m_Data.DateTime), &cid);
		break;
	default:
		throw SQLException("unknown type", ESQLErrorCode::NO_SUPPORT_TYPE);
	}

	return result;
}


template<>
int NetworkCommon::DBConnection::SQLBuffer::GetValue() noexcept
{
	return m_Data.Int;
}

template<>
float NetworkCommon::DBConnection::SQLBuffer::GetValue() noexcept
{
	return m_Data.Float;
}

template<>
std::string NetworkCommon::DBConnection::SQLBuffer::GetValue() noexcept
{ 
	return m_string;
}

template<>
time_t NetworkCommon::DBConnection::SQLBuffer::GetValue() noexcept
{
	return m_Data.DateTime;
}
