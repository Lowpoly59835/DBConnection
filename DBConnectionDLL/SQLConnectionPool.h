#pragma once

#include "Singleton.h"
#include "IConnection.h"
#include "SharedClass.h"
#include <vector>
#include <string.h>

namespace NetworkCommon
{
	namespace DBConnection
	{
#pragma warning (disable : 4231)
#pragma warning( disable : 4251)
		EXPORT_INTERFACE_CLASS(std::vector<IConnection*>);
#pragma warning (default : 4231) 
#pragma warning (default : 4251)
		class DBCONNECTIONDLL_EXPORTS_DECLSPEC CSQLConnectionPool : public CSingleton<CSQLConnectionPool>
		{
		public:
			CSQLConnectionPool();
			~CSQLConnectionPool();

			IConnection* GetConnect();
			void LoadDriver(std::string driverInfo);

		private:
			std::vector<IConnection*> m_connectPool;
			std::string m_driverInfo;
			
			CCriticalSection m_cs;
			
			int m_connectCount;
			int m_maxConnectCount;
		
		public:
			PROPERT_GETEX(m_connectCount, int, ConnectSize);

			const int DefaultConnectCount = 5;
			const int DefaultMaxConectCount = 15;
		};
	}
}

