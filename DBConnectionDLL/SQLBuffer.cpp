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
