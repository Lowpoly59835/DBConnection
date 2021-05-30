#include "pch.h"
#include "IConnection.h"

using std::exception;

void DBCONNECTIONDLL_IMPORT NetworkCommon::DBConnection::HandleDiagnosticRecord(SQLHANDLE hHandle, SQLSMALLINT hType, RETCODE RetCode)
{
	SQLSMALLINT iRec = 0;
	SQLINTEGER  iError;
	WCHAR       wszMessage[1000];
	WCHAR       wszState[SQL_SQLSTATE_SIZE + 1];

	if (RetCode == SQL_INVALID_HANDLE)
	{
		throw exception("Invalid handle!\n");
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
		throw exception("Invalid handle!\n");
	}
}
