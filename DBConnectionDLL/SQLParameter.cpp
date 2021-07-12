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

RETCODE NetworkCommon::DBConnection::SQLParameter::BindParmeter(SQLHSTMT& hstmt, int colpos, SQLSMALLINT bindType)
{
	SQLLEN cid = 0;
	SQLRETURN result = 0;
	SQLLEN string_length = 0;

	if (!m_name.empty())
	{
		SQLHDESC hIpd = NULL;

		result = SQLGetStmtAttr(hstmt, SQL_ATTR_IMP_PARAM_DESC, &hIpd, 0, 0);

		if (!IsSuccess(result))
		{
			throw SQLException("", ESQLErrorCode::BIND_PARMETER_ERROR, result);
		}

		result = SQLSetDescField(hIpd, colpos, SQL_DESC_NAME, SQLPOINTER(m_name.c_str()), SQL_NTS);


		if (!IsSuccess(result))
		{
			throw SQLException("", ESQLErrorCode::BIND_PARMETER_ERROR, result);
		}
	}

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
		std::string* pString = static_cast<std::string*>(m_buffer.GetBuffer());
		result = SQLBindParameter(hstmt, colpos, bindType, SQL_C_CHAR, SQL_CHAR, pString->length(), 0, SQLPOINTER(static_cast<std::string*>(m_buffer.GetBuffer())), 0, &cid);
	}break;
	case SQLBuffer::EStorageType::DateTime:
		result = SQLBindParameter(hstmt, colpos, bindType, SQL_C_TIMESTAMP, SQL_TIMESTAMP, sizeof(TIMESTAMP_STRUCT), 0, static_cast<TIMESTAMP_STRUCT*>(m_buffer.GetBuffer()), 0, &cid);
		break;
	default:
		throw SQLException("unknown type", ESQLErrorCode::NO_SUPPORT_TYPE);
	}

	if (cid == SQL_NULL_DATA)
	{
		throw SQLException("null data", ESQLErrorCode::INVALID);
	}

	return result;
}