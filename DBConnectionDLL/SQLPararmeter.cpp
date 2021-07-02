#include "pch.h"
#include "SQLParameter.h"


NetworkCommon::DBConnection::SQLParameter::SQLParameter()
	:m_name(), m_type()
{
}

NetworkCommon::DBConnection::SQLParameter::SQLParameter(const char * name, char type)
	: m_name(name), m_type(type)
{
	switch (m_type)
	{
	case SQL_C_CHAR:
		break;
	case SQL_C_LONG:
		break;
	case SQL_C_DOUBLE:
		break;
	case SQL_C_DATE:
		break;
	default:
		static_assert(true, "none support type");
		break;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

NetworkCommon::DBConnection::SQLParameter::SQLParameter(const SQLParameter& other)
	:m_name(other.m_name), m_type(other.m_type)
{
}

NetworkCommon::DBConnection::SQLParameter::~SQLParameter()
{
}
