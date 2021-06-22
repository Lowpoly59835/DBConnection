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

			template<typename T>
			void SetValue(T* value)
			{
				if (value == nullptr)
				{
					return;
				}

				switch (m_Type)
				{
				case EStorageType::Int:
					m_Data.Int = static_cast<int>(*value);
					break;
				case EStorageType::Float:
					m_Data.Float = static_cast<float>(*value);
					break;
				case EStorageType::String:
					m_string = static_cast<char*>(*value);
					break;
				case EStorageType::DateTime:
					m_Data.DateTime = static_cast<time>(*value);
					break;
				default:
					throw exception("unknown type");
				}
			}

			PROPERT_GETEX(m_Type, EStorageType, Type)

		private:
			EStorageType m_Type;
			StorageData m_Data;
			//union으로 string을 관리하기 힘들기에 따로 관리
			std::string m_string;
		};
	}
}