#pragma once
#include "IConnection.h"

namespace NetworkCommon
{
	namespace DBConnection
	{
		class DBCONNECTIONDLL_EXPORTS SQLConnection : public IConnection
		{
		public:
			SQLConnection() = delete;
			SQLConnection(const SQLConnection&) = delete;
			SQLConnection& operator=(const SQLConnection&) = delete;

			SQLConnection(const wchar_t* strConnection);
			~SQLConnection();

		public:
			void Open() throw(std::exception) final;
			void Close() throw(std::exception) final;

			friend class SQLCommand;

		private:
			std::wstring m_strConnection;
			SQLHDBC m_connHanlde;
			SQLHENV m_envHandle;
		};
	}
}

