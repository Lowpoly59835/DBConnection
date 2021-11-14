#pragma once
#include "DBType.h"
#include "SQLReader.h"
#include <iostream>
#include "CustomString.h"

using std::ostream;

namespace NetworkCommon
{
	namespace DBConnection
	{
		typedef class DBCONNECTIONDLL_EXPORTS_DECLSPEC CDBObject
		{
		public:
			~CDBObject() = default;

			virtual CDBType GetType() = 0;
			const char* GetName();
		protected:
			CDBObject() = default;
			CDBObject(const char* objectName);

		public:
			static CDBObject&& CreateObject(CDBType& type);
		private:
			CustomString m_objectName;
		} DBObject;

		typedef class DBCONNECTIONDLL_EXPORTS_DECLSPEC CDBTABLE : public DBObject
		{
		public:
			CDBTABLE(const char* tableName);
			CDBType GetType();
			virtual void SetRecord(SQLReader& reader) = 0;
		private:
			CDBType m_dbType;
		}DBTABLE;

		typedef class DBCONNECTIONDLL_EXPORTS_DECLSPEC CDBINT : public DBObject
		{
		public:
			CDBINT(CDBTABLE& owner, const char* columnName);
			CDBINT();
			CDBINT(const CDBINT& other) = delete;
			CDBType GetType() final;
			int GetValue();

			CDBINT& operator=(int other)
			{
				m_value = other;
				return *this;
			}

			friend ostream& operator<<(ostream& os, const CDBINT& dbINT)
			{
				// TODO: 여기에 return 문을 삽입합니다.
				return os << dbINT.m_value;
			}
		private:
			int m_value;
			CMemberInfo m_dbType;
		}DBINT;

		typedef class DBCONNECTIONDLL_EXPORTS_DECLSPEC CDBBIGINT : public DBObject
		{
		public:
			CDBBIGINT(CDBTABLE& owner, const char* columnName);
			CDBBIGINT();
			CDBBIGINT(const CDBBIGINT& other) = delete;
			CDBType GetType() final;
			INT64 GetValue();

			CDBBIGINT& operator=(INT64 other)
			{
				m_value = other;
				return *this;
			}

			friend ostream& operator<<(ostream& os, const CDBBIGINT& dbINT)
			{
				// TODO: 여기에 return 문을 삽입합니다.
				return os << dbINT.m_value;
			}
		private:
			INT64 m_value;
			CMemberInfo m_dbType;
		}DBBIGINT;

		typedef class DBCONNECTIONDLL_EXPORTS_DECLSPEC CDBSTRING : public DBObject
		{
		public:
			CDBSTRING(CDBTABLE& owner, const char* columnName);
			CDBSTRING();
			CDBSTRING(const CDBSTRING& other) = delete;
			CDBType GetType() final;

			const char* GetValue();

			CDBSTRING& operator=(std::string other)
			{
				m_value = other;
				return *this;
			}

			friend ostream& operator<<(ostream& os, const CDBSTRING& dbValue)
			{
				// TODO: 여기에 return 문을 삽입합니다.
				return os << dbValue.m_value;
			}
		private:
			CustomString m_value;
			CMemberInfo m_dbType;
		}DBSTRING;


		typedef class DBCONNECTIONDLL_EXPORTS_DECLSPEC CDBFLOAT : public DBObject
		{
		public:
			CDBFLOAT(CDBTABLE& owner, const char* columnName);
			CDBFLOAT();
			CDBFLOAT(const CDBFLOAT& other) = delete;
			CDBType GetType() final;


			float GetValue();

			CDBFLOAT& operator=(float other)
			{
				m_value = other;
				return *this;
			}

			friend ostream& operator<<(ostream& os, const CDBFLOAT& dbValue)
			{
				// TODO: 여기에 return 문을 삽입합니다.
				return os << dbValue.m_value;
			}
		private:
			float m_value;
			CMemberInfo m_dbType;
		}DBFLOAT;



		typedef class DBCONNECTIONDLL_EXPORTS_DECLSPEC CDBDATETIME : public DBObject
		{
		public:
			CDBDATETIME(CDBTABLE& owner, const char* columnName);
			CDBDATETIME();
			CDBDATETIME(const CDBFLOAT& other) = delete;
			CDBType GetType() final;

			TIMESTAMP_STRUCT GetValue();

			CDBDATETIME& operator=(TIMESTAMP_STRUCT other);
			CDBDATETIME& operator=(tm& other);

			friend ostream& operator<<(ostream& os, CDBDATETIME& dbValue)
			{
				// TODO: 여기에 return 문을 삽입합니다.
				return os << dbValue.ToString();
			}

			std::string ToString();
		private:
			TIMESTAMP_STRUCT m_value;
			CMemberInfo m_dbType;
		}DBDATETIME;
	}
}