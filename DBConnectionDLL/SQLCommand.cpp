#include "pch.h"
#include "SQLCommand.h"
#include "SQLReader.h"
#include <exception>
#include <utility>

using std::exception;
using NetworkCommon::DBConnection::SQLReader;
using std::make_pair;
using std::string;


NetworkCommon::DBConnection::SQLCommand::SQLCommand(SQLConnection* connection, const wchar_t* command)
	:m_connection(connection), m_command(command)
{
}

NetworkCommon::DBConnection::SQLCommand::~SQLCommand()
{
}

const SQLReader&& NetworkCommon::DBConnection::SQLCommand::Execute()
{
	if (m_connection == nullptr)
	{
		throw exception("conntion is null");
	}
	else if (m_command.empty())
	{
		throw exception("command is empty");
	}


	SQLHSTMT hStmt = NULL;

	RETCODE retCode = SQLAllocHandle(SQL_HANDLE_STMT, m_connection->m_connHanlde, &hStmt);

	if (retCode != SQL_SUCCESS)
	{
		throw exception(Format("Invalid stmt errorCode :  %d \n", retCode));
	}
	
	retCode = ExecuteStatement(hStmt);

	if (retCode != SQL_SUCCESS)
	{
		throw exception(Format("Excute fail :  %d \n", retCode));
	}

	return SQLReader(hStmt);
}

RETCODE NetworkCommon::DBConnection::SQLCommand::ExecuteStatement(SQLHSTMT& hStmt)
{
	WCHAR* command = const_cast<WCHAR*>(m_command.c_str());

	RETCODE retcode = SQLPrepare(hStmt, command, SQL_NTS);

	if (retcode != SQL_SUCCESS) 
	{
		throw exception(Format("sql prepare fail"));
	}

	 retcode = SQLExecute(hStmt);

	 if (retcode != SQL_SUCCESS) 
	 {
		 throw exception(Format("sql query execute fail"));
	 }

	 return retcode;
}

const SQLReader && NetworkCommon::DBConnection::SQLCommand::Execute(const wchar_t * command)
{
	m_command = command;

	return Execute();
}


void NetworkCommon::DBConnection::SQLCommand::AddParameterWithValue(const char * parameterName, char type)
{
	m_pararmetersWithValue[parameterName] = SQLParameter(parameterName, type);
}

void NetworkCommon::DBConnection::SQLCommand::AddParameterWithOutput(const char * parameterName, char type)
{
	m_pararmetersOutput[parameterName] = SQLParameter(parameterName, type);
}

NetworkCommon::DBConnection::SQLParameter::SQLParameter(const char * name, char type)
	:m_name(name), m_type(type)
{
	switch (m_type)
	{
	case SQL_C_CHAR:
	case SQL_C_LONG:
	case SQL_C_DOUBLE:
	case SQL_C_DATE:
		break;
	default:
		static_assert(true, "none support type");
	}
}

NetworkCommon::DBConnection::SQLParameter::~SQLParameter()
{
}
