#pragma once

#include "ExportDefine.h"
#include "SharedClass.h"
#include <sql.h>
#include <sqlext.h>
#include "CustomString.h"
#include <time.h>

namespace NetworkCommon
{
	namespace DBConnection
	{
		__interface DBCONNECTIONDLL_EXPORTS_DECLSPEC IConnection
		{
		public:
			void Open();
			void Close();
		};

		void DBCONNECTIONDLL_EXPORTS_DECLSPEC HandleDiagnosticRecord(SQLHANDLE hHandle, SQLSMALLINT hType, RETCODE RetCode, OUT CustomString& errorMessage, OUT SQLINTEGER& errorCode);
		bool DBCONNECTIONDLL_EXPORTS_DECLSPEC IsSuccess(SQLRETURN val);



		class DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLException 
		{
		private:
			SQLINTEGER m_errorCode;
			CustomString m_message;
		public:
			SQLException(SQLHANDLE& handle, SQLSMALLINT hType, RETCODE retCode);
			SQLException(const char* message);
			PROPERT_GETEX(m_errorCode, SQLINTEGER, ErrorCode);

			const char* GetMessage()
			{
				return m_message;
			}
		};

		tm TotmFromTimeStamp(TIMESTAMP_STRUCT& time_st);
		TIMESTAMP_STRUCT ToTimeStampFromtime_t(time_t& time_t);
		TIMESTAMP_STRUCT ToTimeStampFromtime_tm(tm& time_tm);

		
	}
}