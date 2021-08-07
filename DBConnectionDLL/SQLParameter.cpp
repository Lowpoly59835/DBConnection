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
	*pValue = value;
}

RETCODE NetworkCommon::DBConnection::SQLParameter::BindParmeter(SQLHSTMT& hstmt, int colpos, SQLSMALLINT bindType)
{
	SQLLEN cid = 0;
	SQLRETURN result = 0;
	SQLLEN string_length = 0;

	switch (m_buffer.Type)
	{
	case SQLBuffer::EStorageType::Int:
		result = SQLBindParameter(hstmt, colpos, bindType, SQL_INTEGER, SQL_INTEGER, 0, 0, static_cast<SQLINTEGER*>(m_buffer.GetBuffer()), 0, &cid);
		break;
	case SQLBuffer::EStorageType::Float:
		result = SQLBindParameter(hstmt, colpos, bindType, SQL_C_FLOAT, SQL_FLOAT, 0, 0, static_cast<SQLFLOAT*>(m_buffer.GetBuffer()), 0, &cid);
		break;
	case SQLBuffer::EStorageType::String:
	{
		cid = SQL_NTS;
		CustomString* pString = static_cast<CustomString*>(m_buffer.GetBuffer());
		result = SQLBindParameter(hstmt, colpos, bindType, SQL_C_CHAR, SQL_CHAR, pString->Size(), 0, SQLPOINTER(pString->c_str()), pString->Size() + 1, &cid);
	}break;
	case SQLBuffer::EStorageType::DateTime:
		result = SQLBindParameter(hstmt, colpos, bindType, SQL_C_TIMESTAMP, SQL_TIMESTAMP, sizeof(TIMESTAMP_STRUCT), 0, static_cast<TIMESTAMP_STRUCT*>(m_buffer.GetBuffer()), 0, &cid);
		break;
	default:
		throw SQLException(Format("%s parameter is unknown type", m_name.c_str()).c_str(), ESQLErrorCode::NO_SUPPORT_TYPE);
	}

	if (cid == SQL_NULL_DATA)
	{
		throw SQLException("null data", ESQLErrorCode::INVALID);
	}


	//if (!m_name.empty())
	//{
	//	SQLHDESC hIpd = NULL;

	//	result = SQLGetStmtAttr(hstmt, SQL_ATTR_IMP_PARAM_DESC, &hIpd, 0, 0);

	//	if (!IsSuccess(result))
	//	{
	//		throw SQLException("", ESQLErrorCode::BIND_PARMETER_ERROR, result);
	//	}

	//	result = SQLSetDescField(hIpd, colpos, SQL_DESC_NAME, SQLPOINTER(m_name.c_str()), SQL_NTS);

	//	if (!IsSuccess(result))
	//	{
	//		throw SQLException("", ESQLErrorCode::BIND_PARMETER_ERROR, result);
	//	}
	//}

	return result;
}
