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

#pragma warning (disable : 4231)
#pragma warning( disable : 4251)
		EXPORT_INTERFACE_CLASS(vector<SQLBuffer>);
#pragma warning (default : 4231) 
#pragma warning (default : 4251)

		class DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLReader
		{
			
		public:
			SQLReader() = delete;
			SQLReader(const SQLReader&) = delete;
			SQLReader(SQLCommand& command, SQLHSTMT hStmt) noexcept;
			SQLReader(const SQLReader&& other) noexcept;
			~SQLReader();

		public:
			bool Next() noexcept;
			void GetValue(const char* colName) noexcept;
			bool HasValue() noexcept;
			int RowCount() noexcept;

		private:
			void bind();

		private:
			SQLHSTMT m_hStmt;
			SQLCommand& m_command;
			
			vector<SQLBuffer> m_sqlResult;
		};

	}
}

