#pragma once
#include "DBType.h"
#include <vector>
#include "ExportDefine.h"
#include <unordered_map>
#include <string>
#include "HashFunc.h"

using std::unordered_map;
using std::vector;

namespace NetworkCommon
{
	namespace DBConnection
	{
#pragma warning (disable : 4231)
#pragma warning( disable : 4251)
		//EXPORT_INTERFACE_CLASS(vector<CDBType>);
		//EXPORT_INTERFACE_CLASS(unordered_map<CustomString, CDBType, HashCustomString>);
		EXPORT_INTERFACE_CLASS(unordered_map<CustomString, unordered_map<CustomString, CDBType, HashCustomString>, HashCustomString>);
		EXPORT_INTERFACE_CLASS(unordered_map<CustomString, vector<CDBType>, HashCustomString>);
#pragma warning (default : 4231) 
#pragma warning (default : 4251)


		class DBCONNECTIONDLL_EXPORTS_DECLSPEC CDBTypeManager : public CSingleton<CDBTypeManager>
		{
			typedef unordered_map<CustomString, unordered_map<CustomString, CDBType, HashCustomString>, HashCustomString> MapTypeList;
			typedef unordered_map<CustomString, vector<CDBType>, HashCustomString> MapCashTypeList;
			typedef unordered_map<CustomString, CDBType, HashCustomString> MapType;
		public:
			CDBTypeManager() = default;
			~CDBTypeManager() = default;

			void RegistType(CDBType* dbType);
			void RegistType(const char* typeName, CDBType* dbType);
			vector<CDBType> FindMemberInfos(CDBType& dbType);
		private:
			MapTypeList m_TypeList;
			MapCashTypeList m_CashTypeList;
			CCriticalSection m_typelock;
			CCriticalSection m_cashlock;
		};
	}
}