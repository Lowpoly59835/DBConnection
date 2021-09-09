#pragma once
#include "IConnection.h"

namespace NetworkCommon
{
	namespace DBConnection
	{
		class DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLConnection : public IConnection
		{
		public:
			SQLConnection() = delete;
			SQLConnection(const SQLConnection&) = delete;
			SQLConnection& operator=(const SQLConnection&) = delete;

			SQLConnection(const char* strConnection);
			~SQLConnection();

		public:
			void Open() final;
			void Close() final;

			friend class SQLCommand;

		private:
			CustomString m_strConnection;
			SQLHDBC m_connHanlde;
			SQLHENV m_envHandle;
		};
	}
}

