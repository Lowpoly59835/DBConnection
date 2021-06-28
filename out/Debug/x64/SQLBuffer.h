#pragma once
#include "IConnection.h"
#include "SharedClass.h"
#include "ExportDefine.h"


namespace NetworkCommon
{
	namespace DBConnection
	{
#pragma warning (disable : 4231)
#pragma warning( disable : 4251)
		EXPORT_STL_STRING(char);
#pragma warning (default : 4231) 
#pragma warning (default : 4251)
		//int, float, datetime, string만 지원
		class DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLBuffer
		{
			friend class SQLReader;
		public:
			enum class DBCONNECTIONDLL_EXPORTS_DECLSPEC EStorageType
			{
				None = 0,
				Int = 4,
				Float = 6,
				DateTime = 9,
				String = 12
			};

			union DBCONNECTIONDLL_EXPORTS_DECLSPEC StorageData
			{
				INT32 Int;
				FLOAT Float;
				time_t DateTime;
			};

			template<typename T>
			T GetValue() noexcept
			{
				static_assert(true, "unknow data type");
			}

		public:
			SQLBuffer();
			SQLBuffer(const SQLBuffer&);
			SQLBuffer(SQLSMALLINT sqlType);
			~SQLBuffer();


			PROPERT_GETEX(m_Type, EStorageType, Type);

		private:
			SQLRETURN Bind(SQLHSTMT& hstmt, int colpos);

		private:
			EStorageType m_Type;
			StorageData m_Data;
			//union으로 string을 관리하기 힘들기에 따로 관리
			std::string m_string;
		};


		template <>
		int DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLBuffer::GetValue<int>() noexcept;

		template <>
		float DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLBuffer::GetValue<float>() noexcept;

		template <>
		std::string DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLBuffer::GetValue<std::string>() noexcept;

		template <>
		time_t DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLBuffer::GetValue<time_t>() noexcept;
	}
}