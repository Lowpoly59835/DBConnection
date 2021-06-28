#include "pch.h"
#include "SQLConnection.h"

NetworkCommon::DBConnection::SQLConnection::SQLConnection(const wchar_t* strConnection)
	:m_strConnection(strConnection), m_connHanlde(NULL), m_envHandle(NULL)
{
}

NetworkCommon::DBConnection::SQLConnection::~SQLConnection()
{
	Close();
}

void NetworkCommon::DBConnection::SQLConnection::Open()
{
	if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_envHandle) == SQL_ERROR)
	{
		throw SQLException("Unable to allocate an environment handle", ESQLErrorCode::ALLOC_HANDDLE_FAIL, SQL_ERROR);
	}

	SQLRETURN retCode = SQLSetEnvAttr(m_envHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);


	if (!IsSuccess(retCode))
	{
		throw SQLException("Invalid handle errorCode", ESQLErrorCode::ALLOC_HANDDLE_FAIL, retCode);
	}

	//HandleDiagnosticRecord(m_envHandle, SQL_HANDLE_ENV, retCode);

	retCode = SQLAllocHandle(SQL_HANDLE_DBC, m_envHandle, &m_connHanlde);

	if (!IsSuccess(retCode))
	{
		throw SQLException("Invalid ConnHanlde", ESQLErrorCode::INVALID, retCode);
	}


	//HandleDiagnosticRecord(m_envHandle, SQL_HANDLE_ENV, retCode);
	WCHAR* pwszConnStr = const_cast<WCHAR*>(m_strConnection.c_str());

	retCode = SQLDriverConnect(m_connHanlde, GetDesktopWindow(), pwszConnStr, SQL_NTS, NULL, 0, NULL, SQL_DRIVER_COMPLETE);

	if (!IsSuccess(retCode))
	{
		throw SQLException("Connect fail", ESQLErrorCode::CONNECT_FAIL, retCode);
	}
}

void NetworkCommon::DBConnection::SQLConnection::Close()
{
	if (m_connHanlde)
	{
		SQLDisconnect(m_connHanlde);
		SQLFreeHandle(SQL_HANDLE_DBC, m_connHanlde);
		m_connHanlde = NULL;
	}

	if (m_envHandle) 
	{
		SQLFreeHandle(SQL_HANDLE_ENV, m_envHandle);
		m_envHandle = NULL;
	}
}


