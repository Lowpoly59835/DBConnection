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
		using std::string;

#pragma warning (disable : 4231)
#pragma warning( disable : 4251)
		EXPORT_INTERFACE_CLASS(vector<std::pair<string, SQLBuffer>>);
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
			bool Next();

			template<typename T>
			T GetValue(const char* colName)
			{
				static_assert(true, "unknow data type");
			}

			bool HasValue() noexcept;
			int RowCount() noexcept;

		private:
			void bind();

		private:
			SQLHSTMT m_hStmt;
			SQLCommand& m_command;
			
			vector<std::pair<string, SQLBuffer>> m_resultBuffer;
			int m_rowCount;
			bool m_hasValue;
		};

		template <>
		int DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLReader::GetValue<int>(const char* colName);

		template <>
		float DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLReader::GetValue<float>(const char* colName);

		template <>
		std::string DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLReader::GetValue<std::string>(const char* colName);

		template <>
		time_t DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLReader::GetValue<time_t>(const char* colName);
	}
}

