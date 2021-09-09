#pragma once
#include "SQLCommand.h"
#include <vector>
#include "SQLBuffer.h"
#include "CustomString.h"


namespace NetworkCommon
{
	namespace DBConnection
	{
		using std::vector;
#pragma warning (disable : 4231)
#pragma warning( disable : 4251)
		EXPORT_INTERFACE_CLASS(vector<std::pair<CustomString, SQLBuffer*>>);
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

		private:
			void Bind();
			SQLRETURN BindReadBuffer(SQLBuffer& buffer, SQLHSTMT& hstmt, int colpos);
			void BufferClear();

		private:
			SQLHSTMT m_hStmt;
			SQLCommand& m_command;
			
			vector<std::pair<CustomString, SQLBuffer*>> m_resultBuffer;
			bool m_hasValue;
		};

		template <>
		int DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLReader::GetValue<int>(const char* colName);

		template <>
		float DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLReader::GetValue<float>(const char* colName);

		template <>
		std::string DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLReader::GetValue<std::string>(const char* colName);

		template <>
		TIMESTAMP_STRUCT DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLReader::GetValue<TIMESTAMP_STRUCT>(const char* colName);

		/// 초단위까지만 지원
		/// 밀리세컨드는 따로 변환해야함
		template <>
		tm DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLReader::GetValue<tm>(const char* colName);
	}
}

