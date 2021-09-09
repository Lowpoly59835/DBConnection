#include "pch.h"
#include "SQLConnection.h"

NetworkCommon::DBConnection::SQLConnection::SQLConnection(const char* strConnection)
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
		throw SQLException("Unable to allocate an environment handle");
	}

	SQLRETURN retCode = SQLSetEnvAttr(m_envHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);


	if (!IsSuccess(retCode))
	{
		throw SQLException(m_envHandle, SQL_HANDLE_ENV, retCode);
	}

	//HandleDiagnosticRecord(m_envHandle, SQL_HANDLE_ENV, retCode);

	retCode = SQLAllocHandle(SQL_HANDLE_DBC, m_envHandle, &m_connHanlde);

	if (!IsSuccess(retCode))
	{
		throw SQLException(m_envHandle, SQL_HANDLE_DBC, retCode);
	}

	std::wstring wstrConnection = ToWString(m_strConnection.c_str());

	//WCHAR* pwszConnStr = const_cast<WCHAR*>(wstrConnection.c_str());
	SQLWCHAR out_connect_str[1024] = L"";
	SQLSMALLINT OutConnStrLen = 0;

	retCode = SQLDriverConnect(m_connHanlde, GetDesktopWindow(), wstrConnection.data(), wcslen(wstrConnection.data()), out_connect_str, 1024, &OutConnStrLen, SQL_DRIVER_NOPROMPT);

	if (!IsSuccess(retCode))
	{
		throw SQLException(m_connHanlde, SQL_HANDLE_DBC, retCode);
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


