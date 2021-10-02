#include "pch.h"
#include "SQLTranstaction.h"

using NetworkCommon::DBConnection::SQLConnection;

NetworkCommon::DBConnection::SQLTranstaction::SQLTranstaction(SQLConnection* connection)
	:m_connection(connection), m_isCommit(true)
{
	if (m_connection == nullptr)
	{
		throw SQLException("Connection is null");
	}
}

NetworkCommon::DBConnection::SQLTranstaction::~SQLTranstaction()
{
	try
	{
		if (!m_isCommit)
		{
			Rollback();
		}
	}
	catch (SQLException&)
	{
		return;
	}
}

VOID NetworkCommon::DBConnection::SQLTranstaction::BegionTrans()
{
	SQLRETURN result = SQLSetConnectAttr(m_connection->m_connHanlde, SQL_ATTR_AUTOCOMMIT, SQL_AUTOCOMMIT_OFF, SQL_IS_UINTEGER);

	if (!IsSuccess(result))
	{
		throw SQLException(m_connection->m_connHanlde, SQL_HANDLE_DBC, result);
	}
	m_isCommit = false;
}

VOID NetworkCommon::DBConnection::SQLTranstaction::Commit()
{
	SQLRETURN result = SQLEndTran(SQL_HANDLE_ENV, m_connection->m_envHandle, SQL_COMMIT);

	if (!IsSuccess(result))
	{
		throw SQLException(m_connection->m_envHandle, SQL_HANDLE_DBC, result);
	}
	m_isCommit = true;
}

void NetworkCommon::DBConnection::SQLTranstaction::Rollback()
{
	if (m_connection->m_envHandle == NULL)
	{
		return;
	}

	SQLRETURN result = SQLEndTran(SQL_HANDLE_ENV, m_connection->m_envHandle, SQL_ROLLBACK);

	if (!IsSuccess(result))
	{
		throw SQLException(m_connection->m_envHandle, SQL_HANDLE_DBC, result);
	}

	m_isCommit = true;
}
