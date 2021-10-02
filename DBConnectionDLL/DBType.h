#pragma once
#include <vector>

#include "Singleton.h"
#include "SharedClass.h"

#include "ExportDefine.h"

#include "CustomString.h"

using std::vector;

namespace NetworkCommon
{
	namespace DBConnection
	{		
		class CDBObject;

		class DBCONNECTIONDLL_EXPORTS_DECLSPEC CDBType
		{
		public:
			CDBType(CDBObject* obj);
			~CDBType() = default;

			const char* GetName() { return m_name.c_str(); }
			vector<CDBType> GetMemberInfos();

			bool operator==(const type_info& other);
			bool operator==(const CDBType& other);
			bool operator==(const CDBType& other) const;

		protected:
			CDBType();

		protected:
			CustomString m_name;
			size_t m_nativeTypeHashCode;
		};

		class DBCONNECTIONDLL_EXPORTS_DECLSPEC CMemberInfo : public CDBType
		{
		public:
			CMemberInfo();
			CMemberInfo(CDBObject* owner, CDBObject* member);
			~CMemberInfo() = default;
		};

	}
}