#pragma once
#include "SQLCommand.h"
#include <list>
#include "DBRecord.h"
#include "type.h"


namespace NetworkCommon
{
	namespace DBConnection
	{
		using std::list;
		using namespace NetworkCommon::Type;
	
		class DBCONNECTIONDLL_EXPORTS SQLReader
		{

		public:
			SQLReader() = delete;
			SQLReader(const SQLReader&) = delete;
			SQLReader(SQLHSTMT& hStmt, std::list<SQLParameter>& pararmetersWithValue, std::list<SQLParameter>& pararmetersWithOutput);
			SQLReader(const SQLReader&& other);
			~SQLReader();

		public:
			bool Next();
			void GetValue(const char* colName);



		private:
			SQLHSTMT m_hStmt;


			list<SQLParameter> m_pararmetersWithOutput;
			list<SQLParameter> m_pararmetersWithValue;

			list<ISQLResult> m_sqlResult;
		};

		struct ISQLResult
		{

		};

		template<typename T>
		struct DBCONNECTIONDLL_EXPORTS SQLResult : ISQLResult
		{
		public:
			SQLResult()
			{
				static_assert(check_type<T>::value, "none support type");
			}

			~SQLResult()
			{

			}

			T value;
		};
	}
}

