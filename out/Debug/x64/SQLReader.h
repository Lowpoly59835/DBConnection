#pragma once
#include "SQLCommand.h"
#include <vector>
#include "SQLBuffer.h"


namespace NetworkCommon
{
	namespace DBConnection
	{
		using std::vector;
		using std::wstring;

#pragma warning (disable : 4231)
#pragma warning( disable : 4251)
		EXPORT_STL_STRING(wchar_t);
		EXPORT_INTERFACE_CLASS(vector<std::pair<wstring, SQLBuffer*>>);
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
			T GetValue(const wchar_t* colName)
			{
				static_assert(true, "unknow data type");
			}

			bool HasValue() noexcept;
			int RowCount() noexcept;

		private:
			void bind();
			void BufferClear();

		private:
			SQLHSTMT m_hStmt;
			SQLCommand& m_command;
			
			vector<std::pair<wstring, SQLBuffer*>> m_resultBuffer;
			INT64 m_rowCount;
			bool m_hasValue;
		};

		template <>
		int DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLReader::GetValue<int>(const wchar_t* colName);

		template <>
		float DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLReader::GetValue<float>(const wchar_t* colName);

		template <>
		std::string DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLReader::GetValue<std::string>(const wchar_t* colName);

		template <>
		TIMESTAMP_STRUCT DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLReader::GetValue<TIMESTAMP_STRUCT>(const wchar_t* colName);

		/// 초단위까지만 지원
		/// 밀리세컨드는 따로 변환해야함
		template <>
		tm DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLReader::GetValue<tm>(const wchar_t* colName);
	}
}

