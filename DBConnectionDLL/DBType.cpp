#include "pch.h"
#include "DBType.h"
#include "DBObject.h"
#include <typeinfo>
#include <iostream>
#include <string.h>
#include "DBTypeManager.h"

using std::string;

NetworkCommon::DBConnection::CDBType::CDBType(CDBObject* obj)
{
	m_name = obj->GetName();
	//m_name.erase(0, 6);
	CDBTypeManager::Instance()->RegistType(this);

	m_nativeTypeHashCode = typeid(*obj).hash_code();
}

NetworkCommon::DBConnection::CDBType::CDBType()
	:m_name(""), m_nativeTypeHashCode(0)
{
}

vector<NetworkCommon::DBConnection::CDBType> NetworkCommon::DBConnection::CDBType::GetMemberInfos()
{
	return CDBTypeManager::Instance()->FindMemberInfos(*this);
}

bool NetworkCommon::DBConnection::CDBType::operator==(const type_info& other)
{
	return m_nativeTypeHashCode == other.hash_code();
}

bool NetworkCommon::DBConnection::CDBType::operator==(const CDBType& other)
{
	return m_nativeTypeHashCode == other.m_nativeTypeHashCode;
}

bool NetworkCommon::DBConnection::CDBType::operator==(const CDBType& other) const
{
	return m_nativeTypeHashCode == other.m_nativeTypeHashCode;
}



///////////////////////////////////////////////////////////////

NetworkCommon::DBConnection::CMemberInfo::CMemberInfo()
	:CDBType::CDBType()
{
}

NetworkCommon::DBConnection::CMemberInfo::CMemberInfo(CDBObject* owner, CDBObject* member)
	: CDBType::CDBType()
{
	string typeName = typeid(*member).name();
	typeName.erase(0, 6);

	m_name = owner->GetName();
	m_name += "::";
	m_name += member->GetName();


	m_nativeTypeHashCode = typeid(*member).hash_code();

	CDBTypeManager::Instance()->RegistType(owner->GetName(), this);
}
