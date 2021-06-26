#pragma once
#include "IConnection.h"

namespace NetworkCommon
{
	namespace DBConnection
	{
#pragma warning (disable : 4231)
#pragma warning( disable : 4251)
		EXPORT_STL_STRING(wchar_t);
#pragma warning (default : 4231) 
#pragma warning (default : 4251)
		class DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLConnection : public IConnection
		{
		public:
			SQLConnection() = delete;
			SQLConnection(const SQLConnection&) = delete;
			SQLConnection& operator=(const SQLConnection&) = delete;

			SQLConnection(const wchar_t* strConnection);
			~SQLConnection();

		public:
			void Open() final;
			void Close() final;

			friend class SQLCommand;

		private:
			std::wstring m_strConnection;
			SQLHDBC m_connHanlde;
			SQLHENV m_envHandle;
		};
	}
}

