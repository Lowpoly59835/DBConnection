#pragma once
#include "SQLConnection.h"
#include <vector>

namespace NetworkCommon
{
	namespace DBConnection
	{
		class SQLReader;
#pragma warning (disable : 4231)
#pragma warning( disable : 4251)
		EXPORT_STL_STRING(char);
#pragma warning (default : 4231) 
#pragma warning (default : 4251)

		struct DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLParameter
		{
		public:
			SQLParameter();
			SQLParameter(const SQLParameter*) = delete;

			SQLParameter(const char* name, char type);
			SQLParameter(const SQLParameter&);
			~SQLParameter();

		public:
			std::string m_name;
			char m_type;

		};

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

