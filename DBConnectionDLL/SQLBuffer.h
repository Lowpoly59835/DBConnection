#pragma once
#include "type.h"
#include <exception>
#include "SharedClass.h"
#include "ExportDefine.h"

using std::exception;

namespace NetworkCommon
{
	namespace DBConnection
	{
		//int, float, datetime, string만 지원
		class DBCONNECTIONDLL_EXPORTS_DECLSPEC SQLBuffer
		{
			friend class SQLReader;
		public:
			enum EStorageType
			{
				None,
				Int,
				Float,
				String,
				DateTime
			};

			union StorageData
			{
				INT32 Int;
				FLOAT Float;
				time_t DateTime;
			};

		public:
			SQLBuffer();
			SQLBuffer(const SQLBuffer&);
			SQLBuffer(EStorageType type);
			~SQLBuffer();

			template<typename T>
			T GetValue()
			{
				switch (m_Type)
				{
				case EStorageType::Int:
					return m_Data.Int;
				case EStorageType::Float:
					return m_Data.Float;
				case EStorageType::String:
					return m_string;
				case EStorageType::DateTime:
					return m_Data.DateTime;
				default:
					throw std::exception("unknow data type");
				}
			}

			PROPERT_GETEX(m_Type, EStorageType, Type);

		private:
			SQLRETURN Bind(SQLHSTMT& hstmt, int colpos, SQLLEN string_length = 0);

			
		private:
			EStorageType m_Type;
			StorageData m_Data;
			//union으로 string을 관리하기 힘들기에 따로 관리
			std::string m_string;
		};
	}
}