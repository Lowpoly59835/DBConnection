#include "pch.h"
#include "SQLBuffer.h"
#include "IConnection.h"

NetworkCommon::DBConnection::SQLBuffer::SQLBuffer()
	:m_type(EStorageType::None)
{
}

NetworkCommon::DBConnection::SQLBuffer::SQLBuffer(const SQLBuffer & other)
	: m_data(other.m_data), m_type(other.m_type), m_strData(other.m_strData)
{
}

NetworkCommon::DBConnection::SQLBuffer::SQLBuffer(SQLSMALLINT sqlType)
	: m_type((EStorageType)sqlType)
{
	m_data.Int = 0;
	if (sqlType == SQL_TIME || sqlType == SQL_TYPE_DATE || sqlType == SQL_TYPE_TIMESTAMP || sqlType == SQL_TYPE_TIME)
	{
		m_type = EStorageType::DateTime;
	}
	else if (sqlType == -9)
	{
		m_type = EStorageType::String;
	}
}


NetworkCommon::DBConnection::SQLBuffer::~SQLBuffer()
{
}

void * NetworkCommon::DBConnection::SQLBuffer::GetBuffer()
{
	switch (m_type)
	{
	case SQLBuffer::EStorageType::Int:
		return &m_data.Int;
	case SQLBuffer::EStorageType::Float:
		return &m_data.Float;
	case SQLBuffer::EStorageType::BIGINT:
		return &m_data.BIGINT;
	case SQLBuffer::EStorageType::String:
		return &m_strData;
	case SQLBuffer::EStorageType::DateTime:
		return &m_data.DateTime;
	default:
		throw SQLException("unknown type");
	}
}

template<>
int NetworkCommon::DBConnection::SQLBuffer::GetValue() noexcept
{
	return m_data.Int;
}

template<>
float NetworkCommon::DBConnection::SQLBuffer::GetValue() noexcept
{
	return m_data.Float;
}

template<>
INT64 NetworkCommon::DBConnection::SQLBuffer::GetValue() noexcept
{
	return m_data.BIGINT;
}
template<>
std::string NetworkCommon::DBConnection::SQLBuffer::GetValue() noexcept
{ 
	return m_strData.c_str();
}

template<>
TIMESTAMP_STRUCT NetworkCommon::DBConnection::SQLBuffer::GetValue() noexcept
{
	return m_data.DateTime;
}
