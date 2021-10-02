#pragma once
#include "ExportDefine.h"
#include <string>
#include <ostream>

namespace NetworkCommon
{
	namespace DBConnection
	{
		class DBCONNECTIONDLL_EXPORTS_DECLSPEC CustomString
		{
		public:
			CustomString();
			CustomString(const char* value);
			CustomString(const wchar_t* value);
			CustomString(const CustomString& other);
			~CustomString();

			CustomString& operator=(const char* value);
			CustomString& operator+=(const char* value);
			CustomString& operator=(const wchar_t* value);
			CustomString& operator+=(const wchar_t* value);
			CustomString& operator=(const CustomString& other);
			CustomString& operator=(const std::string& value);
			CustomString& operator+=(const std::string& value);
			
			operator const char* ();
			bool operator==(const CustomString& other) const;
			friend std::ostream& operator<<(std::ostream& os, const CustomString& value)
			{
				// TODO: 여기에 return 문을 삽입합니다.
				return os << const_cast<CustomString&>(value).c_str();
			}

		private:
			bool Write(const char* desc, size_t length);
			bool Write(const wchar_t* desc, size_t length);
			void Clear();
		public:
			size_t Capacity();
			const char* c_str();
			const char* data();
			bool Empty();
			size_t Size();
			void Resize(size_t length);
			size_t Max();
		private:
			static const int DEFAULT_SIZE = 64;

			size_t max_size;
			size_t write_size;
			char* m_Buff;
		};
	}
}