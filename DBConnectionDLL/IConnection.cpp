#include "pch.h"
#include "IConnection.h"

using std::exception;

void NetworkCommon::DBConnection::HandleDiagnosticRecord(SQLHANDLE hHandle, SQLSMALLINT hType, RETCODE RetCode)
{
	SQLSMALLINT iRec = 0;
	SQLINTEGER  iError;
	WCHAR       wszMessage[1000];
	WCHAR       wszState[SQL_SQLSTATE_SIZE + 1];

	if (RetCode == SQL_INVALID_HANDLE)
	{
		throw SQLException("Invalid handle!", ESQLErrorCode::INVALID);
	}

	if (SQLGetDiagRec(hType,
		hHandle,
		++iRec,
		wszState,
		&iError,
		wszMessage,
		(SQLSMALLINT)(sizeof(wszMessage) / sizeof(WCHAR)),
		(SQLSMALLINT*)NULL) != SQL_SUCCESS)
	{
		throw SQLException("Invalid handle!", ESQLErrorCode::INVALID);
	}
}

bool DBCONNECTIONDLL_EXPORTS_DECLSPEC NetworkCommon::DBConnection::IsSuccess(SQLRETURN val)
{
	return val == SQLRETURN(SQL_SUCCESS) || val == SQLRETURN(SQL_SUCCESS_WITH_INFO);
}

NetworkCommon::DBConnection::SQLException::SQLException(const char* message, ESQLErrorCode errcode, SQLRETURN returnValue)
	:m_exception(message), m_errorCode(errcode), m_result(returnValue)
{
}
