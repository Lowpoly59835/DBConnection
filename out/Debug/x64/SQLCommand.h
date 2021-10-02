#pragma once
#include "SQLConnection.h"
#include "SQLParameter.h"
#include <vector>


namespace NetworkCommon
{
	namespace DBConnection
	{
		class SQLReader;
		using std::vector; 
		
#pragma warning (disable : 4231)
#pragma warning( disable : 4251)
		EXPORT_INTERFACE_CLASS(vector<SQLParameter>);
#pragma warning (default : 4231) 
#pragma warning (default : 4251)

		class DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLCommand
		{

		public:
			SQLCommand() = delete;
			SQLCommand(SQLConnection* connection);
			SQLCommand(SQLConnection* connection, const wchar_t* strCommand);
			~SQLCommand();

		public:
			SQLReader Execute();
			SQLReader Execute(const wchar_t * command);

			SQLParameter* AddParameter(const char* parameterName, SQLSMALLINT type);
			SQLParameter* AddParameterWithValue(const char* parameterName, SQLSMALLINT type, int value);
			SQLParameter* AddParameterWithValue(const char* parameterName, SQLSMALLINT type, long long value);
			SQLParameter* AddParameterWithValue(const char* parameterName, SQLSMALLINT type, float value);
			SQLParameter* AddParameterWithValue(const char* parameterName, SQLSMALLINT type, std::string& value);
			SQLParameter* AddParameterWithValue(const char* parameterName, SQLSMALLINT type, TIMESTAMP_STRUCT& value);
			SQLParameter* AddParameterWithValue(const char* parameterName, SQLSMALLINT type, tm& value);

			SQLParameter* AddOutputParameter(const char* parameterName, SQLSMALLINT type);
			/*
			SQLParameter* AddOutputParameterWithValue(const char* parameterName, SQLSMALLINT type, int value);
			SQLParameter* AddOutputParameterWithValue(const char* parameterName, SQLSMALLINT type, long long value);
			SQLParameter* AddOutputParameterWithValue(const char* parameterName, SQLSMALLINT type, float value);
			SQLParameter* AddOutputParameterWithValue(const char* parameterName, SQLSMALLINT type, std::string& value);
			SQLParameter* AddOutputParameterWithValue(const char* parameterName, SQLSMALLINT type, TIMESTAMP_STRUCT& value);
			SQLParameter* AddOutputParameterWithValue(const char* parameterName, SQLSMALLINT type, tm& value);
			*/

			template<typename T>
			T GetParameterOutputValue(const char* colName)
			{
				static_assert(true, "unknow data type");
			}


		private:
			RETCODE ExecuteStatement(SQLHSTMT& hStmt);

		private:
			CustomString m_command;
			SQLConnection* m_connection;
			
			vector<SQLParameter> m_pararmetersOutput;
			vector<SQLParameter> m_pararmeters;
		};



		template <>
		int DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLCommand::GetParameterOutputValue<int>(const char* colName);
		
		template <>
		float DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLCommand::GetParameterOutputValue<float>(const char* colName);

		template <>
		std::string DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLCommand::GetParameterOutputValue<std::string>(const char* colName);

		template <>
		TIMESTAMP_STRUCT DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLCommand::GetParameterOutputValue<TIMESTAMP_STRUCT>(const char* colName);

		/// 초단위까지만 지원
		/// 밀리세컨드는 따로 변환해야함
		template <>
		tm DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLCommand::GetParameterOutputValue<tm>(const char* colName);
	}
}

