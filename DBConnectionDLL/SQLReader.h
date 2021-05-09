#pragma once
#include "SQLCommand.h"
#include <type_traits>

namespace NetworkCommon
{
	namespace DBConnection
	{
		class DBCONNECTIONDLL_EXPORTS SQLReader
		{
		public:
			SQLReader() = delete;
			SQLReader(const SQLReader&) = delete;
			SQLReader(SQLHSTMT& hStmt);
			SQLReader(const SQLReader&& other);
			~SQLReader();

		public:
			
			template<typename T>
			T GetResult();

		private:
			SQLHSTMT m_resultStmt;
		};
	}
}

