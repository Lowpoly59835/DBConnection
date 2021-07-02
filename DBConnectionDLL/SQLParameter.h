#pragma once
#include "IConnection.h"

namespace NetworkCommon
{
	namespace DBConnection
	{
#pragma warning (disable : 4231)
#pragma warning( disable : 4251)
		EXPORT_STL_STRING(char);
#pragma warning (default : 4231) 
#pragma warning (default : 4251)

		struct DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLParameter
		{
		public:
			SQLParameter();
			SQLParameter(const SQLParameter*) = delete;

			SQLParameter(const char* name, char type);
			SQLParameter(const SQLParameter&);
			~SQLParameter();

		public:
			std::string m_name;
			char m_type;
		};
	}
}