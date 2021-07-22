#pragma once
#include "IConnection.h"
#include "SharedClass.h"
#include "ExportDefine.h"


namespace NetworkCommon
{
	namespace DBConnection
	{
		//int, float, datetime, string�� ����
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
			friend class SQLReader;
			friend class SQLParameter;

			void* GetBuffer();

		private:
			EStorageType m_type;
			StorageData m_data;
			//union���� string�� �����ϱ� ����⿡ ���� ����
			CustomString m_strData;
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