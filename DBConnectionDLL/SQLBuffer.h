#pragma once
#include "IConnection.h"
#include "SharedClass.h"
#include "ExportDefine.h"


namespace NetworkCommon
{
	namespace DBConnection
	{
		//int, float, datetime, string만 지원
		class DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLBuffer
		{
		public:
			enum class DBCONNECTIONDLL_EXPORTS_DECLSPEC EStorageType : SQLSMALLINT
			{
				None = 0,
				Int = SQL_INTEGER,
				BIGINT = SQL_BIGINT,
				Float = SQL_FLOAT,
				DateTime = SQL_DATETIME,
				String = SQL_VARCHAR
			};

			union DBCONNECTIONDLL_EXPORTS_DECLSPEC StorageData
			{
				SQLINTEGER  Int;
				SQLFLOAT	Float;
				SQLBIGINT	BIGINT;
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
			friend class SQLReader;
			friend class SQLParameter;
			friend class SQLCommand;

			void* GetBuffer();

		private:
			EStorageType m_type;
			StorageData m_data;
			//union으로 string을 관리하기 힘들기에 따로 관리
			CustomString m_strData;
		};


		template <>
		int DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLBuffer::GetValue<int>() noexcept;
		
		template <>
		long long DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLBuffer::GetValue<long long>() noexcept;

		template <>
		float DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLBuffer::GetValue<float>() noexcept;

		template <>
		std::string DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLBuffer::GetValue<std::string>() noexcept;

		template <>
		TIMESTAMP_STRUCT DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLBuffer::GetValue<TIMESTAMP_STRUCT>() noexcept;
	}
}