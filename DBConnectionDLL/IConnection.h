#pragma once

#include "ExportDefine.h"
#include "SharedClass.h"
#include <sql.h>
#include <sqlext.h>

namespace NetworkCommon
{
	namespace DBConnection
	{
		__interface DBCONNECTIONDLL_EXPORTS IConnection
		{
		public:
			void Open() throw(std::exception);
			void Close() throw(std::exception);
		};

		void DBCONNECTIONDLL_EXPORTS HandleDiagnosticRecord(SQLHANDLE hHandle, SQLSMALLINT hType, RETCODE RetCode);
	}
}