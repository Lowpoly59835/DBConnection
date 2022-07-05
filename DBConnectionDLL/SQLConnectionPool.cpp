#include "pch.h"
#include "SQLConnectionPool.h"
#include "SQLConnection.h"
#include <functional>

using NetworkCommon::DBConnection::IConnection;

NetworkCommon::DBConnection::CSQLConnectionPool::CSQLConnectionPool()
	:m_connectCount(DefaultConnectCount), m_maxConnectCount(DefaultMaxConectCount)
{
}

NetworkCommon::DBConnection::CSQLConnectionPool::~CSQLConnectionPool()
{
}

IConnection* NetworkCommon::DBConnection::CSQLConnectionPool::GetConnect()
{
	if (this->m_driverInfo.empty())
	{
		return nullptr;
	}

	return nullptr;
}

void NetworkCommon::DBConnection::CSQLConnectionPool::LoadDriver(std::string driverInfo)
{
	this->m_driverInfo = driverInfo;

	for (int i = 0; i < m_maxConnectCount; i++)
	{
	}
}

