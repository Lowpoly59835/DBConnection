#include "pch.h"
#include "DBObject.h"
#include <typeinfo>
#include "IConnection.h"
#include "DBTypeManager.h"

using NetworkCommon::DBConnection::SQLException;
using NetworkCommon::DBConnection::CDBObject;
using NetworkCommon::DBConnection::CDBTABLE;
using NetworkCommon::DBConnection::CDBINT;
using NetworkCommon::DBConnection::CDBSTRING;
using NetworkCommon::DBConnection::CDBFLOAT;
using NetworkCommon::DBConnection::CDBDATETIME;
using NetworkCommon::DBConnection::CDBType;
using NetworkCommon::DBConnection::CDBTypeManager;
using NetworkCommon::DBConnection::CustomString;

using std::ostream;

CDBObject::CDBObject(const char* columnName)
	:m_objectName(columnName)
{
}

CDBObject&& CDBObject::CreateObject(CDBType& type)
{
	if (type == typeid(CDBINT))
	{
		return CDBINT();
	}
	else if(type == typeid(CDBFLOAT))
	{
		return CDBFLOAT();
	}
	else if (type == typeid(CDBSTRING))
	{
		return CDBSTRING();
	}

	throw NetworkCommon::DBConnection::SQLException(Format("[%s] Not support db type",GetCurrentMethodName).c_str());
}



const char* CDBObject::GetName()
{
	return m_objectName.c_str();
}


///////////////////////////////////////////////////////////////

CDBTABLE::CDBTABLE(const char* tableName)
	:CDBObject::CDBObject(tableName), m_dbType(this)
{
}

CDBType CDBTABLE::GetType()
{
	return m_dbType;
}

///////////////////////////////////////////////////////////////

CDBINT::CDBINT(CDBTABLE& owner, const char* columnName)
	: CDBObject::CDBObject(columnName), m_dbType(&owner, this), m_value(0)
{
}

CDBINT::CDBINT()
	: CDBObject::CDBObject(""), m_dbType(), m_value(0)
{
}

int NetworkCommon::DBConnection::CDBINT::GetValue()
{
	return m_value;
}

CDBType CDBINT::GetType()
{
	return m_dbType;
}

///////////////////////////////////////////////////////////////

CDBSTRING::CDBSTRING(CDBTABLE& owner, const char* columnName)
	: CDBObject::CDBObject(columnName), m_dbType(&owner, this), m_value("")
{
}

CDBSTRING::CDBSTRING()
	: CDBObject::CDBObject(""), m_dbType(), m_value("")
{
}

CDBType CDBSTRING::GetType()
{
	return m_dbType;
}


///////////////////////////////////////////////////////////////

CDBFLOAT::CDBFLOAT(CDBTABLE& owner, const char* columnName)
	: CDBObject::CDBObject(columnName), m_dbType(&owner, this), m_value(0.0f)
{
}

CDBFLOAT::CDBFLOAT()
	: CDBObject::CDBObject(""), m_dbType(), m_value(0.0f)
{
}

CDBType CDBFLOAT::GetType()
{
	return m_dbType;
}
///////////////////////////////////////////////////////////////

CDBDATETIME::CDBDATETIME(CDBTABLE& owner, const char* columnName)
	: CDBObject::CDBObject(columnName), m_dbType(&owner, this), m_value()
{
}

CDBDATETIME::CDBDATETIME()
	: CDBObject::CDBObject(""), m_dbType(), m_value()
{
}

CDBType CDBDATETIME::GetType()
{
	return m_dbType;
}

CDBDATETIME& NetworkCommon::DBConnection::CDBDATETIME::operator=(TIMESTAMP_STRUCT other)
{
	m_value = other;
	return *this;
}


CDBDATETIME& NetworkCommon::DBConnection::CDBDATETIME::operator=(tm& other)
{
	m_value.year = other.tm_year + 1900;
	m_value.month = other.tm_mon + 1;
	m_value.day = other.tm_mday;
	m_value.hour = other.tm_hour;
	m_value.minute = other.tm_min;
	m_value.second = other.tm_sec;
	m_value.fraction = 0;

	return *this;
}

std::string CDBDATETIME::ToString()
{
	return Format("%d-%d-%d %d:%d:%d:%d ", m_value.year, m_value.month, m_value.day, m_value.hour, m_value.minute, m_value.second, m_value.fraction);
}

///////////////////////////////////////////////////////////////

NetworkCommon::DBConnection::CDBBIGINT::CDBBIGINT(CDBTABLE& owner, const char* columnName)
	: CDBObject::CDBObject(columnName), m_dbType(&owner, this), m_value()
{
}

NetworkCommon::DBConnection::CDBBIGINT::CDBBIGINT()
	: CDBObject::CDBObject(""), m_dbType(), m_value()
{
}

CDBType NetworkCommon::DBConnection::CDBBIGINT::GetType()
{
	return m_dbType;
}

int NetworkCommon::DBConnection::CDBBIGINT::GetValue()
{
	return m_value;
}
