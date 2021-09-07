#include "pch.h"
#include "IConnection.h"

using std::exception;

void NetworkCommon::DBConnection::HandleDiagnosticRecord(SQLHANDLE hHandle, SQLSMALLINT hType, RETCODE RetCode, OUT CustomString& errorMessage, OUT SQLINTEGER& errorCode)
{
	SQLSMALLINT iRec = 0;
	WCHAR       wszMessage[1000];
	WCHAR       wszState[SQL_SQLSTATE_SIZE + 1];

	if (RetCode == SQL_INVALID_HANDLE)
	{
		errorMessage = "Invalid handle!";
		errorCode = SQL_INVALID_HANDLE;
		return;
	}

	if (SQLGetDiagRec(hType,
		hHandle,
		++iRec,
		wszState,
		&errorCode,
		wszMessage,
		(SQLSMALLINT)(sizeof(wszMessage) / sizeof(WCHAR)),
		(SQLSMALLINT*)NULL) == SQL_SUCCESS)
	{
		//throw SQLException("Invalid handle!", ESQLErrorCode::INVALID);
		errorMessage = wszMessage;
	}
}

bool DBCONNECTIONDLL_EXPORTS_DECLSPEC NetworkCommon::DBConnection::IsSuccess(SQLRETURN val)
{
	return val == SQLRETURN(SQL_SUCCESS) || val == SQLRETURN(SQL_SUCCESS_WITH_INFO);
}

tm NetworkCommon::DBConnection::TotmFromTimeStamp(TIMESTAMP_STRUCT& time_st)
{
	tm time_tm{ time_st.second , time_st.minute, time_st.hour, time_st.day, time_st.month - 1, time_st.year - 1900
	};

	mktime(&time_tm);

	return time_tm;
}

TIMESTAMP_STRUCT NetworkCommon::DBConnection::ToTimeStampFromtime_t(time_t& time_t)
{
	tm time_tm;

	localtime_s(&time_tm, &time_t);

	return ToTimeStampFromtime_tm(time_tm);
}

TIMESTAMP_STRUCT NetworkCommon::DBConnection::ToTimeStampFromtime_tm(tm& time_tm)
{
	TIMESTAMP_STRUCT tm_stamp{time_tm.tm_year, time_tm.tm_mon, time_tm.tm_mday, time_tm.tm_hour, time_tm.tm_min, time_tm.tm_sec, 0};

	return tm_stamp;
}

NetworkCommon::DBConnection::SQLException::SQLException(SQLHANDLE& handle, SQLSMALLINT hType, RETCODE retCode)
{
	HandleDiagnosticRecord(handle, hType, retCode, m_message, m_errorCode);
}

NetworkCommon::DBConnection::SQLException::SQLException(const char* message)
	:m_message(message), m_errorCode(-1)
{
}
