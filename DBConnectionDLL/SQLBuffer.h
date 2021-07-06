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
				SQLINTEGER  Int;
				SQLFLOAT	Float;
				TIMESTAMP_STRUCT  DateTime;
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

			PROPERT_GETEX(m_type, EStorageType, Type);


		private:
			//SQLRETURN ParmeterBind(SQLHSTMT & hstmt, int colpos, char inputOutputType);
			friend class SQLReader;
			friend class SQLCommand;
			void* GetBuffer();

		private:
			EStorageType m_type;
			StorageData m_data;
			//union으로 string을 관리하기 힘들기에 따로 관리
			std::string m_strData;
		};


		template <>
		int DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLBuffer::GetValue<int>() noexcept;

		template <>
		float DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLBuffer::GetValue<float>() noexcept;

		template <>
		std::string DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLBuffer::GetValue<std::string>() noexcept;

		template <>
		TIMESTAMP_STRUCT DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLBuffer::GetValue<TIMESTAMP_STRUCT>() noexcept;
	}
}