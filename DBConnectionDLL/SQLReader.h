#pragma once
#include "SQLCommand.h"
#include <list>
#include "type.h"


namespace NetworkCommon
{
	namespace DBConnection
	{
		using std::list;
		using namespace NetworkCommon::Type;

		struct ISQLResult
		{

		};



		template<typename T>
		struct DBCONNECTIONDLL_IMPORT SQLResult : ISQLResult
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
		class DBCONNECTIONDLL_IMPORT SQLReader
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
			void SetResult();

		private:
			SQLHSTMT m_hStmt;


			list<SQLParameter> m_pararmetersWithOutput;
			list<SQLParameter> m_pararmetersWithValue;

			list<ISQLResult*> m_sqlResult;
		};
	}
}

