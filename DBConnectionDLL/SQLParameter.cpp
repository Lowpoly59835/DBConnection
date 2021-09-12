#include "pch.h"
#include "SQLParameter.h"

NetworkCommon::DBConnection::SQLParameter::SQLParameter(SQLSMALLINT type)
	:m_name(), m_buffer(type)
{
}

NetworkCommon::DBConnection::SQLParameter::SQLParameter(const char * name, SQLSMALLINT type)
	:m_name(name), m_buffer(type)
{
}

NetworkCommon::DBConnection::SQLParameter::~SQLParameter()
{
}

void NetworkCommon::DBConnection::SQLParameter::operator=(int value)
{
	SQLINTEGER* pValue = static_cast<SQLINTEGER*>(m_buffer.GetBuffer());
	*pValue = value;
}

void NetworkCommon::DBConnection::SQLParameter::operator=(long long value)
{
	SQLBIGINT* pValue = static_cast<SQLBIGINT*>(m_buffer.GetBuffer());
	*pValue = value;
}

void NetworkCommon::DBConnection::SQLParameter::operator=(float value)
{
	SQLFLOAT* pValue = static_cast<SQLFLOAT*>(m_buffer.GetBuffer());
	*pValue = value;
}

void NetworkCommon::DBConnection::SQLParameter::operator=(const char* value)
{
	CustomString* pValue = static_cast<CustomString*>(m_buffer.GetBuffer());
	*pValue = value;
}

void NetworkCommon::DBConnection::SQLParameter::operator=(std::string& value)
{
	CustomString* pValue = static_cast<CustomString*>(m_buffer.GetBuffer());
	*pValue = value.c_str();
}

void NetworkCommon::DBConnection::SQLParameter::operator=(TIMESTAMP_STRUCT& value)
{
	TIMESTAMP_STRUCT* pValue = static_cast<TIMESTAMP_STRUCT*>(m_buffer.GetBuffer());
	*pValue = TIMESTAMP_STRUCT { value.year, value.month, value.day, value.hour, value.minute, value.second, value.fraction };
}


RETCODE NetworkCommon::DBConnection::SQLParameter::BindParmeter(SQLHSTMT& hstmt, int colpos, SQLSMALLINT bindType)
{
	SQLLEN cid = 0;
	SQLRETURN result = 0;
	SQLLEN string_length = 0;

	SQLSMALLINT   NumParams, i, DataType, DecimalDigits, Nullable;
	SQLULEN   ParamSize;

	result = SQLDescribeParam(hstmt, colpos, &DataType, &ParamSize, &DecimalDigits, &Nullable);

	if (!IsSuccess(result))
	{
		throw SQLException(hstmt, SQL_HANDLE_STMT, result);
	}

	switch (m_buffer.Type)
	{
	case SQLBuffer::EStorageType::Int:
		result = SQLBindParameter(hstmt, colpos, bindType, SQL_INTEGER, DataType, 0, 0, static_cast<SQLINTEGER*>(m_buffer.GetBuffer()), 0, &cid);
		break;
	case SQLBuffer::EStorageType::Float:
		result = SQLBindParameter(hstmt, colpos, bindType, SQL_C_FLOAT, DataType, 0, 0, static_cast<SQLFLOAT*>(m_buffer.GetBuffer()), 0, &cid);
		break;
	case SQLBuffer::EStorageType::BIGINT:
		result = SQLBindParameter(hstmt, colpos, bindType, SQL_BIGINT, DataType, 0, 0, static_cast<SQLBIGINT*>(m_buffer.GetBuffer()), 0, &cid);
		break;
	case SQLBuffer::EStorageType::String:
	{
		cid = SQL_NTS;
		CustomString* pString = static_cast<CustomString*>(m_buffer.GetBuffer());
		result = SQLBindParameter(hstmt, colpos, bindType, SQL_C_CHAR, DataType, ParamSize, 0, SQLPOINTER(pString->c_str()), pString->Size() * 2, &cid);
		//result = SQLBindParameter(hstmt, colpos, bindType, SQL_C_CHAR, DataType, ParamSize, 0, SQLPOINTER(pString->c_str()), ParamSize+1, &cid);
	}break;
	case SQLBuffer::EStorageType::DateTime:
		result = SQLBindParameter(hstmt, colpos, bindType, SQL_C_TYPE_TIMESTAMP, DataType, ParamSize, DecimalDigits, static_cast<TIMESTAMP_STRUCT*>(m_buffer.GetBuffer()), sizeof(TIMESTAMP_STRUCT), 0);
		break;
	default:
		throw SQLException(Format("%s parameter is unknown type", m_name.c_str()).c_str());
	}
	if (cid == SQL_NULL_DATA)
	{
		throw SQLException("null data");
	}


	if (!IsSuccess(result))
	{
		throw SQLException(hstmt, SQL_HANDLE_STMT, result);
	}

	return result;
}
