#pragma once
#include "SQLConnection.h"
#include <string>
#include <vector>

namespace NetworkCommon
{
	using std::vector;

	namespace DBConnection
	{
		class SQLReader;


		struct DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLParameter
		{
		public:
			SQLParameter() = delete;
			SQLParameter(const SQLParameter*) = delete;

			SQLParameter(const char* name, char type);
			SQLParameter(const SQLParameter&);
			~SQLParameter();

		public:
			std::string m_name;
			char m_type;

		};

		class DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLCommand
		{

		public:
			SQLCommand() = delete;
			SQLCommand(SQLConnection* connection, const wchar_t* strConnection);
			~SQLCommand();

		public:
			const SQLReader Execute();
			const SQLReader Execute(const wchar_t * command);

			void AddParameterWithValue(const char* parameterName, char type);
			void AddParameterWithOutput(const char* parameterName, char type);

			PROPERT_GETEX(m_pararmetersWithValue, vector<SQLParameter>, ParameterWithValues);
			PROPERT_GETEX(m_pararmetersOutput, vector<SQLParameter>, ParameterOutputs);

		private:
			RETCODE ExecuteStatement(SQLHSTMT& hStmt);

		private:
			std::wstring m_command;
			SQLConnection* m_connection;
			
			vector<SQLParameter> m_pararmetersOutput;
			vector<SQLParameter> m_pararmetersWithValue;
		};
	}
}

