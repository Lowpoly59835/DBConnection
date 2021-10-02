#pragma once
#include "SQLConnection.h"

namespace NetworkCommon
{
	namespace DBConnection
	{
		class DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLTranstaction
		{
		public:
			SQLTranstaction() = delete;
			SQLTranstaction(SQLConnection* connection);
			~SQLTranstaction();

			void BegionTrans();
			void Commit();
			void Rollback();

		private:
			SQLConnection* m_connection;
			bool m_isCommit;
		};
	}
}

