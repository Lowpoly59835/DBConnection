#pragma once

#include "ExportDefine.h"
#include "SharedClass.h"
#include <sql.h>
#include <sqlext.h>

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

		void DBCONNECTIONDLL_EXPORTS_DECLSPEC HandleDiagnosticRecord(SQLHANDLE hHandle, SQLSMALLINT hType, RETCODE RetCode);
		bool DBCONNECTIONDLL_EXPORTS_DECLSPEC IsSuccess(SQLRETURN val);


		enum class DBCONNECTIONDLL_EXPORTS_DECLSPEC ESQLErrorCode
		{
			UNKNOWN = -100,
			INVALID = -200,
			SUCESS = 0,
			CONNECT_FAIL = 1,
			NO_SUPPORT_TYPE = 2,
			ALLOC_HANDDLE_FAIL = 3,
			EXECUTE_FAIL = 4,
			COLUMNS_ERROR = 5,
			NOT_EXISTIS_COLUM = 6,
			BIND_PARMETER_ERROR = 7
		};

		class EXPORT_INTERFACE(std::exception);

		class DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLException 
		{
		private:
			ESQLErrorCode m_errorCode;
			SQLRETURN m_result;
			std::exception m_exception;
		public:
			SQLException(const char* message = "", ESQLErrorCode errcode = ESQLErrorCode::UNKNOWN, SQLRETURN returnValue = 0);
			PROPERT_GETEX(m_errorCode, ESQLErrorCode, ErrorCode);

			std::string GetMessage()
			{
				return Format("[%d]%s", m_errorCode, m_exception.what());
			}
		};

	}
}