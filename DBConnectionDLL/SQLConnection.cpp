#include "pch.h"
#include "SQLConnection.h"
#include <exception>

using std::exception;

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
		throw exception("Unable to allocate an environment handle\n");
	}

	RETCODE retCode = SQLSetEnvAttr(m_envHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);


	if (retCode != SQL_SUCCESS)
	{
		throw exception(Format("Invalid handle errorCode :  %d \n", retCode));
	}

	HandleDiagnosticRecord(m_envHandle, SQL_HANDLE_ENV, retCode);

	retCode = SQLAllocHandle(SQL_HANDLE_DBC, m_envHandle, &m_connHanlde);

	if (retCode != SQL_SUCCESS)
	{
		throw exception(Format("Invalid ConnHanlde! errorCode :  %d \n", retCode));
	}


	HandleDiagnosticRecord(m_envHandle, SQL_HANDLE_ENV, retCode);
	WCHAR* pwszConnStr = const_cast<WCHAR*>(m_strConnection.c_str());

	retCode = SQLDriverConnect(m_connHanlde, GetDesktopWindow(), pwszConnStr, SQL_NTS, NULL, 0, NULL, SQL_DRIVER_COMPLETE);

	if (retCode != SQL_SUCCESS)
	{
		throw exception(Format("Connect fail errorCode :  %d \n", retCode));
	}
}

void NetworkCommon::DBConnection::SQLConnection::Close() throw(std::exception)
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


