#pragma once
#include "SQLCommand.h"
#include <vector>
#include "SQLBuffer.h"


namespace NetworkCommon
{
	namespace DBConnection
	{
		using std::vector;
		using namespace NetworkCommon::Type;

		template class DBCONNECTIONDLL_EXPORTS_DECLSPEC vector<SQLBuffer>;

		class DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLReader
		{
			
		public:
			SQLReader() = delete;
			SQLReader(const SQLReader&) = delete;
			SQLReader(SQLHSTMT& hStmt);
			SQLReader(const SQLReader&& other);
			~SQLReader();

		public:
			bool Next() noexcept;
			void GetValue(const char* colName) noexcept;

		private:
			SQLHSTMT m_hStmt;
			
			vector<SQLBuffer> m_sqlResult;
		};

	}
}

