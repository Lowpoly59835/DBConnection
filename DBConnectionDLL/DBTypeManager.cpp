#include "pch.h"
#include "DBTypeManager.h"
using NetworkCommon::DBConnection::CDBType;

void NetworkCommon::DBConnection::CDBTypeManager::RegistType(CDBType* dbType)
{
	RegistType(dbType->GetName(), dbType);
}

void NetworkCommon::DBConnection::CDBTypeManager::RegistType(const char* typeName, CDBType* dbType)
{
	if (dbType == nullptr)
	{
		return;
	}
	else if (typeName == nullptr || strlen(typeName) == 0)
	{
		return;
	}

	CCriticalSectionLock locker(m_typelock);

	auto findIt = m_TypeList.find(typeName);

	if (findIt == m_TypeList.end())
	{
		MapType newRecord;
		//newRecord.insert({dbType->GetName(), * dbType});
		m_TypeList.insert({ typeName, newRecord });
	}
	else
	{
		auto& subRecord = findIt->second;
		subRecord.insert({ dbType->GetName(), *dbType });
	}
}

vector<CDBType> NetworkCommon::DBConnection::CDBTypeManager::FindMemberInfos(CDBType& dbType)
{
	MapTypeList::iterator findIt;

	if (CCriticalSectionLock lock = m_typelock)
	{
		findIt = m_TypeList.find(dbType.GetName());

		if (findIt == m_TypeList.end())
		{
			return vector<CDBType>();
		}
		else
		{
			if (m_CashTypeList.count(dbType.GetName()))
			{
				return m_CashTypeList[dbType.GetName()];
			}
		}
	}

	if (CCriticalSectionLock lock = m_cashlock)
	{
		vector<CDBType> newCashList;
		for (auto& typeinfo : findIt->second)
		{
			newCashList.emplace_back(typeinfo.second);
		}

		m_CashTypeList[dbType.GetName()] = newCashList;

		return m_CashTypeList[dbType.GetName()];
	}
	return vector<CDBType>();
}